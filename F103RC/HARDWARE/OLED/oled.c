/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑       永不宕机     永无BUG
 *
 */

#include "oled.h"
#include "delay.h"

#if USE_MY_I2C == 0

void IIC_Start()
{
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

void IIC_Stop()
{
	OLED_SCLK_Set();
	// OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}

void IIC_Send_Byte(u8 IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
			OLED_SDIN_Set();
		else 
			OLED_SDIN_Clr();
		da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}

#endif

// OLED的显存
u8 OLED_GRAM[128][8];
//存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

/**********************************************
 * 通过I2C写命令
 **********************************************/
void Write_IIC_Command(u8 Command)
{
	IIC_Start();
	IIC_Send_Byte(0x78); // Slave address,SA0=0
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00); // write command
	IIC_Wait_Ack();
	IIC_Send_Byte(Command);
	IIC_Wait_Ack();
	IIC_Stop();
}
/**********************************************
 * 通过I2C写数据
 **********************************************/
void Write_IIC_Data(u8 Data)
{
	IIC_Start();
	IIC_Send_Byte(0x78); // D/C#=0; R/W#=0
	IIC_Wait_Ack();
	IIC_Send_Byte(0x40); // write data
	IIC_Wait_Ack();
	IIC_Send_Byte(Data);
	IIC_Wait_Ack();
	IIC_Stop();
}

/**
 * @description:
 * @param {u8} dat:数据/命令
 * @param {u8} cmd：OLED_CMD /OLED_DATA
 * @return {*}
 */
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	if (cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_Command(dat);
	}
}

/**
 * @description: 刷新OLED屏幕，将显存中的数据更新到OLED屏幕上
 * @param {*}
 * @return {*}
 */
void OLED_Refresh(void)
{
	unsigned char m, n;
	for (m = 0; m < 8; m++)
	{
		OLED_WR_Byte(0xb0 + m, 0); // page0-page1
		OLED_WR_Byte(0x00, 0);	   // low column start address
		OLED_WR_Byte(0x10, 0);	   // high column start address
		for (n = 0; n < 128; n++)
		{
			OLED_WR_Byte(OLED_GRAM[n][m], OLED_DATA);
		}
	}
}

void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD);
}

/**
 * @description: 画点
 * @param {u8} x：x坐标
 * @param {u8} y：y坐标
 * @param {u8} t：1亮色 0暗色 （正常模式下）
 * @return {*}
 */
void OLED_DrawPoint(u8 x, u8 y, u8 t)
{
	u8 pos, bx, temp = 0;
	if (x > 127 || y > 63)
		return;
	pos = 7 - y / 8;
	bx = y % 8;
	temp = 1 << (7 - bx);
	if (t)
		OLED_GRAM[x][pos] |= temp;
	else
		OLED_GRAM[x][pos] &= ~temp;
}

/**
 * @description: 开启OLED显示
 * @param {*}
 * @return {*}
 */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC命令
	OLED_WR_Byte(0X14, OLED_CMD); // DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD); // DISPLAY ON
}

/**
 * @description: 关闭OLED显示
 * @param {*}
 * @return {*}
 */
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC命令
	OLED_WR_Byte(0X10, OLED_CMD); // DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD); // DISPLAY OFF
}

/**
 * @description: 将OLED屏幕设置为纯黑色
 * @param {*}
 * @return {*}
 */
void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	  //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	  //设置显示位置—列高地址
		for (n = 0; n < 128; n++)
		{
#if OLED_INVERSE
			OLED_GRAM[n][i] = 0Xff;
#else
			OLED_GRAM[n][i] = 0X00;
#endif
		}
		OLED_Refresh();
	}
}

/**
 * @description: 将OLED屏幕设置为纯白色
 * @param {*}
 * @return {*}
 */
void OLED_On(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	  //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	  //设置显示位置—列高地址
		for (n = 0; n < 128; n++)
#if OLED_INVERSE
			OLED_WR_Byte(0, OLED_DATA);
#else
			OLED_WR_Byte(1, OLED_DATA);
#endif
	}
}

#if USE_FONT

#include "stdlib.h"
#include "oledfont.h"

/**
 * @description: 在OLED屏幕上显示字符
 * @param {u8} x：x坐标
 * @param {u8} y：y坐标
 * @param {u8} chr：要显示的字符
 * @param {u8} Char_Size：字体大小12或16
 * @return {*}
 */
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 Char_Size)
{
	unsigned char c = 0, i = 0;
	c = chr - ' '; //得到偏移后的值
	if (x > 128 - 1)
	{
		x = 0;
		y = y + 2;
	}
	if (Char_Size == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
	}
}

