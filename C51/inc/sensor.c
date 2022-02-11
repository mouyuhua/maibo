#include"reg52.h"
#include"sensor.h"

u8 SensorData[DATASIZE];//传感器数据缓存

u8 code GetData[DATASIZE] = {0xfd, 0x00, 0x00, 0x00, 0x00, 0x00};//传感器数据读取指令

u8 cnt;
bit SensorState=1;//传感器状态，1：允许发送  0：允许接收

/*初始化单片机与传感器的串口通信，波特率设置为115200*/
void SensorInit(void)
{
    SCON=0x50;   
    TH2=0xFF;           
    TL2=0xFD;   
    RCAP2H=0xFF;   
    RCAP2L=0xFD; 

    T2CON = 0x34;
    ES = 1;
}

/*
    获取传感器数据，调用之后传感器数据将缓存在SensorData[DATASIZE]中
*/
void GetSensorData(void)
{
    SensorState = 1;
    SendData2Sensor(GetData, 6);
}

/*
    发送数据到传感器
    参数：
        Data[]: 要发送的数据
        length: 发送数据的长度
*/
void SendData2Sensor(u8 Data[], u8 length)
{
    u8 i;
    if(SensorState)
    {
        for(i=0; i<length; i++)
        {
            SBUF = Data[i];
            while(!TI);
            TI = 0;
        }
        SensorState = 0;
    }
}

/*中断服务函数，用于处理数据的接收*/
void InterruptUART() interrupt 4
{
    RI = 0;
    if(!SensorState)
    {
        SensorData[cnt] = SBUF;
        cnt++;
        if(cnt>=6)
        {
            cnt=0;
            SensorState = 1;
        }
    }
}
