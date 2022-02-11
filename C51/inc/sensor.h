#ifndef SENSOR_H
#define SENSOR_H

#include"datadef.h"

void SensorInit(void);

void GetSensorData(void);

void SendData2Sensor(u8 Data[], u8 length);

#endif
