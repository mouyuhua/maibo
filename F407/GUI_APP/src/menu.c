#include"menu.h"
#include"delay.h"
#include"HR_chart.h"
#include"BP_chart.h"
#include"setting.h"

#define SETTING "\xEE\x98\x80"
#define HR_IMG "\xEE\xA2\x9A"
#define BP_IMG "\xEE\x98\x94"

#define LEFT_LMETER_BASE_VALUE 100
#define RIGHT_LMETER_BASE_VALUE 0
#define MAXPAGE 3

extern lv_indev_t * indev_keypad;
extern lv_obj_t *page1;
extern lv_group_t *ui_group;

lv_obj_t *menu_cont;
lv_obj_t *menu_page, *lmeter_tag_left_cont, *lmeter_tag_right_cont, *lmeter_tag_left, *lmeter_tag_right;
lv_obj_t *HR_app_cont, *BP_app_cont, *setting_app_cont;
lv_obj_t *HR_img, *HR_title;
lv_obj_t *BP_img, *BP_title;
lv_obj_t *setting_img, *setting_title;

lv_style_t lmeter_tag_style, img_font_style;

static int8_t load_value = 0;
static int8_t page_num = 0;

void menu_page_focus_cont(uint8_t i)
{
    switch (i)
    {
    case 0:
        lv_page_focus(menu_page, HR_app_cont, LV_ANIM_ON);
        break;
    case 1:
        lv_page_focus(menu_page, BP_app_cont, LV_ANIM_ON);
        break;
    case 2:
        lv_page_focus(menu_page, setting_app_cont, LV_ANIM_ON);
        break;
    default:
        break;
    }
}

static void toluck_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    if(event == LV_EVENT_KEY)
    {
        const uint8_t *key = lv_event_get_data();
        if(*key == LV_KEY_UP)
        {
            lv_group_remove_obj(menu_page);
            lv_group_add_obj(ui_group, page1);
            lv_obj_del_async(menu_cont);
        }
        if(*key == LV_KEY_LEFT)
        {
            page_num--;
            if(page_num < 0) page_num = MAXPAGE-1;
            menu_page_focus_cont((uint8_t)page_num);
        }
        else if(*key == LV_KEY_RIGHT)
        {
            page_num++;
            if(page_num >= MAXPAGE) page_num = 0;
            menu_page_focus_cont((uint8_t)page_num);
        }
        else if(*key == LV_KEY_DOWN)
        {
            load_value += 20;
            lv_lmeter_set_value(lmeter_tag_left, LEFT_LMETER_BASE_VALUE+load_value);
            lv_lmeter_set_value(lmeter_tag_right, RIGHT_LMETER_BASE_VALUE+load_value);
            if(load_value>=100)
            {
                load_value = -20;
                lv_group_remove_obj(menu_page);
                switch (page_num)
                {
                case 0:
                    HR_chart_create();
                    lv_obj_del_async(menu_cont);
                    break;
                case 1:
                    BP_chart_create();
                    lv_obj_del_async(menu_cont);
                    break;
                case 2:
                    main_setting_create();
                    lv_obj_del_async(menu_cont);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void menu_ui_create(void)
{    
    lv_style_copy(&lmeter_tag_style, &lv_style_plain);
    lv_style_copy(&img_font_style, &lv_style_plain);

    menu_cont = lv_cont_create(lv_scr_act(), NULL);
    //lv_group_add_obj(ui_group, menu_cont);
    lv_obj_set_event_cb(menu_cont, toluck_callback);
    lv_obj_set_size(menu_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);

    lmeter_tag_style.body.main_color=LV_COLOR_BLACK;
    lmeter_tag_style.body.grad_color=LV_COLOR_BLACK;
    lmeter_tag_style.line.color = LV_COLOR_WHITE;
    lmeter_tag_style.line.width = 1;
    lmeter_tag_style.body.padding.left = 5;
    lmeter_tag_left_cont = lv_cont_create(menu_cont, NULL);
    lv_obj_set_size(lmeter_tag_left_cont, LV_HOR_RES_MAX/4, LV_VER_RES_MAX);
    menu_page = lv_page_create(menu_cont, NULL);
    lv_group_add_obj(ui_group, menu_page);
    lv_obj_set_event_cb(menu_page, toluck_callback);
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

    HR_app_cont = lv_cont_create(menu_page, NULL);
    HR_img = lv_label_create(HR_app_cont, NULL);
    HR_title = lv_label_create(HR_app_cont, HR_img);
    img_font_style.text.font = &iconfont_18;
    lv_label_set_text(HR_img, HR_IMG);
    lv_label_set_style(HR_img, LV_LABEL_STYLE_MAIN, &img_font_style);
    lv_label_set_text(HR_title, "HR");
    lv_obj_set_size(HR_app_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(HR_app_cont, LV_LAYOUT_CENTER);

    BP_app_cont = lv_cont_create(menu_page, NULL);
    BP_img = lv_label_create(BP_app_cont, HR_img);
    BP_title = lv_label_create(BP_app_cont, HR_title);
    lv_label_set_text(BP_img, BP_IMG);
    lv_label_set_style(BP_img, LV_LABEL_STYLE_MAIN, &img_font_style);
    lv_label_set_text(BP_title, "BP");
    lv_obj_set_size(BP_app_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(BP_app_cont, LV_LAYOUT_CENTER);

    setting_app_cont = lv_cont_create(menu_page, BP_app_cont);
    setting_img = lv_label_create(setting_app_cont, BP_img);
    setting_title = lv_label_create(setting_app_cont, BP_title);
    lv_label_set_text(setting_img, SETTING);
    lv_label_set_style(setting_img, LV_LABEL_STYLE_MAIN, &img_font_style);
    lv_label_set_text(setting_title, "SETTING");
    lv_obj_set_size(setting_app_cont, lv_page_get_fit_width(menu_page), lv_page_get_fit_height(menu_page));
    lv_cont_set_layout(setting_app_cont, LV_LAYOUT_CENTER);

    lv_page_set_scrl_layout(menu_page, LV_LAYOUT_ROW_M);

    lv_cont_set_layout(menu_cont, LV_LAYOUT_ROW_M);

    menu_page_focus_cont((uint8_t)page_num);

}

