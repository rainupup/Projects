#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "OLED.h"
#include "mpu6050.h"


void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);

void vTaskFunction(void){
	xTaskCreate(vStart,"vStart",100,NULL,3,NULL);
}

void vStart(void* pvParameters){
	BaseType_t xReturn = pdPASS;
	
	taskENTER_CRITICAL();            // Í£Ö¹ÖÐ¶Ï
	xReturn = xTaskCreate(vOLED,"vOLED",100, NULL,1,NULL);
	if(xReturn != NULL){
		OLED_ShowString(1, 1, "OLED SUCCESS");
	}
	xReturn = xTaskCreate(vPID,"vPID",100, NULL,1,NULL);
	if(xReturn != NULL){
		OLED_ShowString(2, 1, "PID SUCCESS");
	}
	
	xReturn = xTaskCreate(vBluetooth,"vBluetooth",100, NULL,1,NULL);
	if(xReturn != NULL){
		OLED_ShowString(3, 2, "Bluetooth SUCCESS");
	}

	vTaskDelete(NULL);
	
	taskEXIT_CRITICAL();     // ¿ªÆôÖÐ¶Ï
}
void vPID(void* pvParameters){
	while(1){
	
		vTaskDelay(1);
	}

}
void vOLED(void* pvParameters){
	while(1){
	
		vTaskDelay(10);
	}
}

void vBluetooth(void* pvParameters){
	
	while(1){
	
		vTaskDelay(1);
	}
}