#include"setting.h"
#include"menu.h"

LV_IMG_DECLARE(project_link);

lv_group_t * setting_group;
extern lv_indev_t * indev_keypad;
lv_obj_t * setting_cont;
lv_obj_t * menu_back_cont, * time_setting_cont, * data_setting_cont, * sys_info_cont;

lv_obj_t * time_setting_page;
lv_obj_t * time_back_cont, * time_hour_setting_cont, * time_minute_setting_cont, * time_24H_setting_cont;

lv_obj_t * data_setting_page;
lv_obj_t * data_back_cont, * data_year_setting_cont, * data_month_setting_cont, * data_day_setting_cont;

lv_obj_t * sys_info_app_cont;

lv_style_t page_sb_style;

static void backmenu_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    lv_group_del(setting_group);
    menu_ui_create();
    lv_obj_del_async(setting_cont);
}

static void backsetting_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    lv_group_remove_all_objs(setting_group);
    setting_create();
    if(obj == time_back_cont)
    {
        lv_obj_del_async(time_setting_page);
    }
    if(obj == data_back_cont)
    {
        lv_obj_del_async(data_setting_page);
    }
    if(obj == sys_info_app_cont)
    {
        lv_obj_del_async(sys_info_app_cont);
    }
}

static void to_timesetting_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    lv_group_remove_all_objs(setting_group);
    time_setting();
}

static void to_datasetting_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    lv_group_remove_all_objs(setting_group);
    data_setting();
}

static void to_sysinfo_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    lv_group_remove_all_objs(setting_group);
    sys_info();
}

void main_setting_create(void)
{
    setting_group = lv_group_create();
    lv_style_copy(&page_sb_style, &lv_style_plain);
    page_sb_style.body.padding.right = 2;
    page_sb_style.body.padding.inner = 5;
    lv_indev_set_group(indev_keypad, setting_group);
    setting_create();
}

