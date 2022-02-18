#include "lvgl.h"
#include "lv_port_disp.h"
#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "oled.h"
#include "app_ui.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();  //��ʼ����ʱ����
	TIM3_Int_Init(999,71);
	
	OLED_Init();
	
	lv_init();
	lv_port_disp_init();
	
	main_ui_create();
	
	while(1)
	{
		lv_task_handler();
	}
	
}
