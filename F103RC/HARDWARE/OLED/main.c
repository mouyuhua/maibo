#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
  {	u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	//		delay_ms(8000);
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear()  	; 
	
		t=' ';
		OLED_ShowChinese(54,0,3);//��
		OLED_ShowChinese(72,0,4);//��
		OLED_ShowChinese(90,0,5);//��
		OLED_ShowChinese(108,0,6);//��
	while(1) 
	{		
		OLED_Clear();
		OLED_ShowChinese(54,0,3);//��
		OLED_ShowChinese(72,0,4);//��
		OLED_ShowChinese(90,0,5);//��
		OLED_ShowChinese(108,0,6);//��
		OLED_ShowString(6,3,"0.96' OLED TEST",16); 
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",16);  
		OLED_ShowString(63,6,"CODE:",16);  
		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
			delay_ms(8000);
		delay_ms(8000);

					delay_ms(8000);
		delay_ms(8000);
		delay_ms(8000);
		OLED_Draw(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
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
	
