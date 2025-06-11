#include "Common.h"
#include "PageSettingScreen.h"

using namespace eez;
using namespace eez::flow;

void updatePageSettingScreen()
{
    if (encoderCount1)
    {
        int32_t detail_index_count = 6;
        int32_t detail_index = get_var_setting_detail_index() - encoderCount1;
        if (detail_index < 0)
        {
            detail_index = 0;
        }
        else if (detail_index > detail_index_count)
        {
            detail_index = detail_index_count;
        }
        set_var_setting_detail_index(detail_index);
    }

    if (encoderCount2)
    {
        switch (get_var_setting_detail_index())
        {
        case 0:
        {
            int32_t brightness = get_var_screen_brightness() - encoderCount2;
            int32_t brightness_min = get_var_screen_brightness_min();
            int32_t brightness_max = get_var_screen_brightness_max();
            if (brightness < brightness_min)
            {
                brightness = brightness_min;
            }
            else if (brightness > brightness_max)
            {
                brightness = brightness_max;
            }
            set_var_screen_brightness(brightness);
            break;
        }
        case 1:
        {
            int32_t off_time = get_var_screen_off_time() - encoderCount2 * 10;
            int32_t off_time_min = get_var_screen_off_time_min();
            int32_t off_time_max = get_var_screen_off_time_max();
            if (off_time < off_time_min)
            {
                off_time = off_time_min;
            }
            else if (off_time > off_time_max)
            {
                off_time = off_time_max;
            }
            set_var_screen_off_time(off_time);
            break;
        }
        default:
            break;
        }
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