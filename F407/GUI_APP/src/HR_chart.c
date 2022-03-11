#include"HR_chart.h"
#include"menu.h"

extern lv_group_t * ui_group;

lv_obj_t * HR_chart_cont, * HR_chart;
lv_chart_series_t * HR_series;
lv_coord_t HR_points[11] = {78,89,88,92,110,96,120,119,65,76};

static void tomenu_callback(struct _lv_obj_t *obj, lv_event_t event)
{
    if(event == LV_EVENT_KEY)
    {
        const uint8_t *key = lv_event_get_data();
        if(*key == LV_KEY_DOWN)
        {
            lv_group_remove_obj(HR_chart_cont);
            menu_ui_create();
            lv_obj_del_async(HR_chart_cont);
        }
    }
}

void HR_chart_create(void)
{
    HR_chart_cont = lv_cont_create(lv_scr_act(), NULL);
    lv_group_add_obj(ui_group, HR_chart_cont);
    lv_obj_set_event_cb(HR_chart_cont, tomenu_callback);
    lv_obj_set_size(HR_chart_cont, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    HR_chart = lv_chart_create(HR_chart_cont, NULL);
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
    lv_cont_set_layout(HR_chart_cont, LV_LAYOUT_COL_R);

}
