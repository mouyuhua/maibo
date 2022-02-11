#include "delay.h"
#include "reg52.h"

bit timeflag;

/*��ʱ���ܳ�ʼ������ʱ��1��ʽ1, 50ms*/
void DelayInit(void)
{
    TMOD &= 0x0f;
    TMOD |= 0x10;
    TL1 = 0x00;
    TH1 = 0x4c;
    TR1 = 1;
    ET1 = 1;
}

/*��ʱ100ms*/
void Delay100ms(void)
{
    while(timeflag);
    while(!timeflag);
}

/*��ʱһ����ʱ�䣬����second���������ӳٵ�����*/
void Delay(u8 second)
{
    int i = 0;
    for(i=0; i<second*10; i++)
        Delay100ms();
}

void timer1int() interrupt 3
{
    TL1 = 0x00;
    TH1 = 0x4c;
    timeflag = ~timeflag;
}
