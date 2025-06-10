#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_setting_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_roller_get_selected(ta);
            assignIntegerProperty(flowState, 2, 3, value, "Failed to assign Selected in Roller widget");
        }
    }
}

static void event_handler_cb_test_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 1, 0, e);
    }
}

static void event_handler_cb_test_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_test_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 1, e);
    }
}

static void event_handler_cb_test_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_test_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_test_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 1, e);
    }
}

static void event_handler_cb_screen_setting_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            assignIntegerProperty(flowState, 4, 5, value, "Failed to assign Value in Slider widget");
        }
    }
}

static void event_handler_cb_screen_setting_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            assignIntegerProperty(flowState, 8, 5, value, "Failed to assign Value in Slider widget");
        }
    }
}

void create_screen_welcome() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.welcome = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.title = obj;
            lv_obj_set_pos(obj, 84, 97);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 0);
            lv_obj_set_style_text_font(obj, &ui_font_cn_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "IMAKER STUDIO");
        }
        {
            // subtitle
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.subtitle = obj;
            lv_obj_set_pos(obj, 84, 120);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 0);
            lv_obj_set_style_text_font(obj, &ui_font_cn_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "RADIO PROJECT");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_WELCOME - 1);
    
    tick_screen_welcome();
}

void delete_screen_welcome() {
    lv_obj_del(objects.welcome);
    objects.welcome = 0;
    objects.title = 0;
    objects.subtitle = 0;
    deletePageFlowState(0);
}

void tick_screen_welcome() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_main() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, getFlowState(flowState, 0), 7);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // index_0
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_0 = obj;
            lv_obj_set_pos(obj, 40, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_0);
            lv_img_set_zoom(obj, 255);
        }
        {
            // index_1
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_1 = obj;
            lv_obj_set_pos(obj, 300, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_1);
            lv_img_set_zoom(obj, 255);
        }
        {
            // index_2
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_2 = obj;
            lv_obj_set_pos(obj, 560, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_2);
            lv_img_set_zoom(obj, 255);
        }
        {
            // index_3
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_3 = obj;
            lv_obj_set_pos(obj, 820, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_3);
            lv_img_set_zoom(obj, 255);
        }
        {
            // index_4
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_4 = obj;
            lv_obj_set_pos(obj, 1080, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_0);
            lv_img_set_zoom(obj, 255);
        }
        {
            // index_5
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.index_5 = obj;
            lv_obj_set_pos(obj, -220, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_index_3);
            lv_img_set_zoom(obj, 255);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 228);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_test(obj, getFlowState(flowState, 8), 9);
        }
    }
    
    tick_screen_main();
}

void delete_screen_main() {
    lv_obj_del(objects.main);
    objects.main = 0;
    objects.header = 0;
    objects.index_0 = 0;
    objects.index_1 = 0;
    objects.index_2 = 0;
    objects.index_3 = 0;
    objects.index_4 = 0;
    objects.index_5 = 0;
    objects.obj0 = 0;
    deletePageFlowState(1);
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    tick_user_widget_header(getFlowState(flowState, 0), 7);
    tick_user_widget_test(getFlowState(flowState, 8), 9);
}

void create_screen_local_radio() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.local_radio = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 121, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "LocalRadio");
        }
        {
            // header_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, getFlowState(flowState, 2), 16);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 228);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_test(obj, getFlowState(flowState, 3), 18);
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_LOCAL_RADIO - 1);
    
    tick_screen_local_radio();
}

void delete_screen_local_radio() {
    lv_obj_del(objects.local_radio);
    objects.local_radio = 0;
    objects.header_1 = 0;
    objects.obj1 = 0;
    deletePageFlowState(2);
}

void tick_screen_local_radio() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    tick_user_widget_header(getFlowState(flowState, 2), 16);
    tick_user_widget_test(getFlowState(flowState, 3), 18);
}

void create_screen_net_radio() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.net_radio = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 122, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "NetRadio");
        }
        {
            // header_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, getFlowState(flowState, 2), 25);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_NET_RADIO - 1);
    
    tick_screen_net_radio();
}

void delete_screen_net_radio() {
    lv_obj_del(objects.net_radio);
    objects.net_radio = 0;
    objects.header_2 = 0;
    deletePageFlowState(3);
}

void tick_screen_net_radio() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    tick_user_widget_header(getFlowState(flowState, 2), 25);
}

void create_screen_alarm() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.alarm = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 122, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Alarm");
        }
        {
            // header_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, getFlowState(flowState, 2), 27);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_ALARM - 1);
    
    tick_screen_alarm();
}

void delete_screen_alarm() {
    lv_obj_del(objects.alarm);
    objects.alarm = 0;
    objects.header_3 = 0;
    deletePageFlowState(4);
}

void tick_screen_alarm() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    tick_user_widget_header(getFlowState(flowState, 2), 27);
}

