#include"menu.h"

#define LEFT_LMETER_BASE_VALUE 100
#define RIGHT_LMETER_BASE_VALUE 0
#define MAXPAGE 3

lv_obj_t *menu_cont;
lv_obj_t *menu_page, *lmeter_tag_left_cont, *lmeter_tag_right_cont, *lmeter_tag_left, *lmeter_tag_right;
lv_obj_t *HR_cont, *BP_cont, *setting_cont;
lv_obj_t *HR_img, *HR_title;
lv_obj_t *BP_img, *BP_title;
lv_obj_t *setting_img, *setting_title;

lv_style_t lmeter_tag_style;

static uint8_t load_value = 0;

void del_menu_ui(void)
{
    lv_obj_del_async(menu_cont);
}

void change_page(page_change_command command)
{
    static uint8_t page_num = 0;
    if(command == next)
    {
        switch (page_num)
        {
        case 0:
            lv_page_focus(menu_page, HR_cont, LV_ANIM_OFF);
            page_num++;
            break;
        case 1:
            lv_page_focus(menu_page, BP_cont, LV_ANIM_OFF);
            page_num++;
            break;
        case 2:
            lv_page_focus(menu_cont, setting_cont, LV_ANIM_OFF);
            page_num=0;
            break;
        default:
            break;
        }
    }
    else if(command == forward)
    {
        switch (page_num)
        {
        case 0:
            lv_page_focus(menu_page, HR_cont, LV_ANIM_ON);
            page_num = MAXPAGE-1;
            break;
        case 1:
            lv_page_focus(menu_page, BP_cont, LV_ANIM_ON);
            page_num--;
            break;
        case 2:
            lv_page_focus(menu_cont, setting_cont, LV_ANIM_ON);
            page_num--;
            break;
        default:
            break;
        }
    }
}

void app_load(void)
{
    load_value += 10;
    lv_lmeter_set_value(lmeter_tag_left, LEFT_LMETER_BASE_VALUE+load_value);
    lv_lmeter_set_value(lmeter_tag_right, RIGHT_LMETER_BASE_VALUE+load_value);
    if(load_value>=100)
    {
        load_value = 0;
    }
}

void menu_ui_create(void)
{
    lv_style_copy(&lmeter_tag_style, &lv_style_plain_color);

    menu_cont = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_size(menu_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);

    lmeter_tag_style.body.main_color=LV_COLOR_BLACK;
    lmeter_tag_style.body.grad_color=LV_COLOR_BLACK;
    lmeter_tag_style.line.color = LV_COLOR_WHITE;
    lmeter_tag_style.line.width = 1;
    lmeter_tag_style.body.padding.left = 5;
    lmeter_tag_left_cont = lv_cont_create(menu_cont, NULL);
    lv_obj_set_size(lmeter_tag_left_cont, LV_HOR_RES_MAX/4, LV_VER_RES_MAX);
    menu_page = lv_page_create(menu_cont, NULL);
    lv_page_set_sb_mode(menu_page, LV_SB_MODE_HIDE);
    lv_obj_set_size(menu_page, LV_HOR_RES_MAX/2, LV_VER_RES_MAX);
    lmeter_tag_right_cont = lv_cont_create(menu_cont, lmeter_tag_left_cont);
    lv_obj_set_size(lmeter_tag_right_cont, LV_HOR_RES_MAX/4, LV_VER_RES_MAX);

    lmeter_tag_left = lv_lmeter_create(lmeter_tag_left_cont, NULL);
    lv_obj_set_size(lmeter_tag_left, LV_HOR_RES_MAX/2, LV_HOR_RES_MAX/2);
    lv_lmeter_set_range(lmeter_tag_left, 0, 200);
    lv_lmeter_set_value(lmeter_tag_left, LEFT_LMETER_BASE_VALUE+0);
    lv_lmeter_set_scale(lmeter_tag_left, 360, 50);
    lv_lmeter_set_style(lmeter_tag_left, LV_LMETER_STYLE_MAIN, &lmeter_tag_style);
    lv_obj_align(lmeter_tag_left, NULL, LV_ALIGN_IN_LEFT_MID, -LV_HOR_RES_MAX/4, 0);

    lmeter_tag_right = lv_lmeter_create(lmeter_tag_right_cont, lmeter_tag_left);
    lv_obj_set_size(lmeter_tag_right, LV_HOR_RES_MAX/2, LV_HOR_RES_MAX/2);
    lv_lmeter_set_range(lmeter_tag_right, 0, 200);
    lv_lmeter_set_value(lmeter_tag_right, RIGHT_LMETER_BASE_VALUE);
    lv_lmeter_set_scale(lmeter_tag_right, 360, 50);
    lv_lmeter_set_style(lmeter_tag_right, LV_LMETER_STYLE_MAIN, &lmeter_tag_style);
    lv_obj_align(lmeter_tag_right, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);

    HR_cont = lv_cont_create(menu_page, NULL);
    HR_img = lv_label_create(HR_cont, NULL);
    HR_title = lv_label_create(HR_cont, HR_img);
    lv_label_set_text(HR_img, "HR_IMG");
    lv_label_set_text(HR_title, "HR_TITLE");
    lv_obj_set_size(HR_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(HR_cont, LV_LAYOUT_CENTER);

    BP_cont = lv_cont_create(menu_page, NULL);
    BP_img = lv_label_create(BP_cont, HR_img);
    BP_title = lv_label_create(BP_cont, HR_title);
    lv_label_set_text(BP_img, "BP_IMG");
    lv_label_set_text(BP_title, "BP_TITLE");
    lv_obj_set_size(BP_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(BP_cont, LV_LAYOUT_CENTER);

    setting_cont = lv_cont_create(menu_page, BP_cont);
    setting_img = lv_label_create(setting_cont, BP_img);
    setting_title = lv_label_create(setting_cont, BP_title);
    lv_label_set_text(setting_img, "SETTING_IMG");
    lv_label_set_text(setting_title, "SETTING_TITLE");
    lv_obj_set_size(setting_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(setting_cont, LV_LAYOUT_CENTER);

    lv_page_set_scrl_layout(menu_page, LV_LAYOUT_ROW_M);

    lv_cont_set_layout(menu_cont, LV_LAYOUT_ROW_M);

    //lv_task_create(del_menu_ui, 3000, LV_TASK_PRIO_HIGHEST, NULL);

}

