#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
    	
//�������ɨ�跽��
#define OLED_RL 1           //��������
#define OLED_UD 0           //���ϵ���

//��ɫ��ת
#define OLED_INVERSE 1

//ʹ������
#define USE_FONT 1
/**
 * ���ⲿ����I2C����
 * �ⲿI2C�ļ���Ҫ�����º궨��ͺ�����
 *      �궨�壺
 *          OLED_SCLK_Clr()
 *          OLED_SCLK_Set()
 *          OLED_SDIN_Clr()
 *          OLED_SDIN_Set()
 *      ������
 *          void IIC_Start(void);
 *          void IIC_Stop(void);
 *          void IIC_Wait_Ack(void);
 *					void IIC_Send_Byte(u8 IIC_Byte);
 */
#define USE_MY_I2C 0

/**
 * �ڲ�I2C����
 */
#if USE_MY_I2C
//�����ⲿI2C
#include "myiic.h"

#else

//�ڲ�I2C����
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Wait_Ack(void);
void IIC_Send_Byte(u8 IIC_Byte);

#endif


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED�����ú���
void OLED_Init(void);

void Write_IIC_Command(u8 Command);

void Write_IIC_Data(u8 Data);

void OLED_WR_Byte(u8 dat, u8 cmd);

void OLED_Refresh(void);

void OLED_DrawPoint(u8 x, u8 y, u8 t);

void OLED_Display_On(void);

void OLED_Display_Off(void);

void OLED_On(void);

void OLED_Clear(void);

u32 oled_pow(u8 m, u8 n);

void OLED_Draw(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);

void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot[]);

#if USE_FONT

void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 Char_Size);

void OLED_ShowString(u8 x, u8 y, u8* chr, u8 Char_Size);

void OLED_ShowChinese(u8 x, u8 y, u8 no);

void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size);

#endif

#endif  
