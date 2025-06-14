#include "Common.h"
#include "Utils.h"
#include "Menu.h"
#include "PageLocalRadio.h"

// using namespace eez;
using namespace eez::flow;

#define MIN_ELAPSED_RSSI_TIME 200 // RSSI check uses IN_ELAPSED_RSSI_TIME * 6 = 1.2s

long elapsedRSSI = millis();

bool seekStop = false; // G8PTN: Added flag to abort seeking on rotary encoder detection

// Switch radio to given band
void useBand(const Band *band)
{
  // Set current frequency and mode, reset BFO
  set_var_local_frequency(band->currentFreq);
  currentMode = band->bandMode;
  currentBFO = 0;

  if (band->bandMode == FM)
  {
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
  }
  else
  {
    if (band->bandMode == AM)
    {
      rx.setAM(band->minimumFreq, band->maximumFreq, band->currentFreq, getCurrentStep()->step);
      // More sensitive seek thresholds
      // https://github.com/pu2clr/SI4735/issues/7#issuecomment-810963604
      rx.setSeekAmRssiThreshold(15); // default is 25
      rx.setSeekAmSNRThreshold(5);   // default is 5
    }
    else
    {
      // Configure SI4732 for SSB (SI4732 step not used, set to 0)
      rx.setSSB(band->minimumFreq, band->maximumFreq, band->currentFreq, 0, currentMode);
      // G8PTN: Always enabled
      rx.setSSBAutomaticVolumeControl(1);
      // G8PTN: Commented out
      // rx.setSsbSoftMuteMaxAttenuation(softMuteMaxAttIdx);
      // To move frequency forward, need to move the BFO backwards
      rx.setSSBBfo(-(currentBFO + band->bandCal));
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
  set_var_local_rssi(0);
}

// This function is called by the seek function process.
bool checkStopSeeking()
{
  // Returns true if the user rotates the encoder
  if (seekStop)
    return true;

  // Checking isPressed without debouncing because this callback
  // is not invoked often enough to register a click
  if (pb1.update(io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW, 0).isPressed)
  {
    // Wait till the button is released, otherwise the main loop will register a click
    while (pb1.update(io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW).isPressed)
      delay(100);
    return true;
  }

  return false;
}

// This function is called by the seek function process.
void showFrequencySeek(uint16_t freq)
{
  set_var_local_frequency(freq);
}

// Tune using BFO, using algorithm from Goshante's ATS-20_EX firmware
bool updateBFO(int newBFO, bool wrap)
{
  Band *band = getCurrentBand();
  int newFreq = get_var_local_frequency();

  // No BFO outside SSB modes
  if (!isSSB())
    newBFO = 0;

  // If new BFO exceeds allowed bounds...
  if (newBFO > MAX_BFO || newBFO < -MAX_BFO)
  {
    // Compute correction
    int fCorrect = (newBFO / MAX_BFO) * MAX_BFO;
    // Correct new frequency and BFO
    newFreq += fCorrect / 1000;
    newBFO -= fCorrect;
  }

  // Do not let new frequency exceed band limits
  int f = newFreq * 1000 + newBFO;
  if (f < band->minimumFreq * 1000)
  {
    if (!wrap)
      return false;
    newFreq = band->maximumFreq;
    newBFO = 0;
  }
  else if (f > band->maximumFreq * 1000)
  {
    if (!wrap)
      return false;
    newFreq = band->minimumFreq;
    newBFO = 0;
  }

  // If need to change frequency...
  if (newFreq != get_var_local_frequency())
  {
    // Apply new frequency
    rx.setFrequency(newFreq);

    // Re-apply to remove noise
    doAgc(0);
    // Update current frequency
    set_var_local_frequency(rx.getFrequency());
  }

  // Update current BFO
  currentBFO = newBFO;

  // To move frequency forward, need to move the BFO backwards
  rx.setSSBBfo(-(currentBFO + band->bandCal));

  // Save current band frequency, w.r.t. new BFO value
  band->currentFreq = get_var_local_frequency() + currentBFO / 1000;
  return true;
}

// Tune to a new frequency, resetting BFO if present
bool updateFrequency(int newFreq, bool wrap)
{
  Band *band = getCurrentBand();

  // Do not let new frequency exceed band limits
  if (newFreq < band->minimumFreq)
  {
    if (!wrap)
      return false;
    else
      newFreq = band->maximumFreq;
  }
  else if (newFreq > band->maximumFreq)
  {
    if (!wrap)
      return false;
    else
      newFreq = band->minimumFreq;
  }

  // Set new frequency
  rx.setFrequency(newFreq);

  // Clear BFO, if present
  if (currentBFO)
    updateBFO(0, true);

  // Update current frequency
  set_var_local_frequency(rx.getFrequency());

  // Save current band frequency
  band->currentFreq = get_var_local_frequency() + currentBFO / 1000;
  return true;
}

// Handle tuning
bool doTune(int8_t dir)
{
  //
  // SSB tuning
  //
  if (isSSB())
  {
#ifdef ENABLE_HOLDOFF
    // Tuning timer to hold off (SSB) display updates
    tuning_flag = true;
    tuning_timer = millis();
#endif

    uint32_t step = getCurrentStep()->step;
    uint32_t stepAdjust = (get_var_local_frequency() * 1000 + currentBFO) % step;
    step = !stepAdjust ? step : dir > 0 ? step - stepAdjust
                                        : stepAdjust;

    updateBFO(currentBFO + dir * step, true);
  }

  //
  // Normal tuning
  //
  else
  {
#ifdef ENABLE_HOLDOFF
    // Tuning timer to hold off (FM/AM) display updates
    tuning_flag = true;
    tuning_timer = millis();
#endif

    // G8PTN: Used in place of rx.frequencyUp() and rx.frequencyDown()
    uint16_t step = getCurrentStep()->step;
    uint16_t stepAdjust = get_var_local_frequency() % step;
    step = !stepAdjust ? step : dir > 0 ? step - stepAdjust
                                        : stepAdjust;

    // Tune to a new frequency
    updateFrequency(get_var_local_frequency() + step * dir, true);
  }

  // Clear current station name and information
  clearStationInfo();
  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + currentBFO / 1000);
  // Will need a redraw
  return (true);
}

// Handle encoder rotation in seek mode
bool doSeek(int8_t dir)
{
  if (seekMode() == SEEK_DEFAULT)
  {
    if (isSSB())
    {
#ifdef ENABLE_HOLDOFF
      // Tuning timer to hold off (FM/AM) display updates
      tuning_flag = true;
      tuning_timer = millis();
#endif

      updateBFO(currentBFO + dir * getCurrentStep(true)->step, true);
    }
    else
    {
      // Clear stale parameters
      clearStationInfo();
      set_var_local_snr(0);
      set_var_local_rssi(0);

      // G8PTN: Flag is set by rotary encoder and cleared on seek entry
      seekStop = false;
      rx.seekStationProgress(showFrequencySeek, checkStopSeeking, dir > 0 ? 1 : 0);
      updateFrequency(rx.getFrequency(), true);
    }
  }
  else if (seekMode() == SEEK_SCHEDULE && dir)
  {
    // uint8_t hour, minute;
    // // Clock is valid because the above seekMode() call checks that
    // clockGetHM(&hour, &minute);

    // size_t offset = -1;
    // const StationSchedule *schedule = dir > 0 ? eibiNext(currentFrequency + currentBFO / 1000, hour, minute, &offset) : eibiPrev(currentFrequency + currentBFO / 1000, hour, minute, &offset);

    // if (schedule)
    //   updateFrequency(schedule->freq, false);
  }

  // Clear current station name and information
  clearStationInfo();
  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + currentBFO / 1000);
  // Will need a redraw
  return (true);
}

