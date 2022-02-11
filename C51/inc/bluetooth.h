#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include"datadef.h"

void BluetoothInit(void);

void StartTXD(u8 Data);

//void StartRXD();

void BluetoothSend(u8 Data[], u8 length);

//void BluetoothRecive(void);



#endif
