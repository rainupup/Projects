#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define TargetSpeedMax   300               // 最大速度
#define TurnSpeedMax   300                 // 最大转弯速度
#define LED_blink    GPIOC->ODR^=(1<<13)
float pitch,roll,yaw;
short AX, AY, AZ, GX, GY, GZ;

int Vertical_Out,Velocity_Out,Turn_Out;    // 直立环、速度环、转向环 输出

bool Fore_Enable,Back_Enable,Left_Enable,Right_Enable;  // 前进、后退、左转、右转 标志
int motor1,motor2;                         // 左右电机最终速度
int Encoder_Left,Encoder_Right;            // 左右编码器值
int Target_Speed = 0;      // 目标速度
int Turn_Speed = 0;        // 目标速度
int Med_Angle = 1;         // 平衡角度
 
int16_t RData;                               // 蓝牙接收的数据

void vStart(void* pvParameters);
void vPID(void* pvParameters);
void vOLED(void* pvParameters);
void vBluetooth(void* pvParameters);
void vAIR780E(void* pvParameters);

void vTaskFunction(void){
	xTaskCreate(vStart,"vStart",100,NULL,1,NULL);
}

void vStart(void* pvParameters){
	BaseType_t xReturn = pdPASS;
	
	taskENTER_CRITICAL();            // 停止中断
	xReturn = xTaskCreate(vOLED,"vOLED",100, NULL,3,NULL);
//	if(xReturn != NULL){
//		OLED_ShowString(1, 1, "OLED SUCCESS");
//	}
	xReturn = xTaskCreate(vPID,"vPID",100, NULL,3,NULL);
	if(xReturn != NULL){
//		OLED_ShowString(2, 1, "PID SUCCESS");
	}
//    xReturn = xTaskCreate(vAIR780E,"vAIR780E",100, NULL,3,NULL);
//	if(xReturn != NULL){
////		OLED_ShowString(3, 2, "AIR780E SUCCESS");
//	}
    
//	xReturn = xTaskCreate(vBluetooth,"vBluetooth",100, NULL,3,NULL);
//	if(xReturn != NULL){
//		OLED_ShowString(3, 2, "BT SUCCESS");
//	}
//	OLED_Clear();
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();     // 开启中断
}
/**
*   控制前进后退左转右转，并限制最大速度
**/
void ForeBackControl(void){
    
//    if((Fore_Enable == 0) && (Back_Enable == 0)) Target_Speed = 0;   
//    if(Fore_Enable == 1) Target_Speed++;
//    if(Back_Enable == 1) Target_Speed--;
//    Target_Speed = Target_Speed > TargetSpeedMax ? TargetSpeedMax : (Target_Speed < (-TargetSpeedMax) ? (-TargetSpeedMax) : Target_Speed);
//    
//    
//    if((Left_Enable == 0) && (Right_Enable == 0)) Turn_Speed = 0;
//    if(Left_Enable == 1) Turn_Speed+=5;
//    if(Right_Enable == 1) Turn_Speed-=5;
//    Turn_Speed = Turn_Speed > TurnSpeedMax ? TurnSpeedMax :(Turn_Speed < (-TurnSpeedMax) ? (-TurnSpeedMax):Turn_Speed);	
}
/**
*   控制线程
*   平衡车最终控制函数  
**/


void vPID(void* pvParameters){
//	uint32_t target;
    while(1){
        
//		Encoder_Left = Read_Speed(2);                 // 获得左电机编码器数值
//		Encoder_Right= Read_Speed(4);                 // 获得右电机编码器数值

//        ForeBackControl();
//        printf("vPID SUCCESS！\r\n");

//        MPU_Get_Gyroscope(&GX,&GY,&GZ);
//        printf("MPU SUCCESS！\r\n");
//        MPU_Get_Gyroscope(&GX,&GY,&GZ);
        printf("GX:%d GY:%d GZ:%d\r\n",GX,GZ,GY);
//        CAN_SendData(1,2);
//        
//       printf("ID:%d \r\n",MPU_Read_Byte(MPU_DEVICE_ID_REG));
    
//        float angle;
//        target = Uart_Receive();
//        printf("target = %d\r\n",target);
//         Servo_SetAngle(50);
//        angle=(u16)(50.0 * target / 9.0 + 249.0);
//        printf("angle = %f\r\n",angle);
//        
//        TIM_SetCompare1(TIM2,angle);
//        TIM_SetCompare2(TIM2,angle);
//        
//        pidTest();
        
//        printf("%d \r\n",Res);
        
//        Velocity_Out = Velocity(Target_Speed,Encoder_Left,Encoder_Right);
//        Vertical_Out = Vertical(Med_Angle,pitch,GY);	
//		      
//		
//		Turn_Out = Turn(GZ,Turn_Speed,Turn_KD);
//		
//		motor1 = Velocity_Out + Vertical_Out + Turn_Out; // 最终PWM
//		motor2 = Velocity_Out + Vertical_Out - Turn_Out; // 最终PWM
		
        vTaskDelay(50);
        
	}
}

/**
*   显示线程
**/
void vOLED(void* pvParameters){
	while(1){
////		OLED_ShowString(1, 10,"p");
////		OLED_ShowString(2, 10,"Y");
////		OLED_ShowString(3, 10,"Z");
//		//OLED_ShowString(4, 10,"M");
//		
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
        LED_blink;	
        vTaskDelay(500);
	}
}
/**
*   AIR780E线程
**/
void vAIR780E(void* pvParameters){
	while(1){
		RData = GetAir780EData();
        
//        printf("16: %x \r\n",RData);
        
        
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
        
		vTaskDelay(1);
	}
}

/**
*   蓝牙线程
**/
void vBluetooth(void* pvParameters){
	while(1){
//		RData = GetBuleToothData();
//        
//        printf("%d \r\n",RData);
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
//		vTaskDelay(1);
	}
}
/**
*   中断获取MPU6050数据，
**/
void EXTI9_5_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) 
	{
        printf("MPU SUCCESS！\r\n");
		EXTI->PR=1<<5; //清楚中断标志位
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{printf("GX:%d GY:%d GZ:%d pitch:%f roll:%f yaw:%f \r\n",GX,GY,GZ,pitch,roll,yaw);
			MPU_Get_Gyroscope(&GX,&GY,&GZ);
		}	
	}	
}
float pid_val = 0;
void pidTest(void)
{
    static float P=2,D =0 ,Err,preErr;
		//滤波，降低系统敏感性
    float a = 0.30;
    Err=preErr * a;
    Err += roll * (1-a);
    
    
    //计算PID
    pid_val += Err * P + (preErr - Err) *D;
    
    //PID_VAL限幅，定时器自动重装载值是20000，可控制舵机的比较值范围就是500~2500
    if(pid_val < 500) pid_val = 300;
    if(pid_val > 1200) pid_val = 1200;
    printf("roll = %f pid_val = %f \r\n",roll,pid_val);
    //应用
    TIM_SetCompare1(TIM2, pid_val);
    
    preErr = Err;
}
