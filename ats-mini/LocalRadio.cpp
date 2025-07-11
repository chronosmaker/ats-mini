#include "Common.h"
#include "Utils.h"
#include "LocalRadio.h"

bool seekStop = false; // G8PTN: Added flag to abort seeking on rotary encoder detection

/**
 * @brief 检查是否停止搜索
 * 如果用户旋转编码器或按下编码器按钮，则返回 true。
 * @return 如果用户旋转编码器或按下编码器按钮，则返回 true；否则返回 false。
 */
bool checkStopSeeking() {
  // Returns true if the user rotates the encoder
  if (seekStop)
    return true;
  // Checking isPressed without debouncing because this callback
  // is not invoked often enough to register a click
  if (pb1.update(io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW, 0).isPressed) {
    // Wait till the button is released, otherwise the main loop will register a click
    while (pb1.update(io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW).isPressed)
      delay(100);
    return true;
  }
  return false;
}

/**
 * @brief 显示频率搜索
 * 显示频率搜索界面，并更新本地频率变量。
 * @param freq 频率值，类型为 uint16_t
 */
void showFrequencySeek(uint16_t freq) {
  set_var_local_frequency(freq);
  ui_tick();
  lv_timer_handler();
}

/**
 * @brief 更新当前BFO值
 * 更新当前BFO值，并确保其在允许的范围内。如果新的频率超出当前频带的限制，
 * 则根据是否启用环绕模式调整频率或返回错误。
 * Tune using BFO, using algorithm from Goshante's ATS-20_EX firmware
 * @param newBFO 新的BFO值
 * @param wrap 是否启用环绕模式
 * @return 如果成功更新BFO则返回true，否则返回false
 */
bool updateBFO(int newBFO, bool wrap) {
  Band* band = getCurrentBand();
  int newFreq = get_var_local_frequency();

  // No BFO outside SSB modes
  if (!isSSB()) {
    newBFO = 0;
  }

  // If new BFO exceeds allowed bounds...
  if (newBFO > MAX_BFO || newBFO < -MAX_BFO) {
    // Compute correction
    int fCorrect = (newBFO / MAX_BFO) * MAX_BFO;
    // Correct new frequency and BFO
    newFreq += fCorrect / 1000;
    newBFO -= fCorrect;
  }

  // Do not let new frequency exceed band limits
  int f = newFreq * 1000 + newBFO;
  if (f < band->minimumFreq * 1000) {
    if (!wrap)
      return false;
    newFreq = band->maximumFreq;
    newBFO = 0;
  } else if (f > band->maximumFreq * 1000) {
    if (!wrap)
      return false;
    newFreq = band->minimumFreq;
    newBFO = 0;
  }

  // If need to change frequency...
  if (newFreq != get_var_local_frequency()) {
    // Apply new frequency
    rx.setFrequency(newFreq);
    // Re-apply to remove noise
    doAgc(0);
    // Update current frequency
    set_var_local_frequency(rx.getFrequency());
  }

  // Update current BFO
  set_var_local_bfo(newBFO);

  // To move frequency forward, need to move the BFO backwards
  rx.setSSBBfo(-(get_var_local_bfo() + band->bandCal));

  // Save current band frequency, w.r.t. new BFO value
  band->currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  return true;
}

/**
 * @brief 更新频率
 * 更新当前频带中的频率，如果新频率超出频带限制，可以选择是否回绕。
 * @param newFreq 新的频率值
 * @param wrap 是否启用回绕功能，true表示启用，false表示不启用
 * @return 如果更新成功返回true，否则返回false
 */
bool updateFrequency(int newFreq, bool wrap) {
  Band* band = getCurrentBand();

  // Do not let new frequency exceed band limits
  if (newFreq < band->minimumFreq) {
    if (!wrap) {
      return false;
    } else {
      newFreq = band->maximumFreq;
    }
  } else if (newFreq > band->maximumFreq) {
    if (!wrap) {
      return false;
    } else {
      newFreq = band->minimumFreq;
    }
  }

  // Set new frequency
  rx.setFrequency(newFreq);

  // Clear BFO, if present
  if (get_var_local_bfo()) {
    updateBFO(0, true);
  }

  // Update current frequency
  set_var_local_frequency(rx.getFrequency());

  // Save current band frequency
  band->currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  return true;
}

