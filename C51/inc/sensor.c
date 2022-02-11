#include"reg52.h"
#include"sensor.h"

u8 SensorData[DATASIZE];//���������ݻ���

u8 code GetData[DATASIZE] = {0xfd, 0x00, 0x00, 0x00, 0x00, 0x00};//���������ݶ�ȡָ��

u8 cnt;
bit SensorState=1;//������״̬��1��������  0���������

/*��ʼ����Ƭ���봫�����Ĵ���ͨ�ţ�����������Ϊ115200*/
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
    ��ȡ���������ݣ�����֮�󴫸������ݽ�������SensorData[DATASIZE]��
*/
void GetSensorData(void)
{
    SensorState = 1;
    SendData2Sensor(GetData, 6);
}

/*
    �������ݵ�������
    ������
        Data[]: Ҫ���͵�����
        length: �������ݵĳ���
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

/*�жϷ����������ڴ������ݵĽ���*/
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
