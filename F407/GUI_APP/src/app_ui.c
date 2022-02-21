#include"app_ui.h"
#include"usart.h"
#include"self_functions.h"

#define P_TAG "\xEE\x99\xA3"
#define LBP_TAG "\xEE\xA2\x9B"
#define HBP_TAG "\xEE\x98\xA8"

lv_coord_t height, width;

lv_task_t *task_time_refresh, *task_time_set, *task_sta_refresh;

lv_obj_t* scr, *page1;
lv_obj_t* times_cont;
lv_obj_t* time_cont;
lv_obj_t* time_HH,* time_MM,* time_point;
lv_obj_t* date_cont;
lv_obj_t* date_year,* date_month,* date_day,* date_point_1,* date_point_2;
lv_obj_t* sta_cont;
lv_obj_t* P_cont,* P_tag,* P_num;
lv_obj_t* HBP_cont,* HBP_tag,* HBP_num;
lv_obj_t* LBP_cont,* LBP_tag,* LBP_num;

lv_style_t page1_bg_style;
lv_style_t page1_scrl_style;
lv_style_t time_cont_style, day_cont_style;
lv_style_t time_style, iconfont_style, iconfont_P;

uint8_t num_P[]="***", num_HBP[]="***", num_LBP[]="***";
uint8_t P=000, HBP=000, LBP=000;
uint8_t num_HH[]="21", num_MM[]="21";
uint8_t HH=14, MM=40, second=0;
uint8_t num_year[]="2021", num_month[]="05", num_day[]="21";
uint16_t year=2021;
uint8_t month=5, day=21;

void time_refresh(void)
{
    second++;
    if(second>=60)
    {
        second=0;
        MM+=1;
        if(MM>=60)
        {
            MM=0;
            HH++;
            if(HH>=24)
            {
                HH=0;
                day++;
                if(day>month_days(year, month))
                {
                    day=1;
                    month++;
                    if(month>12)
                    {
                        month=1;
                        year++;
                        num2str(year, num_year, 4);
                        lv_label_set_text(date_year, num_year);
                    }
                    num2str(month, num_month, 2);
                    lv_label_set_text(date_month, num_month);
                }
                num2str(day, num_day, 2);
                lv_label_set_text(date_day, num_day);
            }
            num2str(HH, num_HH, 2);
            lv_label_set_text(time_HH, num_HH);
        }
        num2str(MM, num_MM, 2);
        lv_label_set_text(time_MM, num_MM);
    }
}

void sta_refresh(void)
{
    uint8_t data_len, i;
    if(USART_RX_STA&0x8000)
    {
        data_len = USART_RX_STA&0x3fff;
        for(i=1; i<data_len; i++)
        {
            switch (i)
            {
            case 1:
								// printf("HBP_num:%d\t", USART_RX_BUF[i]);
                num2str(USART_RX_BUF[i], num_HBP, 3);
                lv_label_set_text(HBP_num, num_HBP);
                // printf("HBP:%s\n", num_HBP);
                break;
            case 2:
                num2str(USART_RX_BUF[i], num_LBP, 3);
                lv_label_set_text(LBP_num, num_LBP);
                // printf("LBP:%s\n", num_LBP);
                break;
            case 3:
                num2str(USART_RX_BUF[i], num_P, 3);
                lv_label_set_text(P_num, num_P);
                // printf("P:%s\n", num_P);
                break;           
            default:
                break;
            }
        }
        USART_RX_STA = 0;
    }
}