/**
 * @brief 改变当前频段
 * 根据输入的方向参数，改变当前频段。
 * @param dir 改变频段的方向，正值表示向上移动频段，负值表示向下移动频段
 */
void doBand(int dir) {
  int32_t bandIdx = get_var_local_band_index();
  // Save current band settings
  bands[bandIdx].currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[get_var_local_mode_index()];
  bands[bandIdx].bandMode = get_var_local_mode_index();

  set_var_local_step_index(stepIdx[get_var_local_mode_index()]);

  // Change band
  bandIdx = wrap_range(bandIdx, dir, 0, getLastBand());
  set_var_local_band_index(bandIdx);

  // Enable the new band
  selectBand(bandIdx);
}

/**
 * @brief 根据给定的方向调整当前频段模式
 * 根据给定的方向（dir）调整当前频段的模式。
 * @param dir 调整方向，可以是正值或负值，表示向上或向下调整模式
 */
void doMode(int dir) {
  int32_t bandIdx = get_var_local_band_index();
  // This is our current mode for the current band
  set_var_local_mode_index(bands[bandIdx].bandMode);

  // Cannot change away from FM mode
  if (get_var_local_mode_index() == FM) {
    return;
  }

  // Change AM/LSB/USB modes, do not allow FM mode
  do {
    set_var_local_mode_index(wrap_range(get_var_local_mode_index(), dir, 0, getLastBandMode()));
  } while (get_var_local_mode_index() == FM);

  // Save current band settings
  bands[bandIdx].currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[get_var_local_mode_index()];
  bands[bandIdx].bandMode = get_var_local_mode_index();

  set_var_local_step_index(stepIdx[get_var_local_mode_index()]);

  // Enable the new band
  selectBand(bandIdx);
}

/**
 * @brief 执行一个步长搜索
 * 根据给定的方向参数，执行一个步长搜索，更新当前步长索引，并设置接收机的频率步长和搜索间隔。
 * @param dir 方向参数，1 表示向前，-1 表示向后
 */
void doStep(int dir) {
  uint8_t idx = stepIdx[get_var_local_mode_index()];

  idx = wrap_range(idx, dir, 0, getLastStep(get_var_local_mode_index()));
  bands[get_var_local_band_index()].currentStepIdx = stepIdx[get_var_local_mode_index()] = idx;

  set_var_local_step_index(idx);

  rx.setFrequencyStep(steps[get_var_local_mode_index()][idx].step);

  // Set seek spacing
  if (get_var_local_mode_index() == FM) {
    rx.setSeekFmSpacing(steps[get_var_local_mode_index()][idx].spacing);
  } else {
    rx.setSeekAmSpacing(steps[get_var_local_mode_index()][idx].spacing);
  }
}

/**
 * @brief 调整频率
 * 根据方向参数调整频率，支持SSB和正常模式。
 * @param dir 调整方向，正数表示向上调整，负数表示向下调整
 */
void doTune(int8_t dir) {
  // SSB tuning
  if (isSSB()) {
    uint32_t step = getCurrentStep()->step;
    uint32_t stepAdjust = (get_var_local_frequency() * 1000 + get_var_local_bfo()) % step;
    step = !stepAdjust ? step : dir > 0 ? step - stepAdjust : stepAdjust;

    updateBFO(get_var_local_bfo() + dir * step, true);
  }

  // Normal tuning
  else {
    // G8PTN: Used in place of rx.frequencyUp() and rx.frequencyDown()
    uint16_t step = getCurrentStep()->step;
    uint16_t stepAdjust = get_var_local_frequency() % step;
    step = !stepAdjust ? step : dir > 0 ? step - stepAdjust : stepAdjust;

    // Tune to a new frequency
    updateFrequency(get_var_local_frequency() + step * dir, true);
  }

  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
}

