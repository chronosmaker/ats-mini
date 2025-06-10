#include "ui.h"
#include "vars.h"
#include "actions.h"
#include "screens.h"

using namespace eez;
using namespace eez::flow;

// extern "C" void action_scroll_to_view(lv_event_t *e)
// {
//     lv_obj_scroll_to_view(e->current_target, LV_ANIM_ON);
// }

// int32_t index_count = 3;

// extern "C" void action_index_prev()
// {
//     int32_t index = get_var_index();
//     set_var_index(index > 0 ? index - 1 : index_count);
//     set_var_index_dir(-1);
// }

// extern "C" void action_index_next()
// {
//     int32_t index = get_var_index();
//     set_var_index(index < index_count ? index + 1 : 0);
//     set_var_index_dir(1);
// }

// extern "C" void action_go_main()
// {
//     set_var_page_level(0);
//     eez_flow_set_screen(SCREEN_ID_MAIN, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0);
// }

// extern "C" void action_go_page()
// {
//     set_var_page_level(1);
//     int32_t index = get_var_index();
//     switch (index)
//     {
//     case 0:
//         eez_flow_set_screen(SCREEN_ID_LOCAL_RADIO, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
//         break;
//     case 1:
//         eez_flow_set_screen(SCREEN_ID_NET_RADIO, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
//         break;
//     case 2:
//         eez_flow_set_screen(SCREEN_ID_ALARM, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
//         break;
//     case 3:
//         eez_flow_set_screen(SCREEN_ID_SETTING, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0);
//         break;
//     default:
//         break;
//     }
// }

// int32_t setting_menu_count = 6;

// extern "C" void action_setting_menu_prev()
// {
//     int32_t index = get_var_setting_menu_index();
//     set_var_setting_menu_index(index > 0 ? index - 1 : setting_menu_count);
// }

// extern "C" void action_setting_menu_next()
// {
//     int32_t index = get_var_setting_menu_index();
//     set_var_setting_menu_index(index < setting_menu_count ? index + 1 : 0);
// }

// int32_t screen_setting_count = 1;

// void screen_setting_scroll_to_view(int32_t target)
// {
//     switch (target)
//     {
//     case 0:
//         lv_obj_scroll_to_view(objects.screen_setting__screen_brightness, LV_ANIM_ON);
//         break;
//     case 1:
//         lv_obj_scroll_to_view(objects.screen_setting__screen_off_time, LV_ANIM_ON);
//         break;
//     default:
//         break;
//     }
// }

// extern "C" void action_screen_setting_prev()
// {
//     int32_t index = get_var_screen_setting_index();
//     int32_t target = index > 0 ? index - 1 : screen_setting_count;
//     set_var_screen_setting_index(target);
//     screen_setting_scroll_to_view(target);
// }

// extern "C" void action_screen_setting_next()
// {
//     int32_t index = get_var_screen_setting_index();
//     int32_t target = index < screen_setting_count ? index + 1 : 0;
//     set_var_screen_setting_index(target);
//     screen_setting_scroll_to_view(target);
// }