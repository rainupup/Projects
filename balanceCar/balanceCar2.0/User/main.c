#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "PWM.h"
#include "Encoder.h"
#include "MPU6050.h"
#include "Bluetooth.h"
#include "Motor.h"
#include <stdio.h>
#include <stdarg.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ,RData,PWMSpeed=3000;

//int fputc( int ch, FILE *f )
//{
//	//while((USART1->SR >> 7) == 0);
//	while((USART3->SR & (1 << 7)) == 0);
//	USART3->DR = ch;
//	return ch;
//}

void HardWareInit(void){
	MPU_Init();
	OLED_Init();
	PWM_Init();
	Encoder_Init();
	Bluttooth_Init();
	MOTOR_Init();
}

int main(void)
{	

	
	while(1){
		
		RData = GetBuleToothData();
		OLED_ShowHexNum(1, 4, RData , 8);
		
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

		OLED_ShowSignedNum(2, 1, 74-Get_Encoder1(), 5);
		OLED_ShowSignedNum(3, 1, Get_Encoder2(), 5); 
		
		
//		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
//		OLED_ShowSignedNum(2, 1, AX, 5);
//		OLED_ShowSignedNum(3, 1, AY, 5);
//		OLED_ShowSignedNum(4, 1, AZ, 5);
//		
//		OLED_ShowSignedNum(2, 8, GX, 5);
//		OLED_ShowSignedNum(3, 8, GY, 5);
//		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
//	vTaskStartScheduler();
}