/**
 * @brief 根据给定的方向调整频率
 * 根据给定的方向（dir）调整频率。如果当前是SSB模式，则更新BFO频率；否则，重置SNR和RSSI，
 * 并开始搜索电台。搜索过程中会检查是否达到停止条件，并更新当前频率。
 * @param dir 调整方向，正数表示向上调整，负数表示向下调整
 */
void doSeek(int8_t dir) {
  if (isSSB()) {
    updateBFO(get_var_local_bfo() + dir * getCurrentStep(true)->step, true);
  } else {
    set_var_local_snr(0);
    set_var_local_rssi(0);

    // G8PTN: Flag is set by rotary encoder and cleared on seek entry
    seekStop = false;
    rx.seekStationProgress(showFrequencySeek, checkStopSeeking, dir > 0 ? 1 : 0);
    updateFrequency(rx.getFrequency(), true);
  }
  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
}

/**
 * @brief 设置带宽
 * 根据当前模式和带宽索引设置接收机的带宽。
 */
static void setBandwidth() {
  uint8_t idx = getCurrentBandwidth()->idx;

  switch (get_var_local_mode_index()) {
  case FM:
    rx.setFmBandwidth(idx);
    break;
  case AM:
    rx.setBandwidth(idx, 1);
    break;
  case LSB:
  case USB:
    // Set Audio
    rx.setSSBAudioBandwidth(idx);
    // If audio bandwidth selected is about 2 kHz or below, it is
    // recommended to set Sideband Cutoff Filter to 0.
    rx.setSSBSidebandCutoffFilter(idx == 0 || idx == 4 || idx == 5 ? 0 : 1);
    break;
  }
}

/**
 * @brief 设置带宽
 * 根据传入的方向调整带宽索引，并设置带宽。
 * @param dir 方向，正值表示向上调整，负值表示向下调整
 */
void doBandwidth(int dir) {
  uint8_t idx = bwIdx[get_var_local_mode_index()];

  idx = wrap_range(idx, dir, 0, getLastBandwidth(get_var_local_mode_index()));
  bands[get_var_local_band_index()].bandwidthIdx = bwIdx[get_var_local_mode_index()] = idx;
  setBandwidth();
}

/**
 * @brief 执行FM区域切换操作
 * 根据传入的方向参数dir，切换FM模式下的区域。
 * @param dir 切换方向，正数表示向前切换，负数表示向后切换
 */
void doFmRegion(int dir) {
  // Only allow for FM mode
  if (get_var_local_mode_index() != FM) {
    return;
  }
  FmRegionIdx = wrap_range(FmRegionIdx, dir, 0, getLastFmRegion());
  rx.setFMDeEmphasis(fmRegions[FmRegionIdx].value);
}

/**
 * @brief 对指定方向的波段进行校准
 * 根据输入的方向（dir）对指定的波段进行校准。
 * @param dir 校准方向，正数表示增加校准值，负数表示减少校准值
 */
void doCal(int dir) {
  int32_t bandIdx = get_var_local_band_index();
  bands[bandIdx].bandCal = clamp_range(bands[bandIdx].bandCal, 10 * dir, -MAX_CAL, MAX_CAL);

  // If in SSB mode set the SI4732/5 BFO value
  // This adjusts the BFO while in the calibration menu
  if (isSSB()) {
    updateBFO(get_var_local_bfo(), true);
  }
}

/**
 * @brief 执行自动增益控制（AGC）操作
 * 根据不同的模式（FM、SSB、AM）调整AGC（自动增益控制）索引。
 * @param dir 调整方向，正数表示增加，负数表示减少
 */
void doAgc(int dir) {
  if (get_var_local_mode_index() == FM) {
    agcIdx = FmAgcIdx = wrap_range(FmAgcIdx, dir, 0, 27);
  } else if (isSSB()) {
    agcIdx = SsbAgcIdx = wrap_range(SsbAgcIdx, dir, 0, 1);
  } else {
    agcIdx = AmAgcIdx = wrap_range(AmAgcIdx, dir, 0, 37);
  }

  // Process agcIdx to generate disableAgc and agcIdx
  // agcIdx     0 1 2 3 4 5 6  ..... n    (n:    FM = 27, AM = 37, SSB = 1)
  // agcNdx     0 0 1 2 3 4 5  ..... n -1 (n -1: FM = 26, AM = 36, SSB = 0)
  // disableAgc 0 1 1 1 1 1 1  ..... 1

  // if true, disable AGC; else, AGC is enabled
  disableAgc = agcIdx > 0 ? 1 : 0;
  agcNdx = agcIdx > 1 ? agcIdx - 1 : 0;

  // Configure SI4732/5 (if agcNdx = 0, no attenuation)
  rx.setAutomaticGainControl(disableAgc, agcNdx);
}