void luck_ui(void)
{
    //样式创建
    lv_style_copy(&page1_bg_style, &lv_style_plain);
    lv_style_copy(&page1_scrl_style, &lv_style_plain);
    lv_style_copy(&time_cont_style, &lv_style_plain);
    lv_style_copy(&day_cont_style, &lv_style_plain);
    lv_style_copy(&time_style, &lv_style_plain);
    lv_style_copy(&iconfont_style, &lv_style_plain);
    lv_style_copy(&iconfont_P, &lv_style_plain);

    //基本ui创建
    page1 = lv_page_create(scr, NULL);

    times_cont = lv_cont_create(page1, NULL);
    time_cont = lv_cont_create(times_cont, NULL);
    time_HH = lv_label_create(time_cont, NULL);
    time_point = lv_label_create(time_cont, time_HH);
    time_MM = lv_label_create(time_cont,time_HH);

    date_cont = lv_cont_create(times_cont, time_cont);
    date_year = lv_label_create(date_cont, time_HH);
    date_point_1 = lv_label_create(date_cont, time_HH);
    date_month = lv_label_create(date_cont, time_HH);
    date_point_2 = lv_label_create(date_cont, time_HH);
    date_day = lv_label_create(date_cont, time_HH);


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
    time_style.text.font = &lv_font_roboto_28;
	num2str(HH, num_HH, 2);
    lv_label_set_text(time_HH, num_HH);
    lv_label_set_style(time_HH, LV_LABEL_STYLE_MAIN, &time_style);
    lv_label_set_text(time_point, ":");
    lv_label_set_style(time_point, LV_LABEL_STYLE_MAIN, &time_style);
	num2str(MM, num_MM, 2);
    lv_label_set_text(time_MM, num_MM);
    lv_label_set_style(time_MM, LV_LABEL_STYLE_MAIN, &time_style);
    lv_obj_set_size(time_cont, width*2/3-4, height*3/4-10);
    time_cont_style.body.padding.left = (lv_obj_get_width(time_cont)-(lv_obj_get_width(time_HH)+lv_obj_get_width(time_point)+lv_obj_get_width(time_MM)))/2;
    lv_cont_set_style(time_cont, LV_CONT_STYLE_MAIN, &time_cont_style);
    lv_cont_set_layout(time_cont, LV_LAYOUT_ROW_M);

    num2str(year, num_year, 4);
    lv_label_set_text(date_year, num_year);
    lv_label_set_text(date_point_1, "/");
    num2str(month, num_month, 2);
    lv_label_set_text(date_month, num_month);
    lv_label_set_text(date_point_2, "/");
    num2str(day, num_day, 2);
    lv_label_set_text(date_day, num_day);
    lv_obj_set_size(date_cont, width*2/3-4, height/4+3);
    day_cont_style.body.padding.left = (lv_obj_get_width(date_cont)-(lv_obj_get_width(date_year)+lv_obj_get_width(date_month)*2+lv_obj_get_width(date_point_1)*2))/2;
    lv_cont_set_style(date_cont, LV_CONT_STYLE_MAIN, &day_cont_style);
    lv_cont_set_layout(date_cont, LV_LAYOUT_ROW_M);

    lv_cont_set_fit4(times_cont, LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_style(times_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(times_cont, LV_LAYOUT_CENTER);

    //状态表布局及样式设置
    iconfont_P.text.font = &iconfont_16;
    lv_label_set_text(P_tag,P_TAG":");
    lv_label_set_style(P_tag, LV_LABEL_STYLE_MAIN, &iconfont_P);
    num2str(P, num_P, 3);
    lv_label_set_text(P_num, num_P);
    lv_cont_set_style(P_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(P_cont, width/3, height/3-1);
    lv_cont_set_layout(P_cont, LV_LAYOUT_ROW_M);

    iconfont_style.text.font = &iconfont_18;
    lv_label_set_text(HBP_tag,HBP_TAG":");
    lv_label_set_style(HBP_tag, LV_LABEL_STYLE_MAIN, &iconfont_style);
    num2str(HBP, num_HBP, 3);
    lv_label_set_text(HBP_num, num_HBP);
    lv_cont_set_style(HBP_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(HBP_cont, width/3, height/3-1);
    lv_cont_set_layout(HBP_cont, LV_LAYOUT_ROW_M);

    lv_label_set_text(LBP_tag,LBP_TAG":");
    lv_label_set_style(LBP_tag, LV_LABEL_STYLE_MAIN, &iconfont_style);
    num2str(LBP, num_LBP, 3);
    lv_label_set_text(LBP_num, num_LBP);
    lv_cont_set_style(LBP_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_obj_set_size(LBP_cont, width/3, height/3-1);
    lv_cont_set_layout(LBP_cont, LV_LAYOUT_ROW_M);

    lv_cont_set_fit4(sta_cont, LV_FIT_TIGHT, LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_cont_set_style(sta_cont, LV_CONT_STYLE_MAIN, &page1_scrl_style);
    lv_cont_set_layout(sta_cont, LV_LAYOUT_CENTER);

}

void menu_ui(void)
{

}

void main_ui_create(void)
{
    
    scr = lv_scr_act();
    height = lv_obj_get_height(scr);
    width = lv_obj_get_width(scr);
    luck_ui();
    task_time_refresh = lv_task_create(time_refresh, 1000, LV_TASK_PRIO_HIGH, NULL);
    task_sta_refresh = lv_task_create(sta_refresh, 600, LV_TASK_PRIO_HIGHEST, NULL);

}
