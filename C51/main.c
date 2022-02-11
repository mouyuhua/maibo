#include"reg52.h"
#include"delay.h"
#include"sensor.h"
#include"bluetooth.h"

sbit led = P0^0;

extern u8 SensorData[DATASIZE];
extern u8 BluetoothSendData[DATASIZE];
u8 i;

void main(void)
{
	// 初始化，开中断
    DelayInit();
    SensorInit();
    BluetoothInit();
    EA = 1;
    led = 1;
	
    while(1)
    {
        GetSensorData();
        led = ~led;
		
		// 将传感器数据存入蓝牙发送数据中，并且将数据转换成协议数据（0x0d 0x0a结尾）
		for(i=0; i<DATASIZE; i++)
			BluetoothSendData[i] = SensorData[i];
		BluetoothSendData[DATASIZE-2]=0x0d;
		BluetoothSendData[DATASIZE-1]=0x0a;
		
        Delay(1);
		
        BluetoothSend(BluetoothSendData, DATASIZE);        
    }
}
