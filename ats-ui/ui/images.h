#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_index_0;
extern const lv_img_dsc_t img_index_1;
extern const lv_img_dsc_t img_index_2;
extern const lv_img_dsc_t img_index_3;
extern const lv_img_dsc_t img_battery_full;
extern const lv_img_dsc_t img_bluetooth;
extern const lv_img_dsc_t img_home;
extern const lv_img_dsc_t img_speaker;
extern const lv_img_dsc_t img_wifi;
extern const lv_img_dsc_t img_radio;
extern const lv_img_dsc_t img_favorite;
extern const lv_img_dsc_t img_search;
extern const lv_img_dsc_t img_manual;
extern const lv_img_dsc_t img_step;
extern const lv_img_dsc_t img_band;
extern const lv_img_dsc_t img_config;
extern const lv_img_dsc_t img_mode;
extern const lv_img_dsc_t img_save;
extern const lv_img_dsc_t img_width;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[19];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/