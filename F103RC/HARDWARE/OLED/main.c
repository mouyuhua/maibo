#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
  {	u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	//		delay_ms(8000);
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 
	
		t=' ';
		OLED_ShowChinese(54,0,3);//电
		OLED_ShowChinese(72,0,4);//子
		OLED_ShowChinese(90,0,5);//科
		OLED_ShowChinese(108,0,6);//技
	while(1) 
	{		
		OLED_Clear();
		OLED_ShowChinese(54,0,3);//电
		OLED_ShowChinese(72,0,4);//子
		OLED_ShowChinese(90,0,5);//科
		OLED_ShowChinese(108,0,6);//技
		OLED_ShowString(6,3,"0.96' OLED TEST",16); 
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			delay_ms(8000);
		delay_ms(8000);

					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
		OLED_Draw(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(8000);
					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
		OLED_Draw(0,0,128,8,BMP1);
		delay_ms(8000);
					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
	}	  
	
}
	
