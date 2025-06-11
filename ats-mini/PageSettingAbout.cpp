#include "Common.h"
#include "PageSettingAbout.h"

using namespace eez;
using namespace eez::flow;

void updatePageSettingAbout()
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
        set_var_setting_detail_index(-2);
        set_var_page_name(PageName_Setting);
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

    if (pb2st.wasShortPressed)
    {
        //
    }

    if (pb2st.isLongPressed)
    {
        //
    }
}