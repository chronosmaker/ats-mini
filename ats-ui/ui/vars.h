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
    PageName_LocalRadioConfig = 13,
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

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LOCAL_SEEK_OPTIONS = 0,
    FLOW_GLOBAL_VARIABLE_LOCAL_BAND_OPTIONS = 1,
    FLOW_GLOBAL_VARIABLE_LOCAL_MODE_OPTIONS = 2,
    FLOW_GLOBAL_VARIABLE_LOCAL_FMSTEP_OPTIONS = 3,
    FLOW_GLOBAL_VARIABLE_LOCAL_SSBSTEP_OPTIONS = 4,
    FLOW_GLOBAL_VARIABLE_LOCAL_AMSTEP_OPTIONS = 5,
    FLOW_GLOBAL_VARIABLE_LOCAL_FMBANDWIDTH_OPTIONS = 6,
    FLOW_GLOBAL_VARIABLE_LOCAL_SSBBANDWIDTH_OPTIONS = 7,
    FLOW_GLOBAL_VARIABLE_LOCAL_AMBANDWIDTH_OPTIONS = 8
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
extern int32_t get_var_local_seek_index();
extern void set_var_local_seek_index(int32_t value);
extern int32_t get_var_local_band_index();
extern void set_var_local_band_index(int32_t value);
extern int32_t get_var_local_mode_index();
extern void set_var_local_mode_index(int32_t value);
extern int32_t get_var_local_step_index();
extern void set_var_local_step_index(int32_t value);
extern int32_t get_var_local_bandwidth_index();
extern void set_var_local_bandwidth_index(int32_t value);
extern int32_t get_var_local_region_index();
extern void set_var_local_region_index(int32_t value);
extern int32_t get_var_local_frequency();
extern void set_var_local_frequency(int32_t value);
extern int32_t get_var_local_bfo();
extern void set_var_local_bfo(int32_t value);
extern int32_t get_var_local_snr();
extern void set_var_local_snr(int32_t value);
extern int32_t get_var_local_rssi();
extern void set_var_local_rssi(int32_t value);
extern int32_t get_var_local_snr_bar();
extern void set_var_local_snr_bar(int32_t value);
extern int32_t get_var_local_rssi_bar();
extern void set_var_local_rssi_bar(int32_t value);
extern int32_t get_var_local_squelch();
extern void set_var_local_squelch(int32_t value);
extern bool get_var_local_squelch_cutoff();
extern void set_var_local_squelch_cutoff(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/