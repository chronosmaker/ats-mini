#include "Common.h"
#include "Utils.h"
#include "Menu.h"
#include "PageLocalRadio.h"

// using namespace eez;
using namespace eez::flow;

#define MIN_ELAPSED_RSSI_TIME 200 // RSSI check uses IN_ELAPSED_RSSI_TIME * 6 = 1.2s

long elapsedRSSI = millis();

bool seekStop = false; // G8PTN: Added flag to abort seeking on rotary encoder detection

// This function is called by the seek function process.
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

// This function is called by the seek function process.
void showFrequencySeek(uint16_t freq) {
  set_var_local_frequency(freq);
  ui_tick();
  lv_timer_handler();
}

// Tune using BFO, using algorithm from Goshante's ATS-20_EX firmware
bool updateBFO(int newBFO, bool wrap) {
  Band* band = getCurrentBand();
  int newFreq = get_var_local_frequency();

  // No BFO outside SSB modes
  if (!isSSB())
    newBFO = 0;

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

// Tune to a new frequency, resetting BFO if present
bool updateFrequency(int newFreq, bool wrap) {
  Band* band = getCurrentBand();

  // Do not let new frequency exceed band limits
  if (newFreq < band->minimumFreq) {
    if (!wrap)
      return false;
    else
      newFreq = band->maximumFreq;
  } else if (newFreq > band->maximumFreq) {
    if (!wrap)
      return false;
    else
      newFreq = band->minimumFreq;
  }

  // Set new frequency
  rx.setFrequency(newFreq);

  // Clear BFO, if present
  if (get_var_local_bfo())
    updateBFO(0, true);

  // Update current frequency
  set_var_local_frequency(rx.getFrequency());

  // Save current band frequency
  band->currentFreq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  return true;
}

// Handle tuning
bool doTune(int8_t dir) {
  //
  // SSB tuning
  //
  if (isSSB()) {
    uint32_t step = getCurrentStep()->step;
    uint32_t stepAdjust = (get_var_local_frequency() * 1000 + get_var_local_bfo()) % step;
    step = !stepAdjust ? step : dir > 0 ? step - stepAdjust
      : stepAdjust;

    updateBFO(get_var_local_bfo() + dir * step, true);
  }

  //
  // Normal tuning
  //
  else {
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
  identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
  // Will need a redraw
  return (true);
}

// Handle encoder rotation in seek mode
bool doSeek(int8_t dir) {
  if (seekMode() == SEEK_DEFAULT) {
    if (isSSB()) {
      updateBFO(get_var_local_bfo() + dir * getCurrentStep(true)->step, true);
    } else {
      // Clear stale parameters
      clearStationInfo();
      set_var_local_snr(0);
      set_var_local_rssi(0);

      // G8PTN: Flag is set by rotary encoder and cleared on seek entry
      seekStop = false;
      rx.seekStationProgress(showFrequencySeek, checkStopSeeking, dir > 0 ? 1 : 0);
      updateFrequency(rx.getFrequency(), true);
    }
  } else if (seekMode() == SEEK_SCHEDULE && dir) {
    // uint8_t hour, minute;
    // // Clock is valid because the above seekMode() call checks that
    // clockGetHM(&hour, &minute);

    // size_t offset = -1;
    // const StationSchedule *schedule = dir > 0 ? eibiNext(currentFrequency + get_var_local_bfo() / 1000, hour, minute, &offset) : eibiPrev(currentFrequency + get_var_local_bfo() / 1000, hour, minute, &offset);

    // if (schedule)
    //   updateFrequency(schedule->freq, false);
  }

  // Clear current station name and information
  clearStationInfo();
  // Check for named frequencies
  identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
  // Will need a redraw
  return (true);
}

// Rotate digit
bool doDigit(int8_t dir) {
  bool updated = false;

  // SSB tuning
  if (isSSB()) {
    updated = updateBFO(get_var_local_bfo() + dir * getFreqInputStep(), false);
  }

  //
  // Normal tuning
  //
  else {
    // Tune to a new frequency
    updated = updateFrequency(get_var_local_frequency() + getFreqInputStep() * dir, false);
  }

  if (updated) {
    // Clear current station name and information
    clearStationInfo();
    // Check for named frequencies
    identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
  }

  // Will need a redraw
  return (updated);
}

bool clickFreq(bool shortPress) {
  if (shortPress) {
    bool updated = false;

    // SSB tuning
    if (isSSB()) {
      updated = updateBFO(get_var_local_bfo() - (get_var_local_frequency() * 1000 + get_var_local_bfo()) % getFreqInputStep(), false);
    } else {
      // Normal tuning
      updated = updateFrequency(get_var_local_frequency() - get_var_local_frequency() % getFreqInputStep(), false);
    }

    if (updated) {
      // Clear current station name and information
      clearStationInfo();
      // Check for named frequencies
      identifyFrequency(get_var_local_frequency() + get_var_local_bfo() / 1000);
    }
    return true;
  }
  return false;
}

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

void updatePageLocalRadio() {
  uint32_t currentTime = millis();
  int32_t local_index = get_var_local_index();

  if (encoderCount1) {
    if (local_index < 0) {
      int32_t local_seek_index = get_var_local_seek_index();
      if (local_seek_index == 0) {
        doSeek(-encoderCount1);
      } else if (local_seek_index == 1) {
        doTune(-encoderCount1);
      } else {
        doSeekMemory(-encoderCount1);
      }
    } else {
      set_var_local_index(wrap_range(local_index, -encoderCount1, 0, 3));
    }
    eepromRequestSave();
  }

  if (encoderCount2) {
    if (local_index < 0) {
      doVolume(encoderCount2);
    } else if (local_index == 0) {
      doMemory(-encoderCount2);
    } else if (local_index == 1) {
      doBand(-encoderCount2);
    } else if (local_index == 2) {
      doMode(-encoderCount2);
    } else if (local_index == 3) {
      doStep(-encoderCount2);
    }
    eepromRequestSave();
  }

  if (pb1st.isPressed) {
    //
  }

  if (pb1st.wasClicked) {
    set_var_local_index(local_index < 0 ? 0 : -1);
  }

  if (pb1st.wasShortPressed || pb1st.isLongPressed) {
    set_var_local_index(-1);
    eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
    set_var_page_name(PageName_Main);
  }

  if (pb2st.isPressed) {
    //
  }

  if (pb2st.wasClicked) {
    if (local_index >= 0) {
      if (local_index == 0 && get_var_local_seek_index() > 1) {
        doSaveMemory();
      } else {
        set_var_local_index(-1);
      }
    }
  }

  if (pb2st.wasShortPressed || pb2st.isLongPressed) {
    set_var_local_index(-1);
    eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
    set_var_page_name(PageName_Main);
  }

  if ((currentTime - elapsedRSSI) > MIN_ELAPSED_RSSI_TIME) {
    processRssiSnr();
    elapsedRSSI = currentTime;
  }
}
