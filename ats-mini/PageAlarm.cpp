#include "Common.h"
#include "PageAlarm.h"

using namespace eez;
using namespace eez::flow;

void updatePageAlarm()
{
  if (encoderCount1)
  {
    //
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
    //
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
    //
  }

  if (pb2st.wasShortPressed || pb2st.isLongPressed)
  {
    eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
    set_var_page_name(PageName_Main);
  }
}