void create_screen_setting() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.setting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_4 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, getFlowState(flowState, 0), 29);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 0, 26);
            lv_obj_set_size(obj, 76, 214);
            lv_roller_set_options(obj, "WIFI\n蓝牙\n时间\n屏幕\n休眠\n操作\n关于", LV_ROLLER_MODE_INFINITE);
            lv_obj_add_event_cb(obj, event_handler_cb_setting_obj3, LV_EVENT_ALL, flowState);
            lv_obj_set_style_text_font(obj, &ui_font_cn_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e4150), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cn_18, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            // wifi_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_wifi_setting(obj, getFlowState(flowState, 3), 31);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // bluetooth_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.bluetooth_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bluetooth_setting(obj, getFlowState(flowState, 4), 32);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // time_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.time_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_time_setting(obj, getFlowState(flowState, 5), 33);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // screen_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.screen_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_screen_setting(obj, getFlowState(flowState, 6), 34);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // sleep_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sleep_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_sleep_setting(obj, getFlowState(flowState, 7), 45);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // operation_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.operation_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_operation_setting(obj, getFlowState(flowState, 8), 46);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // about_setting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.about_setting = obj;
            lv_obj_set_pos(obj, 80, 26);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_about_setting(obj, getFlowState(flowState, 9), 47);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 0, 228);
            lv_obj_set_size(obj, 320, 24);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_test(obj, getFlowState(flowState, 10), 48);
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_SETTING - 1);
    
    tick_screen_setting();
}

void delete_screen_setting() {
    lv_obj_del(objects.setting);
    objects.setting = 0;
    objects.header_4 = 0;
    objects.obj3 = 0;
    objects.wifi_setting = 0;
    objects.bluetooth_setting = 0;
    objects.time_setting = 0;
    objects.screen_setting = 0;
    objects.sleep_setting = 0;
    objects.operation_setting = 0;
    objects.about_setting = 0;
    objects.obj2 = 0;
    deletePageFlowState(5);
}

void tick_screen_setting() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    tick_user_widget_header(getFlowState(flowState, 0), 29);
    {
        if (!(lv_obj_get_state(objects.obj3) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 2, 3, "Failed to evaluate Selected in Roller widget");
            int32_t cur_val = lv_roller_get_selected(objects.obj3);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj3;
                lv_roller_set_selected(objects.obj3, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wifi_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wifi_setting;
            if (new_val) lv_obj_add_flag(objects.wifi_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wifi_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_wifi_setting(getFlowState(flowState, 3), 31);
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.bluetooth_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.bluetooth_setting;
            if (new_val) lv_obj_add_flag(objects.bluetooth_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.bluetooth_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_bluetooth_setting(getFlowState(flowState, 4), 32);
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.time_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.time_setting;
            if (new_val) lv_obj_add_flag(objects.time_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.time_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_time_setting(getFlowState(flowState, 5), 33);
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.screen_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.screen_setting;
            if (new_val) lv_obj_add_flag(objects.screen_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.screen_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_screen_setting(getFlowState(flowState, 6), 34);
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sleep_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sleep_setting;
            if (new_val) lv_obj_add_flag(objects.sleep_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.sleep_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_sleep_setting(getFlowState(flowState, 7), 45);
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.operation_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.operation_setting;
            if (new_val) lv_obj_add_flag(objects.operation_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.operation_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_operation_setting(getFlowState(flowState, 8), 46);
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.about_setting, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.about_setting;
            if (new_val) lv_obj_add_flag(objects.about_setting, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.about_setting, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_about_setting(getFlowState(flowState, 9), 47);
    tick_user_widget_test(getFlowState(flowState, 10), 48);
}

void create_user_widget_test(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj0, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "e1_-1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 100, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj1, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "e1_1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 50, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj2, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pb1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 170, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj3, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "e2_-1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 270, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj4, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "e2_1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
            lv_obj_set_pos(obj, 220, 0);
            lv_obj_set_size(obj, 50, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_test_obj5, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pb2");
                }
            }
        }
    }
}

void tick_user_widget_test(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_header(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 130, 1);
            lv_obj_set_size(obj, 60, 23);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cn_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 28, 2);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_bluetooth);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 4, 2);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_wifi);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 292, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_battery_full);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 265, 2);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_speaker);
        }
    }
}

void tick_user_widget_header(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    {
        const char *new_val = evalTextProperty(flowState, 1, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_wifi_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 77, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "wifi_setting");
        }
    }
}

void tick_user_widget_wifi_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_bluetooth_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 54, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "bluetooth_setting");
        }
    }
}

void tick_user_widget_bluetooth_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_time_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 74, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "time_setting");
        }
    }
}

