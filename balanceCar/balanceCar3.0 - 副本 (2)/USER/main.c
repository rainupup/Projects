#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"
#include "TaskManage.h"
//void Timer_Init(void){
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                  // 使能TIM2时钟
//	
//	TIM_InternalClockConfig(TIM3);                                       // 选择内部时钟源
//    
//	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitSturcture;                   
//	Tim_TimeBaseInitSturcture.TIM_CounterMode = TIM_CounterMode_Up;      // 向上计数
//    // 1s = 1hz = 72MHZ / 100000 / 7200
//	Tim_TimeBaseInitSturcture.TIM_Period = 10000-1;                      // 计数10000次，即每10000次进入一次中断 
//	Tim_TimeBaseInitSturcture.TIM_Prescaler = 7200-1;                    // 分频7200，即每振动7200次计时器加1
//    Tim_TimeBaseInitSturcture.TIM_ClockDivision = TIM_CKD_DIV1 ; 
//	Tim_TimeBaseInitSturcture.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitSturcture);                   // 初始化Timer
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                             // 定时器中断使能，触发方式更新触发

//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitTypeDef NVIC_InitStucture;
//	NVIC_InitStucture.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStucture.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStucture);
//	
//	TIM_Cmd(TIM3,ENABLE);                                                // 使能定时器计数器
//}
//void TIM3_IRQHandler(void){
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET){
//		num++;
//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//	}
//}
void HardWareInit(void){
	NVIC_Configuration();
	delay_init();	
	OLED_Init();
	OLED_Clear();	
	delay_ms(100);
	
	MPU_Init();	                                     //初始化MPU6050
	delay_ms(10);
	MPU6050_EXTI_Init();
	/**
	* 注意：MPU_Init(); 要在mpu_dmp_init()之前执行
	**/
	while(mpu_dmp_init())                            //初始化mpu_dmp库
 	{
		printf("Initialization failed！\r\n");		//串口初始化失败上报
	}

	PWM_Init();
	Encoder1_Init();
	Encoder2_Init();
	Bluttooth_Init();
	MOTOR_Init();
}
float pitch1,roll1,yaw1;
short AX1, AY1, AZ1, GX1, GY1, GZ1;

//void EXTI9_5_IRQHandler(void)
//{	
//	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) 
//	{
//		EXTI->PR=1<<5; //清楚中断标志位
//		if(mpu_dmp_get_data(&pitch1,&roll1,&yaw1)==0)
//		{
//			MPU_Get_Gyroscope(&GX1,&GY1,&GZ1);
//		}	
//	}	
//}

int main(void) 
{	
	//SystemHardwareDriverInit();			//硬件初始化
	//SysTick_Init(72);
	HardWareInit();
//	vTaskFunction();
//	vTaskStartScheduler();          //开启任务调度
	while(1)   
	{
		vTaskFunction();
		vTaskStartScheduler();          //开启任务调度
	}
}

