#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_PAGE_NAME = 0
};

// Native global variables

extern int32_t get_var_encoder1_count();
extern void set_var_encoder1_count(int32_t value);
extern int32_t get_var_encoder2_count();
extern void set_var_encoder2_count(int32_t value);
extern bool get_var_pb1_is_pressed();
extern void set_var_pb1_is_pressed(bool value);
extern bool get_var_pb1_was_clicked();
extern void set_var_pb1_was_clicked(bool value);
extern bool get_var_pb1_was_short_pressed();
extern void set_var_pb1_was_short_pressed(bool value);
extern bool get_var_pb1_is_long_pressed();
extern void set_var_pb1_is_long_pressed(bool value);
extern bool get_var_pb2_is_pressed();
extern void set_var_pb2_is_pressed(bool value);
extern bool get_var_pb2_was_clicked();
extern void set_var_pb2_was_clicked(bool value);
extern bool get_var_pb2_was_short_pressed();
extern void set_var_pb2_was_short_pressed(bool value);
extern bool get_var_pb2_is_long_pressed();
extern void set_var_pb2_is_long_pressed(bool value);
extern const char *get_var_system_time();
extern void set_var_system_time(const char *value);
extern int32_t get_var_screen_brightness();
extern void set_var_screen_brightness(int32_t value);
extern int32_t get_var_screen_off_time();
extern void set_var_screen_off_time(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/