/**
 * @brief 执行自动音量控制（AVC）操作
 * 根据传入的方向参数，调整接收机的自动音量控制（AVC）增益。
 * @param dir 调整方向，正值表示增加增益，负值表示减小增益
 */
void doAvc(int dir) {
  // Only allow for AM and SSB modes
  if (get_var_local_mode_index() == FM) {
    return;
  }

  if (isSSB()) {
    SsbAvcIdx = wrap_range(SsbAvcIdx, 2 * dir, 12, 90);
    rx.setAvcAmMaxGain(SsbAvcIdx);
  } else {
    AmAvcIdx = wrap_range(AmAvcIdx, 2 * dir, 12, 90);
    rx.setAvcAmMaxGain(AmAvcIdx);
  }
}

/**
 * @brief 执行软静音操作
 * 根据指定的方向调整软静音的衰减程度。
 * @param dir 调整方向，正值表示增加衰减，负值表示减少衰减。
 */
void doSoftMute(int dir) {
  // Nothing to do if FM mode
  if (get_var_local_mode_index() == FM) {
    return;
  }

  if (isSSB()) {
    softMuteMaxAttIdx = SsbSoftMuteIdx = wrap_range(SsbSoftMuteIdx, dir, 0, 32);
  } else {
    softMuteMaxAttIdx = AmSoftMuteIdx = wrap_range(AmSoftMuteIdx, dir, 0, 32);
  }

  rx.setAmSoftMuteMaxAttenuation(softMuteMaxAttIdx);
}

// Switch radio to given band
/**
 * @brief 使用指定的波段配置接收器
 * 根据提供的波段信息配置接收器。
 * @param band 指向波段信息的指针
 */
void useBand(const Band* band) {
  // Set current frequency and mode, reset BFO
  set_var_local_frequency(band->currentFreq);
  set_var_local_mode_index(band->bandMode);
  set_var_local_bfo(0);

  if (band->bandMode == FM) {
    rx.setFM(band->minimumFreq, band->maximumFreq, band->currentFreq, getCurrentStep()->step);
    // rx.setTuneFrequencyAntennaCapacitor(0);
    rx.setSeekFmLimits(band->minimumFreq, band->maximumFreq);

    // More sensitive seek thresholds
    // https://github.com/pu2clr/SI4735/issues/7#issuecomment-810963604
    rx.setSeekFmRssiThreshold(5); // default is 20
    rx.setSeekFmSNRThreshold(3);  // default is 3

    rx.setFMDeEmphasis(fmRegions[FmRegionIdx].value);
    rx.RdsInit();
    rx.setRdsConfig(1, 2, 2, 2, 2);
    rx.setGpioCtl(1, 0, 0); // G8PTN: Enable GPIO1 as output
    rx.setGpio(0, 0, 0);    // G8PTN: Set GPIO1 = 0
  } else {
    if (band->bandMode == AM) {
      rx.setAM(band->minimumFreq, band->maximumFreq, band->currentFreq, getCurrentStep()->step);
      // More sensitive seek thresholds
      // https://github.com/pu2clr/SI4735/issues/7#issuecomment-810963604
      rx.setSeekAmRssiThreshold(15); // default is 25
      rx.setSeekAmSNRThreshold(5);   // default is 5
    } else {
      // Configure SI4732 for SSB (SI4732 step not used, set to 0)
      rx.setSSB(band->minimumFreq, band->maximumFreq, band->currentFreq, 0, get_var_local_mode_index());
      // G8PTN: Always enabled
      rx.setSSBAutomaticVolumeControl(1);
      // G8PTN: Commented out
      // rx.setSsbSoftMuteMaxAttenuation(softMuteMaxAttIdx);
      // To move frequency forward, need to move the BFO backwards
      rx.setSSBBfo(-(get_var_local_bfo() + band->bandCal));
    }

    // Set the tuning capacitor for SW or MW/LW
    // rx.setTuneFrequencyAntennaCapacitor((band->bandType == MW_BAND_TYPE || band->bandType == LW_BAND_TYPE) ? 0 : 1);

    // G8PTN: Enable GPIO1 as output
    rx.setGpioCtl(1, 0, 0);
    // G8PTN: Set GPIO1 = 1
    rx.setGpio(1, 0, 0);
    // Consider the range all defined current band
    rx.setSeekAmLimits(band->minimumFreq, band->maximumFreq);
  }

  // Set step and spacing based on mode (FM, AM, SSB)
  doStep(0);
  // Set softMuteMaxAttIdx based on mode (AM, SSB)
  doSoftMute(0);
  // Set disableAgc and agcNdx values based on mode (FM, AM , SSB)
  doAgc(0);
  // Set currentAVC values based on mode (AM, SSB)
  doAvc(0);
  // Wait a bit for things to calm down
  delay(100);
  // Clear signal strength readings
  set_var_local_snr(0);
  set_var_local_snr_bar(getSnrBar(0));
  set_var_local_rssi(0);
  set_var_local_rssi_bar(getRssiBar(0));
}

