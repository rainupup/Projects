#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define TargetSpeedMax   300               // 最大速度
#define TurnSpeedMax   300                 // 最大转弯速度


float pitch,roll,yaw;
short AX, AY, AZ, GX, GY, GZ;

int Vertical_Out,Velocity_Out,Turn_Out;    // 直立环、速度环、转向环 输出

bool Fore_Enable,Back_Enable,Left_Enable,Right_Enable;  // 前进、后退、左转、右转 标志
int motor1,motor2;                         // 左右电机最终速度
int Encoder_Left,Encoder_Right;            // 左右编码器值
int Target_Speed = 0;      // 目标速度
int Turn_Speed = 0;        // 目标速度
int Med_Angle = 1;        // 平衡角度
 

short RData;                               // 蓝牙接收的数据

void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);

void vTaskFunction(void){
	xTaskCreate(vStart,"vStart",100,NULL,1,NULL);
}
void vStart(void* pvParameters){
	BaseType_t xReturn = pdPASS;
	
	taskENTER_CRITICAL();            // 停止中断
	xReturn = xTaskCreate(vOLED,"vOLED",100, NULL,1,NULL);
	if(xReturn != NULL){
		OLED_ShowString(1, 1, "OLED SUCCESS");
	}
	xReturn = xTaskCreate(vPID,"vPID",100, NULL,3,NULL);
	if(xReturn != NULL){
		OLED_ShowString(2, 1, "PID SUCCESS");
	}
	xReturn = xTaskCreate(vBluetooth,"vBluetooth",100, NULL,3,NULL);
	if(xReturn != NULL){
		OLED_ShowString(3, 2, "BT SUCCESS");
	}
	OLED_Clear();
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();     // 开启中断
}
/**
*   控制前进后退左转右转，并限制最大速度
**/
void ForeBackControl(void){
    
    if((Fore_Enable == 0) && (Back_Enable == 0)) Target_Speed = 0;   
    if(Fore_Enable == 1) Target_Speed++;
    if(Back_Enable == 1) Target_Speed--;
    Target_Speed = Target_Speed > TargetSpeedMax ? TargetSpeedMax : (Target_Speed < (-TargetSpeedMax) ? (-TargetSpeedMax) : Target_Speed);
    
    
    if((Left_Enable == 0) && (Right_Enable == 0)) Turn_Speed = 0;
    if(Left_Enable == 1) Turn_Speed+=5;
    if(Right_Enable == 1) Turn_Speed-=5;
    Turn_Speed = Turn_Speed > TurnSpeedMax ? TurnSpeedMax :(Turn_Speed < (-TurnSpeedMax) ? (-TurnSpeedMax):Turn_Speed);	
}
/**
*   控制线程
*   平衡车最终控制函数  
**/
void vPID(void* pvParameters){
	while(1){
//		Encoder_Left = Read_Speed(2);                 // 获得左电机编码器数值
//		Encoder_Right= Read_Speed(4);                 // 获得右电机编码器数值
printf("GX:%d GY:%d GZ:%d pitch:%f roll:%f yaw:%f \r\n",GX,GY,GZ,pitch,roll,yaw);
//        ForeBackControl();
//        
//        Velocity_Out = Velocity(Target_Speed,Encoder_Left,Encoder_Right);
//        Vertical_Out = Vertical(Med_Angle,pitch,GY);	
//		      
//		if((Left_Enable == 0) && (Right_Enable == 0)){
//			Turn_KD = 0;                              // 如果没有左右控制信号，则对转向环进行抑制
//		}else{
//			Turn_KD = 0;                              // 如果进行左右控制
//		}
//		
//		Turn_Out = Turn(GZ,Turn_Speed,Turn_KD);
//		
//		motor1 = Velocity_Out + Vertical_Out + Turn_Out; // 最终PWM
//		motor2 = Velocity_Out + Vertical_Out - Turn_Out; // 最终PWM

//		Limit(&motor1,&motor2);                          // 对PWM进行控制
//		Set_PWM(motor1,motor2);                          // 设置PWM到电机
		vTaskDelay(1);
	}
}
/**
*   显示线程
**/
void vOLED(void* pvParameters){
	while(1){
//		OLED_ShowString(1, 10,"p");
//		OLED_ShowString(2, 10,"Y");
//		OLED_ShowString(3, 10,"Z");
		//OLED_ShowString(4, 10,"M");

//		OLED_ShowSignedNum(1,11,pitch, 5);
//        OLED_ShowSignedNum(2,11,roll, 5);
//		OLED_ShowSignedNum(3,11,GY, 5);
//		OLED_ShowSignedNum(4,11,GZ, 5);
//        
//        OLED_ShowSignedNum(1, 1,Encoder_Left , 5);
//        OLED_ShowSignedNum(2,1,Encoder_Right, 5);
//		RData = GetBuleToothData();
////		OLED_ShowSignedNum(1, 1, RData , 5);
////        OLED_ShowSignedNum(2,1,Target_Speed, 4);
//        OLED_ShowSignedNum(3,1,Turn_Speed, 5);
//        OLED_ShowSignedNum(4,1,Turn_Out, 5);
		vTaskDelay(10);
	}
}
/**
*   蓝牙线程
**/
void vBluetooth(void* pvParameters){
//	while(1){
//		RData = GetBuleToothData();
//		
//		if(RData == 0x47){
//			Fore_Enable = 1,Back_Enable = 0,Left_Enable = 0,Right_Enable = 0;
//		}else if(RData == 0x4A){
//			Fore_Enable = 0,Back_Enable = 0,Left_Enable = 0,Right_Enable = 1;
//		}else if(RData == 0x48){
//			Fore_Enable = 0,Back_Enable = 0,Left_Enable = 1,Right_Enable = 0;
//		}else if(RData == 0x4B){
//			Fore_Enable = 0,Back_Enable = 1,Left_Enable = 0,Right_Enable = 0;
//		}else if(RData == 0x49){
//			Fore_Enable = 0,Back_Enable = 0,Left_Enable = 0,Right_Enable = 0;
//		}
////		else if(RData == 0x41){
////			PWMSpeed = 16000;
////		}else if(RData == 0x42){
////			PWMSpeed = 20000;
////		}else if(RData == 0x43){
////			PWMSpeed = 30000;
////		}else if(RData == 0x44){
////			PWMSpeed = 50000;
////		}		
//		vTaskDelay(1);
//	}
}
/**
*   中断获取MPU6050数据，
**/
void EXTI9_5_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) 
	{
		EXTI->PR=1<<5; //清楚中断标志位
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			MPU_Get_Gyroscope(&GX,&GY,&GZ);
		}	
	}	
}