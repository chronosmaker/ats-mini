#include "Common.h"
#include "PageSetting.h"

using namespace eez;
using namespace eez::flow;

void updatePageSetting()
{
  if (encoderCount1)
  {
    int32_t setting_index_count = 6;
    int32_t setting_index = get_var_setting_index() - encoderCount1;
    if (setting_index < 0)
    {
      setting_index = setting_index_count;
    }
    else if (setting_index > setting_index_count)
    {
      setting_index = 0;
    }
    set_var_setting_index(setting_index);
  }

  if (encoderCount2)
  {
    //
  }

  if (pb1st.isPressed)
  {
    //
  }

  if (pb1st.wasClicked)
  {
    switch (get_var_setting_index())
    {
    case 0:
      set_var_page_name(PageName_SettingWiFi);
      break;
    case 1:
      set_var_page_name(PageName_SettingBluetooth);
      break;
    case 2:
      set_var_page_name(PageName_SettingTime);
      break;
    case 3:
      set_var_page_name(PageName_SettingScreen);
      break;
    case 4:
      set_var_page_name(PageName_SettingSleep);
      break;
    case 5:
      set_var_page_name(PageName_SettingOperation);
      break;
    case 6:
      set_var_page_name(PageName_SettingAbout);
      break;
    default:
      break;
    }
    set_var_setting_detail_index(0);
  }

  if (pb1st.wasShortPressed || pb1st.isLongPressed)
  {
    set_var_setting_detail_index(-2);
    set_var_page_name(PageName_Main);
    eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
  }

  if (pb2st.isPressed)
  {
    //
  }

  if (pb2st.wasClicked)
  {
    //
  }

  if (pb2st.wasShortPressed)
  {
    //
  }

  if (pb2st.isLongPressed)
  {
    //
  }
}
