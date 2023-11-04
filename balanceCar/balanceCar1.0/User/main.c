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

/* Library includes. */
//#include "stm32f10x_it.h"
#define PWMA1   TIM3->CCR2
#define PWMA2   TIM3->CCR3

#define PWMB1   TIM3->CCR1
#define PWMB2   TIM3->CCR4

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

//int fputc( int ch, FILE *f )
//{
//	//while((USART1->SR >> 7) == 0);
//	while((USART3->SR & (1 << 7)) == 0);
//	USART3->DR = ch;
//	return ch;
//}

//电机1的软件PWM

int i = 0;int d = 0;
void vTask1(void * p){
	int16_t PWMSpeed=0,Speed,RData;	
	//	
	PWMB2 = 5000;
	PWMB1=0;
	PWMA2=5000;
	PWMA1=0;
	

	
//	
//	PWMA2=0;
//	PWMA1=15000;
//	
//	PWMB2 = 0;
//	PWMB1=15000;
	

		

	

	while(1){
		RData = GetBuleToothData();
//		OLED_ShowHexNum(1, 4, RData , 8);
//		OLED_ShowNum(3 ,1, Get_Encoder1(), 10);
		

//		TIM_SetCompare3(TIM3,0);
//		TIM_SetCompare4(TIM3,0);
//		TIM_SetCompare1(TIM3,15000);
//		TIM_SetCompare2(TIM3,15000);
		
//		if(RData == 0x47){
//			Forward(PWMSpeed);
//		}else if(RData == 0x4A){
//			Right(PWMSpeed);
//		}else if(RData == 0x48){
//			Left(PWMSpeed);
//		}else if(RData == 0x4B){
//			Back(PWMSpeed);
//		}else if(RData == 0x49){
//			Stop();
//		}else if(RData == 0x41){
//			PWMSpeed = 16000;
//		}else if(RData == 0x42){
//			PWMSpeed = 20000;
//		}else if(RData == 0x43){
//			PWMSpeed = 30000;
//		}else if(RData == 0x44){
//			PWMSpeed = 50000;
//		}	
		OLED_ShowHexNum(1, 5, TIM_GetCapture1(TIM3), 8);
		OLED_ShowHexNum(2, 5, TIM_GetCapture2(TIM3), 8);
		OLED_ShowHexNum(3, 5, TIM_GetCapture3(TIM3), 8);
		OLED_ShowHexNum(4, 5, TIM_GetCapture4(TIM3), 8);
		vTaskDelay(1);
		
		
//		//Stop();
////		Speed = IC_GetCapture1();
////		Speed = Speed / 44 * 60;
////		OLED_ShowSignedNum(1, 10, PWMSpeed, 3);
////		OLED_ShowSignedNum(2, 10, Speed, 3);
//		
////		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
////		OLED_ShowSignedNum(2, 1, AX, 5);
////		OLED_ShowSignedNum(3, 1, AY, 5);
////		OLED_ShowSignedNum(4, 1, AZ, 5);
////		
////		OLED_ShowSignedNum(2, 8, GX, 5);
////		OLED_ShowSignedNum(3, 8, GY, 5);
////		OLED_ShowSignedNum(4, 8, GZ, 5);
//			
	}
}

int main(void)
{	
	MPU6050_Init();
	OLED_Init();
//	PWM_Init();

	//Key_Init();
	Encoder_Init();
	
	Bluttooth_Init();
	
//	OLED_ShowString(1, 1, "PWMSpeed:");
//	OLED_ShowString(2, 1, "Speed:");
	//OLED_ShowString(3, 1, "ID:");
//	ID = MPU6050_GetID();
	//OLED_ShowHexNum(3, 4, ID, 2);
	OLED_ShowString(1, 1, "BT:");

//	PWM_SetCompare1_1(10000);
//	PWM_SetCompare1_2(10000);
//	PWM_SetCompare2_1(10000);
//	PWM_SetCompare2_2(10000);
	
	
	
//	xTaskCreate(vTaskPWM,"SoftPWM",100,NULL,0,NULL);
//	xTaskCreate(vTask1,"1",100,NULL,0,NULL);
//	vTaskStartScheduler();
}


