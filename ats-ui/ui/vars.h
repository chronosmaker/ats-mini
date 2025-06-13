#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

typedef enum {
    PageName_Welcome = 0,
    PageName_Main = 1,
    PageName_LocalRadio = 2,
    PageName_NetRadio = 3,
    PageName_Alarm = 4,
    PageName_Setting = 5,
    PageName_SettingWiFi = 6,
    PageName_SettingBluetooth = 7,
    PageName_SettingTime = 8,
    PageName_SettingScreen = 9,
    PageName_SettingSleep = 10,
    PageName_SettingOperation = 11,
    PageName_SettingAbout = 12
} PageName;

typedef enum {
    LocalMode_FM = 0,
    LocalMode_LSB = 1,
    LocalMode_USB = 2,
    LocalMode_AM = 3
} LocalMode;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern PageName get_var_page_name();
extern void set_var_page_name(PageName value);
extern int32_t get_var_page_index();
extern void set_var_page_index(int32_t value);
extern int32_t get_var_page_index_dir();
extern void set_var_page_index_dir(int32_t value);
extern int32_t get_var_setting_index();
extern void set_var_setting_index(int32_t value);
extern int32_t get_var_setting_detail_index();
extern void set_var_setting_detail_index(int32_t value);
extern int32_t get_var_screen_brightness();
extern void set_var_screen_brightness(int32_t value);
extern int32_t get_var_screen_brightness_min();
extern void set_var_screen_brightness_min(int32_t value);
extern int32_t get_var_screen_brightness_max();
extern void set_var_screen_brightness_max(int32_t value);
extern int32_t get_var_screen_off_time();
extern void set_var_screen_off_time(int32_t value);
extern int32_t get_var_screen_off_time_min();
extern void set_var_screen_off_time_min(int32_t value);
extern int32_t get_var_screen_off_time_max();
extern void set_var_screen_off_time_max(int32_t value);
extern const char *get_var_system_time();
extern void set_var_system_time(const char *value);
extern int32_t get_var_system_mode();
extern void set_var_system_mode(int32_t value);
extern int32_t get_var_sound_mode();
extern void set_var_sound_mode(int32_t value);
extern int32_t get_var_speaker_volume();
extern void set_var_speaker_volume(int32_t value);
extern int32_t get_var_earphone_volume();
extern void set_var_earphone_volume(int32_t value);
extern int32_t get_var_local_index();
extern void set_var_local_index(int32_t value);
extern LocalMode get_var_local_mode();
extern void set_var_local_mode(LocalMode value);
extern int32_t get_var_local_frequency();
extern void set_var_local_frequency(int32_t value);
extern int32_t get_var_local_snr();
extern void set_var_local_snr(int32_t value);
extern int32_t get_var_local_rssi();
extern void set_var_local_rssi(int32_t value);
extern int32_t get_var_local_squelch();
extern void set_var_local_squelch(int32_t value);
extern bool get_var_local_squelch_cutoff();
extern void set_var_local_squelch_cutoff(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/