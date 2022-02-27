#include "lvgl.h"
#include "lv_port_disp.h"
#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "oled.h"
#include "usart.h"
#include "key.h"
#include "app_ui.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	KEY_Init();
	delay_init(168);  //初始化延时函数
	TIM3_Int_Init(10-1,8400-1); //初始化TIM3， 1ms
	uart_init(9600);
	
	OLED_Init();
	
	lv_init();
	lv_port_disp_init();
	
	main_ui_create();
	
	while(1)
	{
		lv_task_handler();
		key_hander();
	}
	
}
