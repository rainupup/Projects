#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);


short AX, AY, AZ, GX, GY, GZ,RData;
uint32_t PWMSpeed;

void vTaskFunction(void){
	xTaskCreate(vStart,"vStart",100,NULL,3,NULL);
}

void vStart(void* pvParameters){
	BaseType_t xReturn = pdPASS;
	
	taskENTER_CRITICAL();            // ֹͣ�ж�
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
		OLED_ShowString(3, 2, "BT SUCCESS");
	}
	OLED_Clear();
	vTaskDelete(NULL);
	
	taskEXIT_CRITICAL();     // �����ж�
}

void vPID(void* pvParameters){
	int Encoder_Left,Encoder_Right;

	
	
	while(1){
		
		Encoder_Left = Get_EncoderLeft();
		Encoder_Right= Get_EncoderRight();
		
		if(RData == 0x47){
			Forward(PWMSpeed);
		}else if(RData == 0x4A){
			Right(PWMSpeed);
		}else if(RData == 0x48){
			Left(PWMSpeed);
		}else if(RData == 0x4B){
			Back(PWMSpeed);
		}else if(RData == 0x49){
			Stop();
		}else if(RData == 0x41){
			PWMSpeed = 16000;
		}else if(RData == 0x42){
			PWMSpeed = 20000;
		}else if(RData == 0x43){
			PWMSpeed = 30000;
		}else if(RData == 0x44){
			PWMSpeed = 50000;
		}	
		vTaskDelay(1);
	}
}
void vOLED(void* pvParameters){
	while(1){
		OLED_ShowSignedNum(2, 1, Get_EncoderLeft(), 5);
		OLED_ShowSignedNum(3, 1, Get_EncoderRight(), 5); 

//		MPU_Get_Gyroscope(&GX,&GY,&GZ);

//		OLED_ShowSignedNum(2, 1, GX, 5);
//		OLED_ShowSignedNum(3, 1, GY, 5); 
//		OLED_ShowSignedNum(4, 1, GZ, 5); 
		vTaskDelay(10);
	}
}

void vBluetooth(void* pvParameters){
	
	while(1){
		RData = GetBuleToothData();
		//OLED_ShowSignedNum(1, 1, 1 , 5);
		vTaskDelay(1);
	}
}