/**
 * @description: 在OLED屏幕上显示字符串
 * @param {u8} x：x坐标
 * @param {u8} y：y坐标
 * @param {u8} *chr：要显示的字符串
 * @param {u8} Char_Size：字体大小
 * @return {*}
 */
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], Char_Size);
		x += 8;
		if (x > 120)
		{
			x = 0;
			y += 2;
		}
		j++;
	}
}

//显示汉字
void OLED_ShowChinese(u8 x, u8 y, u8 no)
{
	u8 t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
		adder += 1;
	}
}

/**
 * @description: 在OLED屏幕上显示数字
 * @param {u8} x：x坐标
 * @param {u8} y：y坐标
 * @param {u32} num：要显示的数字
 * @param {u8} len：数字长度
 * @param {u8} size：字体大小
 * @return {*}
 */
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size)
{
	u8 t, temp;
	u8 enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size / 2) * t, y, ' ', size);
				continue;
			}
			else
				enshow = 1;
		}
		OLED_ShowChar(x + (size / 2) * t, y, temp + '0', size);
	}
}

#endif

// m^n函数
u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
		result *= m;
	return result;
}

/**
 * @description: 向指定区域填充图像，以列为单位进行填充
 * @param {u8} x0：起始x坐标
 * @param {u8} y0：起始y坐标
 * @param {u8} x1：终止x坐标
 * @param {u8} y1：终止y坐标
 * @param {u8} BMP：填充图像的数据
 * @return {*}
 */
void OLED_Draw(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
}

/**
 * @description: 向指定区域填充图像，以像素点为单位填充，可用于GUI接口
 * @param {u8} x1：起始x坐标
 * @param {u8} y1：起始y坐标
 * @param {u8} x2：终止x坐标
 * @param {u8} y2：终止y坐标
 * @param {u8} dot：填充的数据
 * @return {*}
 */
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot[])
{
	u8 x, y;
	u16 j = 0;
	for (y = y1; y <= y2; y++)
	{
		for (x = x1; x <= x2; x++)
			OLED_DrawPoint(x, y, dot[j++]);
	}
	OLED_Refresh();
}

/**
 * @description:OLED屏幕初始化
 * @param {*}
 * @return {*}
 */
void OLED_Init(void)
{
#if USE_MY_I2C
	IIC_Init();
#else
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7);	
#endif

	delay_ms(800);
	OLED_WR_Byte(0xAE, OLED_CMD); //--display off
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address
	OLED_WR_Byte(0xB0, OLED_CMD); //--set page address
	OLED_WR_Byte(0x81, OLED_CMD); // contract control
	OLED_WR_Byte(0xFF, OLED_CMD); //--128

// set segment remap
#if OLED_RL
	OLED_WR_Byte(0xA1, OLED_CMD);
#else
	OLED_WR_Byte(0xA0, OLED_CMD);
#endif

//--normal / reverse
#if OLED_INVERSE
	OLED_WR_Byte(0xA7, OLED_CMD);
#else
	OLED_WR_Byte(0xA6, OLED_CMD);
#endif

	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F, OLED_CMD); //--1/32 duty

// Com scan direction
#if OLED_UD
	OLED_WR_Byte(0xC8, OLED_CMD);
#else
	OLED_WR_Byte(0xC0, OLED_CMD);
#endif
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset
	OLED_WR_Byte(0x00, OLED_CMD); //
	OLED_WR_Byte(0xD5, OLED_CMD); // set osc division
	OLED_WR_Byte(0x80, OLED_CMD); //
	OLED_WR_Byte(0xD8, OLED_CMD); // set area color mode off
	OLED_WR_Byte(0x05, OLED_CMD); //
	OLED_WR_Byte(0xD9, OLED_CMD); // Set Pre-Charge Period
	OLED_WR_Byte(0xF1, OLED_CMD); //
	OLED_WR_Byte(0xDA, OLED_CMD); // set com pin configuartion
	OLED_WR_Byte(0x12, OLED_CMD); //
	OLED_WR_Byte(0xDB, OLED_CMD); // set Vcomh
	OLED_WR_Byte(0x30, OLED_CMD); //
	OLED_WR_Byte(0x8D, OLED_CMD); // set charge pump enable
	OLED_WR_Byte(0x14, OLED_CMD); //
	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
	
}
