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

std::string system_time = "00:00";

extern "C" const char *get_var_system_time()
{
    return system_time.c_str();
}

extern "C" void set_var_system_time(const char *value)
{
    system_time = value;
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
