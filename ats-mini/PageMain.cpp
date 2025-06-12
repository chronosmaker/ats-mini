#include "Common.h"
#include "Utils.h"
#include "Menu.h"
#include "PageMain.h"

using namespace eez;
using namespace eez::flow;

void updatePageMain()
{
  if (encoderCount1)
  {
    int32_t page_index_count = 3;
    int32_t page_index = get_var_page_index() + encoderCount1;
    if (page_index < 0)
    {
      page_index = page_index_count;
    }
    else if (page_index > page_index_count)
    {
      page_index = 0;
    }
    set_var_page_index(page_index);
    set_var_page_index_dir(encoderCount1);
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
    switch (get_var_page_index())
    {
    case 0:
      eez_flow_set_screen(SCREEN_ID_LOCAL_RADIO, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
      set_var_page_name(PageName_LocalRadio);
      break;
    case 1:
      eez_flow_set_screen(SCREEN_ID_NET_RADIO, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
      set_var_page_name(PageName_NetRadio);
      break;
    case 2:
      eez_flow_set_screen(SCREEN_ID_ALARM, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
      set_var_page_name(PageName_Alarm);
      break;
    case 3:
      eez_flow_set_screen(SCREEN_ID_SETTING, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
      set_var_page_name(PageName_Setting);
      break;
    default:
      break;
    }
  }

  if (pb1st.wasShortPressed)
  {
    //
  }

  if (pb1st.isLongPressed)
  {
    //
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