/**
 * @brief 选择频段并设置相应的参数
 * 根据给定的索引idx选择频段，并根据需要加载或卸载SSB补丁。
 * @param idx 频段索引
 */
void selectBand(uint8_t idx) {
  // Set band and mode
  int32_t bandIdx = min(idx, getLastBand());
  set_var_local_band_index(bandIdx);
  set_var_local_mode_index(bands[bandIdx].bandMode);

  // Set tuning step
  stepIdx[get_var_local_mode_index()] = bands[bandIdx].currentStepIdx;

  // Load SSB patch as needed
  if (isSSB()) {
    loadSSB(getCurrentBandwidth()->idx);
  } else {
    unloadSSB();
  }
  // Set bandwidth for the current mode
  setBandwidth();
  // Switch radio to the selected band
  useBand(&bands[bandIdx]);
  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
}

/**
 * @brief 将频率和调制模式调整为指定的内存插槽内容
 * 根据指定的内存插槽内容，调整当前设备的频率和调制模式。
 * @param memory 指向Memory结构体的指针，包含要调整的频率和调制模式
 * @return 如果成功调整，返回true；否则返回false
 */
bool tuneToMemory(const Memory* memory) {
  // Must have frequency
  if (!memory->freq) {
    return (false);
  }
  // Must have valid band index
  if (memory->band >= getTotalBands()) {
    return (false);
  }
  // Band must contain frequency and modulation
  if (!isMemoryInBand(&bands[memory->band], memory)) {
    return (false);
  }
  int32_t bandIdx = get_var_local_band_index();
  // Must differ from the current band, frequency and modulation
  if (memory->band == bandIdx &&
    memory->freq == bands[bandIdx].currentFreq &&
    memory->mode == bands[bandIdx].bandMode) {
    return (true);
  }
  // Save current band settings
  bands[bandIdx].currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  bands[bandIdx].currentStepIdx = stepIdx[get_var_local_mode_index()];

  set_var_local_step_index(stepIdx[get_var_local_mode_index()]);

  // Load frequency and modulation from memory slot
  bands[memory->band].currentFreq = memory->freq;
  bands[memory->band].bandMode = memory->mode;

  // Enable the new band
  selectBand(memory->band);

  // Update BFO if present in memory slot
  if (memory->hz100) {
    updateBFO(memory->hz100 * 100, false);
  }
  return (true);
}

/**
 * @brief 根据方向调整内存指针的位置，并播放调整后的内存中的音频
 * 根据传入的方向参数dir，调整本地变量中的内存指针位置，并播放调整后的内存中的音频。
 * @param dir 调整方向，正数表示向前移动，负数表示向后移动
 */
