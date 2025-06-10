#include <string>
#include "ui.h"
#include "vars.h"

using namespace eez;
using namespace eez::flow;

// extern "C" int32_t get_var_index()
// {
//     return getGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX).int32Value;
// }

// extern "C" void set_var_index(int32_t value)
// {
//     Value temp = getGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX);
//     temp.int32Value = value;
//     setGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX, temp);
// }

// extern "C" int32_t get_var_index_dir()
// {
//     return getGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX_DIR).int32Value;
// }

// extern "C" void set_var_index_dir(int32_t value)
// {
//     Value temp = getGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX_DIR);
//     temp.int32Value = value;
//     setGlobalVariable(FLOW_GLOBAL_VARIABLE_INDEX_DIR, temp);
// }

// int32_t page_level = 0;

// extern "C" int32_t get_var_page_level()
// {
//     return page_level;
// }

// extern "C" void set_var_page_level(int32_t value)
// {
//     page_level = value;
// }

// int32_t setting_menu_index = 0;

// extern "C" int32_t get_var_setting_menu_index()
// {
//     return setting_menu_index;
// }

// extern "C" void set_var_setting_menu_index(int32_t value)
// {
//     setting_menu_index = value;
// }

// int32_t screen_setting_index = 0;

// extern "C" int32_t get_var_screen_setting_index()
// {
//     return screen_setting_index;
// }

// extern "C" void set_var_screen_setting_index(int32_t value)
// {
//     screen_setting_index = value;
// }

int32_t encoder1_count = 0;

extern "C" int32_t get_var_encoder1_count()
{
    return encoder1_count;
}

extern "C" void set_var_encoder1_count(int32_t value)
{
    encoder1_count = value;
}

int32_t encoder2_count = 0;

extern "C" int32_t get_var_encoder2_count()
{
    return encoder2_count;
}

extern "C" void set_var_encoder2_count(int32_t value)
{
    encoder2_count = value;
}

bool pb1_is_pressed = false;

extern "C" bool get_var_pb1_is_pressed()
{
    return pb1_is_pressed;
}

extern "C" void set_var_pb1_is_pressed(bool value)
{
    pb1_is_pressed = value;
}

bool pb1_was_clicked = false;

extern "C" bool get_var_pb1_was_clicked()
{
    return pb1_was_clicked;
}

extern "C" void set_var_pb1_was_clicked(bool value)
{
    pb1_was_clicked = value;
}

bool pb1_was_short_pressed = false;

extern "C" bool get_var_pb1_was_short_pressed()
{
    return pb1_was_short_pressed;
}

extern "C" void set_var_pb1_was_short_pressed(bool value)
{
    pb1_was_short_pressed = value;
}

bool pb1_is_long_pressed = false;

extern "C" bool get_var_pb1_is_long_pressed()
{
    return pb1_is_long_pressed;
}

extern "C" void set_var_pb1_is_long_pressed(bool value)
{
    pb1_is_long_pressed = value;
}

bool pb2_is_pressed = false;

extern "C" bool get_var_pb2_is_pressed()
{
    return pb2_is_pressed;
}

extern "C" void set_var_pb2_is_pressed(bool value)
{
    pb2_is_pressed = value;
}

bool pb2_was_clicked = false;

extern "C" bool get_var_pb2_was_clicked()
{
    return pb2_was_clicked;
}

extern "C" void set_var_pb2_was_clicked(bool value)
{
    pb2_was_clicked = value;
}

bool pb2_was_short_pressed = false;

extern "C" bool get_var_pb2_was_short_pressed()
{
    return pb2_was_short_pressed;
}

extern "C" void set_var_pb2_was_short_pressed(bool value)
{
    pb2_was_short_pressed = value;
}

bool pb2_is_long_pressed = false;

extern "C" bool get_var_pb2_is_long_pressed()
{
    return pb2_is_long_pressed;
}

extern "C" void set_var_pb2_is_long_pressed(bool value)
{
    pb2_is_long_pressed = value;
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

int32_t screen_off_time = 0;

extern "C" int32_t get_var_screen_off_time()
{
    return screen_off_time;
}

extern "C" void set_var_screen_off_time(int32_t value)
{
    screen_off_time = value;
}