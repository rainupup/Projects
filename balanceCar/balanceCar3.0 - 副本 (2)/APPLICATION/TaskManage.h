#ifndef __TASKMANAGE_H
#define __TASKMANAGE_H

void vTaskFunction(void);
void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);

#endif
