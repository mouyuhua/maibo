#include "delay.h"
#include "reg52.h"

bit timeflag;

/*延时功能初始化，定时器1方式1, 50ms*/
void DelayInit(void)
{
    TMOD &= 0x0f;
    TMOD |= 0x10;
    TL1 = 0x00;
    TH1 = 0x4c;
    TR1 = 1;
    ET1 = 1;
}

/*延时100ms*/
void Delay100ms(void)
{
    while(timeflag);
    while(!timeflag);
}

/*延时一定的时间，参数second用于设置延迟的秒数*/
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