void doMemory(int dir) {
  set_var_local_seek_index(wrap_range(get_var_local_seek_index(), dir, 0, getLastMemory() + 2));
  int32_t memoryIdx = get_var_local_seek_index() - 2;
  if (memoryIdx >= 0) {
    tuneToMemory(&memories[memoryIdx]);
  }
}

/**
 * @brief 根据给定的方向查找内存
 * 根据给定的方向（dir）查找内存。首先获取当前内存索引，然后尝试根据方向调整到下一个内存。
 * 如果调整成功，则更新当前内存索引；如果调整失败，则继续尝试，直到找到可用的内存或回到起始位置。
 * @param dir 内存查找方向，正数表示向前查找，负数表示向后查找
 */
void doSeekMemory(int dir) {
  int32_t current = get_var_local_seek_index() - 2;
  int32_t next = wrap_range(current, dir, 0, getLastMemory());

  while (!tuneToMemory(&memories[next])) {
    next = wrap_range(next, dir, 0, getLastMemory());
    if (next == current) {
      break;
    }
  }
  if (next != current) {
    set_var_local_seek_index(next + 2);
  }
}

/**
 * @brief 保存内存信息
 * 该函数根据当前设置的本地变量，更新或清除内存中的相关信息。
 * 如果指定索引的内存信息为空（freq为0），则根据当前本地变量创建一个新的Memory对象，并将其保存到指定索引的内存中。
 * 如果指定索引的内存信息不为空，则将freq置为0，以清空该内存信息。
 * 调用 tuneToMemory 函数将收音机调到新设置的频率。
 */
void doSaveMemory() {
  int32_t idx = get_var_local_seek_index() - 2;
  if (!memories[idx].freq) {
    Memory newMemory;
    newMemory.freq = get_var_local_frequency() + get_var_local_bfo() / 1000;
    newMemory.hz100 = (get_var_local_bfo() % 1000) / 100;
    newMemory.mode = get_var_local_mode_index();
    newMemory.band = get_var_local_band_index();

    memories[idx] = newMemory;
    tuneToMemory(&memories[idx]);
  } else {
    memories[idx].freq = 0;
  }
}

/**
 * @brief 处理RSSI和SNR值
 * 该函数用于处理接收到的RSSI和SNR值，并根据静噪设置调整静音状态。
 * 如果当前静噪值不为0且小于等于127，则会根据RSSI值与静噪值的比较结果来决定是否开启静音，
 * 并更新静噪截断状态。如果当前静噪值为0或者大于127，则始终关闭静音，并清除静噪截断状态。
 * 此外，该函数还根据RSSI和SNR值的变化情况，更新相应的本地变量和状态条显示。
 */
void processRssiSnr() {
  static uint32_t updateCounter = 0;

  rx.getCurrentReceivedSignalQuality();
  int newRSSI = rx.getCurrentRSSI();
  int newSNR = rx.getCurrentSNR();

  // Apply squelch if the volume is not muted
  int32_t currentSquelch = get_var_local_squelch();
  bool squelchCutoff = get_var_local_squelch_cutoff();
  if (currentSquelch && currentSquelch <= 127) {
    if (newRSSI >= currentSquelch && squelchCutoff) {
      tempMuteOn(false);
      set_var_local_squelch_cutoff(false);
    } else if (newRSSI < currentSquelch && !squelchCutoff) {
      tempMuteOn(true);
      set_var_local_squelch_cutoff(true);
    }
  } else if (squelchCutoff) {
    tempMuteOn(false);
    set_var_local_squelch_cutoff(false);
  }

  // G8PTN: Based on 1.2s interval, update RSSI & SNR
  if (!(updateCounter++ & 7)) {
    // Show RSSI status only if this condition has changed
    if (newRSSI != get_var_local_rssi()) {
      set_var_local_rssi(newRSSI);
      set_var_local_rssi_bar(getRssiBar(newRSSI));
    }
    // Show SNR status only if this condition has changed
    if (newSNR != get_var_local_snr()) {
      set_var_local_snr(newSNR);
      set_var_local_snr_bar(getSnrBar(newSNR));
    }
  }
}
