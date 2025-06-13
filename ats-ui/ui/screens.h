#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *welcome;
    lv_obj_t *main;
    lv_obj_t *local_radio;
    lv_obj_t *net_radio;
    lv_obj_t *alarm;
    lv_obj_t *setting;
    lv_obj_t *main_header;
    lv_obj_t *main_header__time;
    lv_obj_t *main_header__volume;
    lv_obj_t *local_radio_header;
    lv_obj_t *local_radio_header__time;
    lv_obj_t *local_radio_header__volume;
    lv_obj_t *net_radio_header;
    lv_obj_t *net_radio_header__time;
    lv_obj_t *net_radio_header__volume;
    lv_obj_t *alarm_header;
    lv_obj_t *alarm_header__time;
    lv_obj_t *alarm_header__volume;
    lv_obj_t *setting_header;
    lv_obj_t *setting_header__time;
    lv_obj_t *setting_header__volume;
    lv_obj_t *wifi_setting;
    lv_obj_t *bluetooth_setting;
    lv_obj_t *time_setting;
    lv_obj_t *screen_setting;
    lv_obj_t *screen_setting__screen_brightness;
    lv_obj_t *screen_setting__obj0;
    lv_obj_t *screen_setting__obj1;
    lv_obj_t *screen_setting__obj2;
    lv_obj_t *screen_setting__screen_off_time;
    lv_obj_t *screen_setting__obj3;
    lv_obj_t *screen_setting__obj4;
    lv_obj_t *screen_setting__obj5;
    lv_obj_t *sleep_setting;
    lv_obj_t *operation_setting;
    lv_obj_t *about_setting;
    lv_obj_t *title;
    lv_obj_t *subtitle;
    lv_obj_t *index_0;
    lv_obj_t *index_1;
    lv_obj_t *index_2;
    lv_obj_t *index_3;
    lv_obj_t *index_4;
    lv_obj_t *index_5;
    lv_obj_t *local_select;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *setting_detail_select;
    lv_obj_t *setting_detail_wrap;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_WELCOME = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_LOCAL_RADIO = 3,
    SCREEN_ID_NET_RADIO = 4,
    SCREEN_ID_ALARM = 5,
    SCREEN_ID_SETTING = 6,
};

void create_screen_welcome();
void delete_screen_welcome();
void tick_screen_welcome();

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_local_radio();
void delete_screen_local_radio();
void tick_screen_local_radio();

void create_screen_net_radio();
void delete_screen_net_radio();
void tick_screen_net_radio();

void create_screen_alarm();
void delete_screen_alarm();
void tick_screen_alarm();

void create_screen_setting();
void delete_screen_setting();
void tick_screen_setting();

void create_user_widget_header(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_header(void *flowState, int startWidgetIndex);

void create_user_widget_wifi_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_wifi_setting(void *flowState, int startWidgetIndex);

void create_user_widget_bluetooth_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_bluetooth_setting(void *flowState, int startWidgetIndex);

void create_user_widget_time_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_time_setting(void *flowState, int startWidgetIndex);

void create_user_widget_screen_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_screen_setting(void *flowState, int startWidgetIndex);

void create_user_widget_sleep_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_sleep_setting(void *flowState, int startWidgetIndex);

void create_user_widget_operation_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_operation_setting(void *flowState, int startWidgetIndex);

void create_user_widget_about_setting(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_about_setting(void *flowState, int startWidgetIndex);

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/