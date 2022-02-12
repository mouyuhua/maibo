#include"app_ui.h"

#define P_TAG "\xEE\x99\xA3"
#define LBP_TAG "\xEE\xA2\x9B"
#define HBP_TAG "\xEE\x98\xA8"

lv_coord_t height, width;

lv_obj_t *page1;
lv_obj_t* times_cont;
lv_obj_t* time_cont;
lv_obj_t *time;
lv_obj_t* date_cont;
lv_obj_t *date;
lv_obj_t* sta_cont;
lv_obj_t* P_cont,* P_tag,* P_num;
lv_obj_t* HBP_cont,* HBP_tag,* HBP_num;
lv_obj_t* LBP_cont,* LBP_tag,* LBP_num;

lv_style_t page1_bg_style;
lv_style_t page1_scrl_style;
lv_style_t time_style, iconfont_style, iconfont_P;

void main_ui_create(void)
{
    lv_obj_t* scr = lv_scr_act();
    height = lv_obj_get_height(scr);
    width = lv_obj_get_width(scr);

    //样式创建
    lv_style_copy(&page1_bg_style, &lv_style_plain);
    lv_style_copy(&page1_scrl_style, &lv_style_plain);
    lv_style_copy(&time_style, &lv_style_plain);
    lv_style_copy(&iconfont_style, &lv_style_plain);
    lv_style_copy(&iconfont_P, &lv_style_plain);

    //基本ui创建
    page1 = lv_page_create(scr, NULL);
    times_cont = lv_cont_create(page1, NULL);
    time_cont = lv_cont_create(times_cont, NULL);
    time = lv_label_create(time_cont, NULL);
    date_cont = lv_cont_create(times_cont, time_cont);
    date = lv_label_create(date_cont, time);
    sta_cont = lv_cont_create(page1, time_cont);
    P_cont = lv_cont_create(sta_cont, NULL);
    P_tag = lv_label_create(P_cont, NULL);
    P_num = lv_label_create(P_cont, P_tag);
    HBP_cont = lv_cont_create(sta_cont, P_cont);
    HBP_tag = lv_label_create(HBP_cont, P_tag);
    HBP_num = lv_label_create(HBP_cont, P_tag);
    LBP_cont = lv_cont_create(sta_cont, P_cont);
    LBP_tag = lv_label_create(LBP_cont, P_tag);
    LBP_num = lv_label_create(LBP_cont, P_tag);

    //主容器样式及布局设置
    lv_obj_set_size(page1, width, height);
//    page1_bg_style.body.padding.bottom = 0;
//    page1_bg_style.body.padding.top = 0;
//    page1_bg_style.body.padding.left = 0;
//    page1_bg_style.body.padding.right = 0;
    //page1_bg_style.body.padding.inner = 5;
    lv_page_set_style(page1, LV_PAGE_STYLE_BG, &page1_bg_style);
    page1_scrl_style.body.padding.bottom = 0;
    page1_scrl_style.body.padding.top = 0;
    page1_scrl_style.body.padding.left = 0;
    page1_scrl_style.body.padding.right = 0;
    page1_scrl_style.body.padding.inner = 0;
    lv_page_set_style(page1, LV_PAGE_STYLE_SCRL, &page1_scrl_style);
    lv_page_set_scrl_layout(page1, LV_LAYOUT_ROW_M);

    //时间容器布局及样式设置
    // lv_obj_set_size(time, width*2/3, height*3/4);
    time_style.text.font = &lv_font_roboto_22;
    lv_label_set_text(time, "21:21");
    lv_label_set_style(time, LV_LABEL_STYLE_MAIN, &time_style);
    lv_obj_set_size(time_cont, width*2/3-4, height*3/4-10);
    lv_cont_set_style(time_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(time_cont, LV_LAYOUT_CENTER);

    lv_label_set_text(date, "2021/05/21");
    lv_obj_set_size(date_cont, width*2/3-4, height/4+3);
    lv_cont_set_style(date_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(date_cont, LV_LAYOUT_CENTER);

    lv_cont_set_fit4(times_cont, LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_style(times_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(times_cont, LV_LAYOUT_CENTER);

    //状态表布局及样式设置
    iconfont_P.text.font = &iconfont_16;
    lv_label_set_text(P_tag,P_TAG);
    lv_label_set_style(P_tag, LV_LABEL_STYLE_MAIN, &iconfont_P);
    lv_label_set_text(P_num,":000");
    lv_cont_set_style(P_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(P_cont, width/3, height/3-1);
    lv_cont_set_layout(P_cont, LV_LAYOUT_ROW_M);

    iconfont_style.text.font = &iconfont_18;
    lv_label_set_text(HBP_tag,HBP_TAG);
    lv_label_set_style(HBP_tag, LV_LABEL_STYLE_MAIN, &iconfont_style);
    lv_label_set_text(HBP_num,":000");
    lv_cont_set_style(HBP_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(HBP_cont, width/3, height/3-1);
    lv_cont_set_layout(HBP_cont, LV_LAYOUT_ROW_M);

    lv_label_set_text(LBP_tag,LBP_TAG);
    lv_label_set_style(LBP_tag, LV_LABEL_STYLE_MAIN, &iconfont_style);
    lv_label_set_text(LBP_num,":000");
    lv_cont_set_style(LBP_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(LBP_cont, width/3, height/3-1);
    lv_cont_set_layout(LBP_cont, LV_LAYOUT_ROW_M);

    lv_cont_set_fit4(sta_cont, LV_FIT_TIGHT, LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_style(sta_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(sta_cont, LV_LAYOUT_CENTER);


}
