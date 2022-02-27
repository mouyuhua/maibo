#ifndef MENU_H
#define MENU_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#define LV_CONF_INCLUDE_SIMPLE
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "lvgl.h"
#include "../lv_ex_conf.h"
#endif

#if LV_USE_DEMO

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
enum change_command{forward, next};
typedef enum change_command page_change_command;
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a demo application
 */
void menu_ui_create(void);
void del_menu_ui(void);
void change_page(page_change_command command);
void app_load(void);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // APP_UI_H
