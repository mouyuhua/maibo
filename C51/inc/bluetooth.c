#include"reg52.h"
#include"bluetooth.h"

sbit PIN_RXD = P2^0; //�������Ŷ���
sbit PIN_TXD = P2^1; //�������Ŷ���

bit RxdOrTxd = 0; //ָʾ��ǰ״̬Ϊ���ջ��Ƿ���
bit RxdEnd = 0; //���ս�����־
bit TxdEnd = 0; //���ͽ�����־
bit BluetoothState = 0; //����״̬���ã�0 ���գ� 1 ����
unsigned char RxdBuf = 0; //���ջ�����
unsigned char TxdBuf = 0; //���ͻ�����

u8 BluetoothSendData[DATASIZE]; //�����������ݻ���
//u8 BluetoothReciveData[DATASIZE];   //�����������ݻ���
u8 count=0;

/*��ʼ����������ͨ�ţ�����������Ϊ9600*/
void BluetoothInit(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x02; 
    TH0 = 256 - (11059200/12)/9600;
}

/*
    ������������
    ������
        Data[]  Ҫ���͵���������
        length  ���͵����ݳ���
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
            while (!TxdEnd); //�ȴ��������
        }
        BluetoothState = 0;
    }
    
}

/*
    ������������
    ���������ݺ󱣴���BluetoothReciveData[DATASIZE]��
*/
//void BluetoothRecive(void)
//{
//    //while (PIN_RXD); //�ȴ��������ų��ֵ͵�ƽ������ʼλ
//    // if(!PIN_RXD)
//    // {
//    //     StartRXD(); //��������
//    //     while (!RxdEnd); //�ȴ��������
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
    ���ڷ���һ�ֽ���������
    ����:
        Data    һ�ֽ���������
*/
void StartTXD(u8 Data)
{
    TxdBuf = Data; //���������ݱ��浽���ͻ�����
    TL0 = TH0; //T0 ������ֵΪ����ֵ
    ET0 = 1; //ʹ�� T0 �ж�
    TR0 = 1; //���� T0
    PIN_TXD = 0; //������ʼλ
    TxdEnd = 0; //���㷢�ͽ�����־
    RxdOrTxd = 1; //���õ�ǰ״̬Ϊ����
}

/*
    ���ڽ���һ�ֽ�����
*/
//void StartRXD(void)
//{
//    TL0 = 256 - ((256-TH0)>>1); //��������ʱ�� T0 ��ʱΪ�������������
//    ET0 = 1; //ʹ�� T0 �ж�
//    TR0 = 1; //���� T0
//    RxdEnd = 0; //������ս�����־
//    RxdOrTxd = 0; //���õ�ǰ״̬Ϊ����
//}

/* T0 �жϷ������������з��ͺͽ��� */
void InterruptTimer0() interrupt 1
{
    static unsigned char cnt = 0; //λ���ջ��ͼ���
    if (RxdOrTxd) //���з��ʹ���
    {
        cnt++;
        if (cnt <= 8) //��λ�������η��� 8bit ����λ
        {
            PIN_TXD = TxdBuf & 0x01;
            TxdBuf >>= 1;
        }
        else if (cnt == 9) //����ֹͣλ
        {
            PIN_TXD = 1;
        }
        else //���ͽ���
        {
            cnt = 0; //��λ bit ������
            TR0 = 0; //�ر� T0
            TxdEnd = 1; //�÷��ͽ�����־
        }
    }
    else //���н��մ���
    {
        if (cnt == 0) //������ʼλ
        {
            if (!PIN_RXD) //��ʼλΪ 0 ʱ��������ջ�������׼����������λ
            {
                RxdBuf = 0;
                cnt++;
            }
            else //��ʼλ��Ϊ 0 ʱ����ֹ����
            {
                TR0 = 0; //�ر� T0
            }
        }
        else if (cnt <= 8) //���� 8 λ����λ
        {
            RxdBuf >>= 1; //��λ���ȣ����Խ�֮ǰ���յ�λ������
            if (PIN_RXD) //���ս�Ϊ 1 ʱ�����������λ�� 1��
            { //��Ϊ 0 ʱ�������Ա�����λ��� 0
                RxdBuf |= 0x80;
            }
            cnt++;
        }
        else //ֹͣλ����
        {
            cnt = 0; //��λ bit ������
            TR0 = 0; //�ر� T0
            if (PIN_RXD) //ֹͣλΪ 1 ʱ��������Ϊ������Ч
            {
                RxdEnd = 1; //�ý��ս�����־
            }
        }
    }
}

