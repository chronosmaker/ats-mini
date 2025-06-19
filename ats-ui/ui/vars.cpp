#include <string>
#include "ui.h"
#include "vars.h"

using namespace eez;
using namespace eez::flow;

PageName page_name = PageName_Welcome;

extern "C" PageName get_var_page_name()
{
    return page_name;
}

extern "C" void set_var_page_name(PageName value)
{
    page_name = value;
}

int32_t page_index = 0;

extern "C" int32_t get_var_page_index()
{
    return page_index;
}

extern "C" void set_var_page_index(int32_t value)
{
    page_index = value;
}

int32_t page_index_dir = 0;

extern "C" int32_t get_var_page_index_dir()
{
    return page_index_dir;
}

extern "C" void set_var_page_index_dir(int32_t value)
{
    page_index_dir = value;
}

int32_t setting_index = 0;

extern "C" int32_t get_var_setting_index()
{
    return setting_index;
}

extern "C" void set_var_setting_index(int32_t value)
{
    setting_index = value;
}

int32_t setting_detail_index = -2;

extern "C" int32_t get_var_setting_detail_index()
{
    return setting_detail_index;
}

extern "C" void set_var_setting_detail_index(int32_t value)
{
    setting_detail_index = value;
}

int32_t screen_brightness = 10;

extern "C" int32_t get_var_screen_brightness()
{
    return screen_brightness;
}

extern "C" void set_var_screen_brightness(int32_t value)
{
    screen_brightness = value;
}

int32_t screen_brightness_min = 1;

extern "C" int32_t get_var_screen_brightness_min()
{
    return screen_brightness_min;
}

extern "C" void set_var_screen_brightness_min(int32_t value)
{
    screen_brightness_min = value;
}

int32_t screen_brightness_max = 20;

extern "C" int32_t get_var_screen_brightness_max()
{
    return screen_brightness_max;
}

extern "C" void set_var_screen_brightness_max(int32_t value)
{
    screen_brightness_max = value;
}

int32_t screen_off_time = 0;

extern "C" int32_t get_var_screen_off_time()
{
    return screen_off_time;
}

extern "C" void set_var_screen_off_time(int32_t value)
{
    screen_off_time = value;
}

int32_t screen_off_time_min = 0;

extern "C" int32_t get_var_screen_off_time_min()
{
    return screen_off_time_min;
}

extern "C" void set_var_screen_off_time_min(int32_t value)
{
    screen_off_time_min = value;
}

int32_t screen_off_time_max = 240;

extern "C" int32_t get_var_screen_off_time_max()
{
    return screen_off_time_max;
}

extern "C" void set_var_screen_off_time_max(int32_t value)
{
    screen_off_time_max = value;
}

std::string system_time = "00:00";

extern "C" const char *get_var_system_time()
{
    return system_time.c_str();
}

extern "C" void set_var_system_time(const char *value)
{
    system_time = value;
}

int32_t system_mode = -1;

extern "C" int32_t get_var_system_mode()
{
    return system_mode;
}

extern "C" void set_var_system_mode(int32_t value)
{
    system_mode = value;
}

int32_t sound_mode = 0;

extern "C" int32_t get_var_sound_mode()
{
    return sound_mode;
}

extern "C" void set_var_sound_mode(int32_t value)
{
    sound_mode = value;
}

int32_t speaker_volume = 15;

extern "C" int32_t get_var_speaker_volume()
{
    return speaker_volume;
}

extern "C" void set_var_speaker_volume(int32_t value)
{
    speaker_volume = value;
}

int32_t earphone_volume = 15;

extern "C" int32_t get_var_earphone_volume()
{
    return earphone_volume;
}

extern "C" void set_var_earphone_volume(int32_t value)
{
    earphone_volume = value;
}

int32_t local_index = -1;

extern "C" int32_t get_var_local_index()
{
    return local_index;
}

extern "C" void set_var_local_index(int32_t value)
{
    local_index = value;
}

int32_t local_seek_index = 0;

extern "C" int32_t get_var_local_seek_index()
{
    return local_seek_index;
}

extern "C" void set_var_local_seek_index(int32_t value)
{
    local_seek_index = value;
}

int32_t local_band_index = 0;

extern "C" int32_t get_var_local_band_index()
{
    return local_band_index;
}

extern "C" void set_var_local_band_index(int32_t value)
{
    local_band_index = value;
}

int32_t local_mode_index = 0;

extern "C" int32_t get_var_local_mode_index()
{
    return local_mode_index;
}

extern "C" void set_var_local_mode_index(int32_t value)
{
    local_mode_index = value;
}

int32_t local_step_index = 0;

extern "C" int32_t get_var_local_step_index()
{
    return local_step_index;
}

extern "C" void set_var_local_step_index(int32_t value)
{
    local_step_index = value;
}

int32_t local_bandwidth_index = 0;

extern "C" int32_t get_var_local_bandwidth_index()
{
    return local_bandwidth_index;
}

extern "C" void set_var_local_bandwidth_index(int32_t value)
{
    local_bandwidth_index = value;
}

int32_t local_region_index = 0;

extern "C" int32_t get_var_local_region_index()
{
    return local_region_index;
}

extern "C" void set_var_local_region_index(int32_t value)
{
    local_region_index = value;
}

int32_t local_frequency = 0;

extern "C" int32_t get_var_local_frequency()
{
    return local_frequency;
}

extern "C" void set_var_local_frequency(int32_t value)
{
    local_frequency = value;
}

int32_t local_snr = 0;

extern "C" int32_t get_var_local_snr()
{
    return local_snr;
}

extern "C" void set_var_local_snr(int32_t value)
{
    local_snr = value;
}

int32_t local_rssi = 0;

extern "C" int32_t get_var_local_rssi()
{
    return local_rssi;
}

extern "C" void set_var_local_rssi(int32_t value)
{
    local_rssi = value;
}

int32_t local_snr_bar = 0;

extern "C" int32_t get_var_local_snr_bar()
{
    return local_snr_bar;
}

extern "C" void set_var_local_snr_bar(int32_t value)
{
    local_snr_bar = value;
}

int32_t local_rssi_bar = 0;

extern "C" int32_t get_var_local_rssi_bar()
{
    return local_rssi_bar;
}

extern "C" void set_var_local_rssi_bar(int32_t value)
{
    local_rssi_bar = value;
}

int32_t local_squelch = 0;

extern "C" int32_t get_var_local_squelch()
{
    return local_squelch;
}

extern "C" void set_var_local_squelch(int32_t value)
{
    local_squelch = value;
}

bool local_squelch_cutoff = false;

extern "C" bool get_var_local_squelch_cutoff()
{
    return local_squelch_cutoff;
}

extern "C" void set_var_local_squelch_cutoff(bool value)
{
    local_squelch_cutoff = value;
}