// Rotate digit
bool doDigit(int8_t dir)
{
  bool updated = false;

  // SSB tuning
  if (isSSB())
  {
#ifdef ENABLE_HOLDOFF
    // Tuning timer to hold off (SSB) display updates
    tuning_flag = true;
    tuning_timer = millis();
#endif

    updated = updateBFO(currentBFO + dir * getFreqInputStep(), false);
  }

  //
  // Normal tuning
  //
  else
  {
#ifdef ENABLE_HOLDOFF
    // Tuning timer to hold off (FM/AM) display updates
    tuning_flag = true;
    tuning_timer = millis();
#endif

    // Tune to a new frequency
    updated = updateFrequency(get_var_local_frequency() + getFreqInputStep() * dir, false);
  }

  if (updated)
  {
    // Clear current station name and information
    clearStationInfo();
    // Check for named frequencies
    identifyFrequency(get_var_local_frequency() + currentBFO / 1000);
  }

  // Will need a redraw
  return (updated);
}

bool clickFreq(bool shortPress)
{
  if (shortPress)
  {
    bool updated = false;

    // SSB tuning
    if (isSSB())
    {
      updated = updateBFO(currentBFO - (get_var_local_frequency() * 1000 + currentBFO) % getFreqInputStep(), false);
    }
    else
    {
      // Normal tuning
      updated = updateFrequency(get_var_local_frequency() - get_var_local_frequency() % getFreqInputStep(), false);
    }

    if (updated)
    {
      // Clear current station name and information
      clearStationInfo();
      // Check for named frequencies
      identifyFrequency(get_var_local_frequency() + currentBFO / 1000);
    }
    return true;
  }
  return false;
}

