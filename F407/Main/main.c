#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "sys.h"
#include "pwm.h"

int main(void)
{
	u8 len;
	u8 start=70;
	u8 i,dir=1;
	u16 beep = 150;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�������ж����ȼ�

	delay_init(168); 
	uart_init(9600);
 	LCD_Init(); 
	PWM_TIM14_Init(500-1,84-1);       

	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;	
	LCD_ShowString(30,30,100,16,16,"title");
  	while(1) 
	{		 
		if(USART_RX_STA&0x8000)	  
		{
			len = USART_RX_STA&0x3fff;	//���ݳ���
			//��ʾ����
			for(i=1; i<len; i++)
			{
				LCD_ShowString(30, start, 50, 16, 16, "name:");
				LCD_ShowNum(70,start,USART_RX_BUF[i],4,16);
				start+=20;	  
			}
			//�ж������Ƿ���������Χ����������쳣����ʼ����
			if(USART_RX_BUF[3]<=60 || USART_RX_BUF[3]>=100)
			{
				LCD_ShowString(140,30,80,16,16,"waring");
				if(dir)
				{
					beep+=20;
					if(beep>=300)
					{
						dir=0;
					}
				}
				else
				{
					beep-=20;
					if(beep<=150)
					{
						dir=1;
					}
				}
				TIM_SetCompare1(TIM14, beep);
			}			
			else
			{
				LCD_ShowString(140,30,80,16,16," fine ");
				TIM_SetCompare1(TIM14, 500);
			}
			start = 70;	
			USART_RX_STA = 0;		
		}
		delay_ms(100);	
	} 
}
