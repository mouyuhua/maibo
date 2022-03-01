#include"HR_chart.h"

extern lv_group_t * group;

lv_obj_t * chart_cont, * HR_chart;
lv_chart_series_t * HR_series;
lv_coord_t HR_points[11] = {78,89,88,92,110,96,120,119,65,76};

void HR_chart_create(void)
{
    chart_cont = lv_cont_create(lv_scr_act(), NULL);
    //lv_group_add_obj(group, chart_cont);
    lv_obj_set_size(chart_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    HR_chart = lv_chart_create(chart_cont, NULL);
    lv_chart_set_type(HR_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(HR_chart, 0, 0);
    lv_chart_set_x_tick_texts(HR_chart, "0\n1\n2\n3\n4\n5", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_x_tick_length(HR_chart, 2, 1);
    lv_chart_set_y_tick_texts(HR_chart, "\n120\n110\n100\n90\n80\n70\n60", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_y_tick_length(HR_chart, 2, 0);
    lv_chart_set_range(HR_chart, 60, 120);
    lv_chart_set_margin(HR_chart, 30);

    HR_series = lv_chart_add_series(HR_chart, LV_COLOR_BLACK);
    lv_chart_set_points(HR_chart, HR_series, HR_points);

    lv_obj_set_size(HR_chart, LV_HOR_RES_MAX-30, LV_VER_RES_MAX-5);
    lv_cont_set_layout(chart_cont, LV_LAYOUT_COL_R);

}
