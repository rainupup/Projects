#ifndef __TASKMANAGE_H
#define __TASKMANAGE_H

extern float pitch,roll,yaw;
extern short AX, AY, AZ, GX, GY, GZ;
void vTaskFunction(void);
void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);
void pidTest(void);
#endif
