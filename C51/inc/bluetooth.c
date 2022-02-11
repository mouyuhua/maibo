#include"reg52.h"
#include"bluetooth.h"

sbit PIN_RXD = P2^0; //接收引脚定义
sbit PIN_TXD = P2^1; //发送引脚定义

bit RxdOrTxd = 0; //指示当前状态为接收还是发送
bit RxdEnd = 0; //接收结束标志
bit TxdEnd = 0; //发送结束标志
bit BluetoothState = 0; //蓝牙状态设置，0 接收， 1 发送
unsigned char RxdBuf = 0; //接收缓冲器
unsigned char TxdBuf = 0; //发送缓冲器

u8 BluetoothSendData[DATASIZE]; //蓝牙发送数据缓存
//u8 BluetoothReciveData[DATASIZE];   //蓝牙接收数据缓存
u8 count=0;

/*初始化蓝牙串口通信，波特率设置为9600*/
void BluetoothInit(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x02; 
    TH0 = 256 - (11059200/12)/9600;
}

/*
    蓝牙发送数据
    参数：
        Data[]  要发送的数据内容
        length  发送的数据长度
*/
void BluetoothSend(u8 Data[], u8 length)
{
    u8 i;
    BluetoothState = 1;
    if(BluetoothState)
    {
        for(i=0; i<length; i++)
        {
            StartTXD(Data[i]);
            while (!TxdEnd); //等待发送完成
        }
        BluetoothState = 0;
    }
    
}

/*
    蓝牙接收数据
    接收完数据后保存至BluetoothReciveData[DATASIZE]中
*/
//void BluetoothRecive(void)
//{
//    //while (PIN_RXD); //等待接收引脚出现低电平，即起始位
//    // if(!PIN_RXD)
//    // {
//    //     StartRXD(); //启动接收
//    //     while (!RxdEnd); //等待接收完成
//    //     BluetoothReciveData[count] = RxdBuf;
//    //     count++;
//    //     if(count<DATASIZE)
//    //         BluetoothRecive();
//    //     count = 0;
//    // }
//    int i;
//    
//    if(!BluetoothState && !PIN_RXD)
//    {
//        //while(PIN_RXD);
//        for(i=0; i<DATASIZE; i++)
//        {
//            //while(PIN_RXD);
//            StartRXD();
//            while(!RxdEnd);
//            BluetoothReciveData[i] = RxdBuf;
//        }
//        BluetoothState = 1;
//    }
//    //BluetoothState = 1;
//}

/*
    用于发送一字节数据数据
    参数:
        Data    一字节数据内容
*/
void StartTXD(u8 Data)
{
    TxdBuf = Data; //待发送数据保存到发送缓冲器
    TL0 = TH0; //T0 计数初值为重载值
    ET0 = 1; //使能 T0 中断
    TR0 = 1; //启动 T0
    PIN_TXD = 0; //发送起始位
    TxdEnd = 0; //清零发送结束标志
    RxdOrTxd = 1; //设置当前状态为发送
}

/*
    用于接收一字节数据
*/
//void StartRXD(void)
//{
//    TL0 = 256 - ((256-TH0)>>1); //接收启动时的 T0 定时为半个波特率周期
//    ET0 = 1; //使能 T0 中断
//    TR0 = 1; //启动 T0
//    RxdEnd = 0; //清零接收结束标志
//    RxdOrTxd = 0; //设置当前状态为接收
//}

/* T0 中断服务函数，处理串行发送和接收 */
void InterruptTimer0() interrupt 1
{
    static unsigned char cnt = 0; //位接收或发送计数
    if (RxdOrTxd) //串行发送处理
    {
        cnt++;
        if (cnt <= 8) //低位在先依次发送 8bit 数据位
        {
            PIN_TXD = TxdBuf & 0x01;
            TxdBuf >>= 1;
        }
        else if (cnt == 9) //发送停止位
        {
            PIN_TXD = 1;
        }
        else //发送结束
        {
            cnt = 0; //复位 bit 计数器
            TR0 = 0; //关闭 T0
            TxdEnd = 1; //置发送结束标志
        }
    }
    else //串行接收处理
    {
        if (cnt == 0) //处理起始位
        {
            if (!PIN_RXD) //起始位为 0 时，清零接收缓冲器，准备接收数据位
            {
                RxdBuf = 0;
                cnt++;
            }
            else //起始位不为 0 时，中止接收
            {
                TR0 = 0; //关闭 T0
            }
        }
        else if (cnt <= 8) //处理 8 位数据位
        {
            RxdBuf >>= 1; //低位在先，所以将之前接收的位向右移
            if (PIN_RXD) //接收脚为 1 时，缓冲器最高位置 1，
            { //而为 0 时不处理即仍保持移位后的 0
                RxdBuf |= 0x80;
            }
            cnt++;
        }
        else //停止位处理
        {
            cnt = 0; //复位 bit 计数器
            TR0 = 0; //关闭 T0
            if (PIN_RXD) //停止位为 1 时，方能认为数据有效
            {
                RxdEnd = 1; //置接收结束标志
            }
        }
    }
}