void tick_user_widget_time_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_screen_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // screen_setting_wrap
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 280);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // screen_setting_select
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 240, 40);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e4150), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // screen_brightness
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 240, 40);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 11);
                            lv_obj_set_size(obj, 90, 21);
                            lv_obj_set_style_text_font(obj, &ui_font_cn_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "屏幕亮度");
                        }
                        {
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 90, 18);
                            lv_obj_set_size(obj, 110, 5);
                            lv_obj_add_event_cb(obj, event_handler_cb_screen_setting_obj8, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 200, 11);
                            lv_obj_set_size(obj, 40, 20);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cn_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // screen_off_time
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 0, 40);
                    lv_obj_set_size(obj, 240, 40);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 0, 11);
                            lv_obj_set_size(obj, 90, 21);
                            lv_obj_set_style_text_font(obj, &ui_font_cn_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "息屏时间");
                        }
                        {
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 90, 18);
                            lv_obj_set_size(obj, 110, 5);
                            lv_obj_add_event_cb(obj, event_handler_cb_screen_setting_obj11, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff008c8d), LV_PART_KNOB | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 200, 11);
                            lv_obj_set_size(obj, 40, 20);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff81d8cf), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cn_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_screen_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 3, "Failed to evaluate Min in Slider widget");
        int32_t cur_val = lv_slider_get_min_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            int16_t min = new_val;
            int16_t max = lv_slider_get_max_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
            if (min < max) {
                lv_slider_set_range(((lv_obj_t **)&objects)[startWidgetIndex + 4], min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 4, "Failed to evaluate Max in Slider widget");
        int32_t cur_val = lv_slider_get_max_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            int16_t min = lv_slider_get_min_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
            int16_t max = new_val;
            if (min < max) {
                lv_slider_set_range(((lv_obj_t **)&objects)[startWidgetIndex + 4], min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 5, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            lv_slider_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 4], new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 3, "Failed to evaluate Min in Slider widget");
        int32_t cur_val = lv_slider_get_min_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 8];
            int16_t min = new_val;
            int16_t max = lv_slider_get_max_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
            if (min < max) {
                lv_slider_set_range(((lv_obj_t **)&objects)[startWidgetIndex + 8], min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 4, "Failed to evaluate Max in Slider widget");
        int32_t cur_val = lv_slider_get_max_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 8];
            int16_t min = lv_slider_get_min_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
            int16_t max = new_val;
            if (min < max) {
                lv_slider_set_range(((lv_obj_t **)&objects)[startWidgetIndex + 8], min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 5, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 8];
            lv_slider_set_value(((lv_obj_t **)&objects)[startWidgetIndex + 8], new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 9]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 9];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 9], new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_sleep_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 72, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "sleep_setting");
        }
    }
}

void tick_user_widget_sleep_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_operation_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 55, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "operation_setting");
        }
    }
}

void tick_user_widget_operation_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_about_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 69, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "about_setting");
        }
    }
}

void tick_user_widget_about_setting(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}


static const char *screen_names[] = { "Welcome", "Main", "LocalRadio", "NetRadio", "Alarm", "Setting" };
static const char *object_names[] = { "welcome", "main", "local_radio", "net_radio", "alarm", "setting", "header", "header__obj6", "obj0", "obj0__obj0", "obj0__obj1", "obj0__obj2", "obj0__obj3", "obj0__obj4", "obj0__obj5", "header_1", "header_1__obj6", "obj1", "obj1__obj0", "obj1__obj1", "obj1__obj2", "obj1__obj3", "obj1__obj4", "obj1__obj5", "header_2", "header_2__obj6", "header_3", "header_3__obj6", "header_4", "header_4__obj6", "wifi_setting", "bluetooth_setting", "time_setting", "screen_setting", "screen_setting__screen_setting_wrap", "screen_setting__screen_setting_select", "screen_setting__screen_brightness", "screen_setting__obj7", "screen_setting__obj8", "screen_setting__obj9", "screen_setting__screen_off_time", "screen_setting__obj10", "screen_setting__obj11", "screen_setting__obj12", "sleep_setting", "operation_setting", "about_setting", "obj2", "obj2__obj0", "obj2__obj1", "obj2__obj2", "obj2__obj3", "obj2__obj4", "obj2__obj5", "title", "subtitle", "index_0", "index_1", "index_2", "index_3", "index_4", "index_5", "obj3" };


typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_welcome,
    create_screen_main,
    create_screen_local_radio,
    create_screen_net_radio,
    create_screen_alarm,
    create_screen_setting,
};
void create_screen(int screen_index) {
    create_screen_funcs[screen_index]();
}
void create_screen_by_id(enum ScreensEnum screenId) {
    create_screen_funcs[screenId - 1]();
}

typedef void (*delete_screen_func_t)();
delete_screen_func_t delete_screen_funcs[] = {
    delete_screen_welcome,
    delete_screen_main,
    delete_screen_local_radio,
    delete_screen_net_radio,
    delete_screen_alarm,
    delete_screen_setting,
};
void delete_screen(int screen_index) {
    delete_screen_funcs[screen_index]();
}
void delete_screen_by_id(enum ScreensEnum screenId) {
    delete_screen_funcs[screenId - 1]();
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_welcome,
    tick_screen_main,
    tick_screen_local_radio,
    tick_screen_net_radio,
    tick_screen_alarm,
    tick_screen_setting,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    eez_flow_set_create_screen_func(create_screen);
    eez_flow_set_delete_screen_func(delete_screen);
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_welcome();
    create_screen_main();
}
