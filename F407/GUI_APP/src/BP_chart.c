#include"BP_chart.h"
#include"menu.h"

extern lv_group_t * ui_group;

lv_obj_t * BP_chart_cont, * BP_chart;
lv_chart_series_t * BP_L_series, * BP_H_series;
lv_coord_t BP_L_points[11] = {78,89,88,92,86,81,91,59,65,76}; //60-90
lv_coord_t BP_H_points[11] = {110, 125, 145, 120, 113, 124, 110, 90, 99, 122, 133}; //100-150

int8_t flag=0;

void set_BP_L_chart(void)
{
    lv_chart_set_y_tick_texts(BP_chart, "\n90\n80\n70\n60\n50", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_y_tick_length(BP_chart, 2, 0);
    lv_chart_set_range(BP_chart, 50, 100);
    lv_chart_set_margin(BP_chart, 30);

    BP_L_series = lv_chart_add_series(BP_chart, LV_COLOR_BLACK);
    lv_chart_set_points(BP_chart, BP_L_series, BP_L_points);
}

void clear_BP_L_chart(void)
{
    lv_chart_clear_serie(BP_chart, BP_L_series);
    lv_chart_refresh(BP_chart);
}

void set_BP_H_chart(void)
{
    lv_chart_set_y_tick_texts(BP_chart, "\n150\n140\n130\n120\n110\n100\n90", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_y_tick_length(BP_chart, 2, 0);
    lv_chart_set_range(BP_chart, 90, 160);
    lv_chart_set_margin(BP_chart, 30);

    BP_H_series = lv_chart_add_series(BP_chart, LV_COLOR_BLACK);
    lv_chart_set_points(BP_chart, BP_H_series, BP_H_points);
}

void clear_BP_H_chart(void)
{
    lv_chart_clear_serie(BP_chart, BP_H_series);
    lv_chart_refresh(BP_chart);
}

void change_chart(void)
{
    if(flag>=16)flag=0;
    if(flag<0)flag=15;
    if(flag%2)
    {
        clear_BP_H_chart();
        set_BP_L_chart();
    }else{
        clear_BP_L_chart();
        set_BP_H_chart();
    }
}

static void tomenu_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    if(event == LV_EVENT_KEY)
    {
        const uint8_t *key = lv_event_get_data();
        if(*key == LV_KEY_DOWN)
        {
            lv_group_remove_obj(BP_chart_cont);
            menu_ui_create();
            lv_obj_del_async(BP_chart_cont);
        }
        if(*key == LV_KEY_LEFT)
        {
            flag+=1;
            change_chart();
        }
        if(*key == LV_KEY_RIGHT)
        {
            flag-=1;
            change_chart();
        }
    }
}

void BP_chart_create(void)
{
    BP_chart_cont = lv_cont_create(lv_scr_act(), NULL);
    lv_group_add_obj(ui_group, BP_chart_cont);
    lv_obj_set_event_cb(BP_chart_cont, tomenu_callback);
    lv_obj_set_size(BP_chart_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    BP_chart = lv_chart_create(BP_chart_cont, NULL);
    lv_chart_set_type(BP_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(BP_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_div_line_count(BP_chart, 0, 0);
    lv_chart_set_x_tick_texts(BP_chart, "0\n1\n2\n3\n4\n5", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_x_tick_length(BP_chart, 2, 1);
    lv_chart_set_margin(BP_chart, 30);

    set_BP_L_chart();

    lv_obj_set_size(BP_chart, LV_HOR_RES_MAX-30, LV_VER_RES_MAX-5);
    lv_cont_set_layout(BP_chart_cont, LV_LAYOUT_COL_R);

}
