#include "Common.h"
#include "Menu.h"
#include "LocalRadio.h"
#include "PageLocalRadio.h"

// using namespace eez;
using namespace eez::flow;

#define MIN_ELAPSED_RSSI_TIME 200 // RSSI check uses IN_ELAPSED_RSSI_TIME * 6 = 1.2s

long elapsedRSSI = millis();

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