void processRssiSnr()
{
  static uint32_t updateCounter = 0;

  rx.getCurrentReceivedSignalQuality();
  int newRSSI = rx.getCurrentRSSI();
  int newSNR = rx.getCurrentSNR();

  // Apply squelch if the volume is not muted
  int32_t currentSquelch = get_var_local_squelch();
  bool squelchCutoff = get_var_local_squelch_cutoff();
  if (currentSquelch && currentSquelch <= 127)
  {
    if (newRSSI >= currentSquelch && squelchCutoff)
    {
      tempMuteOn(false);
      set_var_local_squelch_cutoff(false);
    }
    else if (newRSSI < currentSquelch && !squelchCutoff)
    {
      tempMuteOn(true);
      set_var_local_squelch_cutoff(true);
    }
  }
  else if (squelchCutoff)
  {
    tempMuteOn(false);
    set_var_local_squelch_cutoff(false);
  }

  // G8PTN: Based on 1.2s interval, update RSSI & SNR
  if (!(updateCounter++ & 7))
  {
    // Show RSSI status only if this condition has changed
    if (newRSSI != get_var_local_rssi())
    {
      set_var_local_rssi(newRSSI);
      set_var_local_rssi_bar(getRssiBar(newRSSI));
    }
    // Show SNR status only if this condition has changed
    if (newSNR != get_var_local_snr())
    {
      set_var_local_snr(newSNR);
      set_var_local_snr_bar(getSnrBar(newSNR));
    }
  }
}

void updatePageLocalRadio()
{
  uint32_t currentTime = millis();
  int32_t local_index = get_var_local_index();

  if (encoderCount1)
  {
    if (local_index < 0)
    {
      doTune(-encoderCount1);
      eepromRequestSave();
    }
    else
    {
      local_index = local_index - encoderCount1;
      if (local_index < 0)
      {
        local_index = 9;
      }
      else if (local_index > 9)
      {
        local_index = 0;
      }
      set_var_local_index(local_index);
    }
  }

  if (encoderCount2)
  {
    doVolume(encoderCount2);
    eepromRequestSave();
  }

  if (pb1st.isPressed)
  {
    //
  }

  if (pb1st.wasClicked)
  {
    set_var_local_index(local_index < 0 ? 0 : -1);
  }

  if (pb1st.wasShortPressed || pb1st.isLongPressed)
  {
    eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
    set_var_page_name(PageName_Main);
  }

  if (pb2st.isPressed)
  {
    //
  }

  if (pb2st.wasClicked)
  {
    if (local_index >= 0)
    {
      set_var_local_index(-1);
    }
  }

  if (pb2st.wasShortPressed)
  {
    //
  }

  if (pb2st.isLongPressed)
  {
    //
  }

  if ((currentTime - elapsedRSSI) > MIN_ELAPSED_RSSI_TIME)
  {
    processRssiSnr();
    elapsedRSSI = currentTime;
  }
}