void setting_create(void)
{
    lv_obj_t * setting_page;
    lv_obj_t * menu_back_label, * time_setting_label, * data_setting_label, * sys_info_label;

    setting_cont = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_size(setting_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    setting_page = lv_page_create(setting_cont, NULL);
    lv_page_set_style(setting_page, LV_PAGE_STYLE_SB, &page_sb_style);
    lv_page_set_scrl_layout(setting_page, LV_LAYOUT_COL_M);
    lv_obj_set_size(setting_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);

    menu_back_cont = lv_cont_create(setting_page, NULL);
    lv_obj_set_size(menu_back_cont, lv_page_get_fit_width(setting_page), lv_page_get_fit_height(setting_page)*3/5);
    lv_cont_set_layout(menu_back_cont, LV_LAYOUT_ROW_M);
    menu_back_label = lv_label_create(menu_back_cont, NULL);
    lv_label_set_text(menu_back_label, "back menu");

    time_setting_cont = lv_cont_create(setting_page, setting_page);
    lv_obj_set_size(time_setting_cont, lv_page_get_fit_width(setting_page), lv_page_get_fit_height(setting_page)*3/5);
    lv_cont_set_layout(time_setting_cont, LV_LAYOUT_ROW_M);
    time_setting_label = lv_label_create(time_setting_cont, NULL);
    lv_label_set_text(time_setting_label, "time setting");

    data_setting_cont = lv_cont_create(setting_page, time_setting_cont);
    lv_obj_set_size(data_setting_cont, lv_page_get_fit_width(setting_page), lv_page_get_fit_height(setting_page)*3/5);
    lv_cont_set_layout(data_setting_cont, LV_LAYOUT_ROW_M);
    data_setting_label = lv_label_create(data_setting_cont, time_setting_label);
    lv_label_set_text(data_setting_label, "data setting");

    sys_info_cont = lv_cont_create(setting_page, time_setting_cont);
    lv_obj_set_size(sys_info_cont, lv_page_get_fit_width(setting_page), lv_page_get_fit_height(setting_page)*3/5);
    lv_cont_set_layout(sys_info_cont, LV_LAYOUT_ROW_M);
    sys_info_label = lv_label_create(sys_info_cont, time_setting_label);
    lv_label_set_text(sys_info_label, "system info");

    lv_group_add_obj(setting_group, menu_back_cont);
    lv_group_add_obj(setting_group, time_setting_cont);
    lv_group_add_obj(setting_group, data_setting_cont);
    lv_group_add_obj(setting_group, sys_info_cont);

    lv_obj_set_event_cb(menu_back_cont, backmenu_callback);
    lv_obj_set_event_cb(time_setting_cont, to_timesetting_callback);
    lv_obj_set_event_cb(data_setting_cont, to_datasetting_callback);
    lv_obj_set_event_cb(sys_info_cont, to_sysinfo_callback);
    
}

void time_setting(void)
{
    time_setting_page = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(time_setting_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_page_set_scrl_layout(time_setting_page, LV_LAYOUT_COL_M);

    lv_obj_t * time_back_label;
    time_back_cont = lv_cont_create(time_setting_page, NULL);
    lv_obj_set_size(time_back_cont, lv_page_get_fit_width(time_setting_page), lv_page_get_fit_height(time_setting_page)*4/7);
    time_back_label = lv_label_create(time_back_cont, NULL);
    lv_obj_align(time_back_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(time_back_label, "back");

    lv_obj_t * time_hour_setting_title_label, * time_hour_setting_hour_label;
    time_hour_setting_cont = lv_cont_create(time_setting_page, NULL);
    lv_obj_set_size(time_hour_setting_cont, lv_page_get_fit_width(time_setting_page), lv_page_get_fit_height(time_setting_page)*4/7);
    time_hour_setting_title_label = lv_label_create(time_hour_setting_cont, NULL);
    lv_obj_align(time_hour_setting_title_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(time_hour_setting_title_label, "hour");
    time_hour_setting_hour_label = lv_label_create(time_hour_setting_cont, time_hour_setting_title_label);
    lv_obj_align(time_hour_setting_hour_label, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_label_set_text(time_hour_setting_hour_label, "21");

    lv_obj_t * time_minute_setting_title_label, * time_minute_setting_minute_label;
    time_minute_setting_cont = lv_cont_create(time_setting_page, time_hour_setting_cont);
    lv_obj_set_size(time_minute_setting_cont, lv_page_get_fit_width(time_setting_page), lv_page_get_fit_height(time_setting_page)*4/7);
    time_minute_setting_title_label = lv_label_create(time_minute_setting_cont, time_hour_setting_title_label);
    lv_obj_align(time_minute_setting_title_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(time_minute_setting_title_label, "minute");
    time_minute_setting_minute_label = lv_label_create(time_minute_setting_cont, time_hour_setting_title_label);
    lv_obj_align(time_minute_setting_minute_label, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_label_set_text(time_minute_setting_minute_label, "21");

    lv_obj_t * time_24H_setting_title, * time_24H_setting_switch;
    time_24H_setting_cont = lv_cont_create(time_setting_page, time_hour_setting_cont);
    lv_obj_set_size(time_24H_setting_cont, lv_page_get_fit_width(time_setting_page), lv_page_get_fit_height(time_setting_page)*4/7);
    time_24H_setting_title = lv_label_create(time_24H_setting_cont, time_hour_setting_title_label);
    lv_obj_align(time_24H_setting_title, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(time_24H_setting_title, "24H");
    time_24H_setting_switch = lv_sw_create(time_24H_setting_cont, NULL);
    lv_obj_align(time_24H_setting_switch, NULL, LV_ALIGN_IN_RIGHT_MID, -8, 0);

    lv_group_add_obj(setting_group, time_back_cont);
    lv_group_add_obj(setting_group, time_hour_setting_cont);
    lv_group_add_obj(setting_group, time_minute_setting_cont);
    lv_group_add_obj(setting_group, time_24H_setting_cont);

    lv_obj_set_event_cb(time_back_cont, backsetting_callback);

}

void data_setting(void)
{
    data_setting_page = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(data_setting_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_page_set_scrl_layout(data_setting_page, LV_LAYOUT_COL_M);

    lv_obj_t * data_back_label;
    data_back_cont = lv_cont_create(time_setting_page, NULL);
    lv_obj_set_size(data_back_cont, lv_page_get_fit_width(time_setting_page), lv_page_get_fit_height(time_setting_page)*4/7);
    data_back_label = lv_label_create(data_back_cont, NULL);
    lv_obj_align(data_back_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(data_back_label, "back");

    lv_obj_t * data_year_setting_title_label, * data_year_setting_year_label;
    data_year_setting_cont = lv_cont_create(data_setting_page, NULL);
    lv_obj_set_size(data_year_setting_cont, lv_page_get_fit_width(data_setting_page), lv_page_get_fit_height(data_setting_page)*4/7);
    data_year_setting_title_label = lv_label_create(data_year_setting_cont, NULL);
    lv_obj_align(data_year_setting_title_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(data_year_setting_title_label, "year");
    data_year_setting_year_label = lv_label_create(data_year_setting_cont, data_year_setting_title_label);
    lv_obj_align(data_year_setting_year_label, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_label_set_text(data_year_setting_year_label, "2021");

    lv_obj_t * data_month_setting_title_label, * data_minute_setting_month_label;
    data_month_setting_cont = lv_cont_create(data_setting_page, data_year_setting_cont);
    lv_obj_set_size(data_month_setting_cont, lv_page_get_fit_width(data_setting_page), lv_page_get_fit_height(data_setting_page)*4/7);
    data_month_setting_title_label = lv_label_create(data_month_setting_cont, data_year_setting_title_label);
    lv_obj_align(data_month_setting_title_label, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(data_month_setting_title_label, "month");
    data_minute_setting_month_label = lv_label_create(data_month_setting_cont, data_year_setting_title_label);
    lv_obj_align(data_minute_setting_month_label, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_label_set_text(data_minute_setting_month_label, "05");

    lv_obj_t * data_day_setting_title, * data_day_setting_day_label;
    data_day_setting_cont = lv_cont_create(data_setting_page, data_year_setting_cont);
    lv_obj_set_size(data_day_setting_cont, lv_page_get_fit_width(data_setting_page), lv_page_get_fit_height(data_setting_page)*4/7);
    data_day_setting_title = lv_label_create(data_day_setting_cont, data_year_setting_title_label);
    lv_obj_align(data_day_setting_title, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
    lv_label_set_text(data_day_setting_title, "day");
    data_day_setting_day_label = lv_label_create(data_day_setting_cont, data_year_setting_title_label);
    lv_obj_align(data_day_setting_day_label, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 0);
    lv_label_set_text(data_day_setting_day_label, "21");

    lv_group_add_obj(setting_group, data_back_cont);
    lv_group_add_obj(setting_group, data_year_setting_cont);
    lv_group_add_obj(setting_group, data_month_setting_cont);
    lv_group_add_obj(setting_group, data_day_setting_cont);

    lv_obj_set_event_cb(data_back_cont, backsetting_callback);

}

void sys_info(void)
{
    lv_obj_t * sys_info_label_cont;
    sys_info_app_cont = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_size(sys_info_app_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);

    lv_obj_t * project_link_img;
    project_link_img = lv_img_create(sys_info_app_cont, NULL);
    lv_img_set_src(project_link_img, &project_link);
    lv_obj_align(project_link_img, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    sys_info_label_cont = lv_cont_create(sys_info_app_cont, NULL);
    lv_obj_set_size(sys_info_label_cont, LV_HOR_RES_MAX - 64, LV_VER_RES_MAX);
    lv_cont_set_layout(sys_info_label_cont, LV_LAYOUT_CENTER);
    lv_obj_align(sys_info_label_cont, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_obj_t * sys_info_uiname_label, * sys_info_ver_label;
    sys_info_uiname_label = lv_label_create(sys_info_label_cont, NULL);
    lv_label_set_text(sys_info_uiname_label, "XUI");
    sys_info_ver_label = lv_label_create(sys_info_label_cont, sys_info_uiname_label);
    lv_label_set_text(sys_info_ver_label, "V2.0.0");

    lv_group_add_obj(setting_group, sys_info_app_cont);

    lv_obj_set_event_cb(sys_info_app_cont, backsetting_callback);

}
