#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"
#include "TaskManage.h"
//void Timer_Init(void){
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                  // ʹ��TIM2ʱ��
//	
//	TIM_InternalClockConfig(TIM3);                                       // ѡ���ڲ�ʱ��Դ
//    
//	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitSturcture;                   
//	Tim_TimeBaseInitSturcture.TIM_CounterMode = TIM_CounterMode_Up;      // ���ϼ���
//    // 1s = 1hz = 72MHZ / 100000 / 7200
//	Tim_TimeBaseInitSturcture.TIM_Period = 10000-1;                      // ����10000�Σ���ÿ10000�ν���һ���ж� 
//	Tim_TimeBaseInitSturcture.TIM_Prescaler = 7200-1;                    // ��Ƶ7200����ÿ��7200�μ�ʱ����1
//    Tim_TimeBaseInitSturcture.TIM_ClockDivision = TIM_CKD_DIV1 ; 
//	Tim_TimeBaseInitSturcture.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitSturcture);                   // ��ʼ��Timer
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                             // ��ʱ���ж�ʹ�ܣ�������ʽ���´���

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
//	TIM_Cmd(TIM3,ENABLE);                                                // ʹ�ܶ�ʱ��������
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
	
	MPU_Init();	                                     //��ʼ��MPU6050
	delay_ms(10);
	MPU6050_EXTI_Init();
	/**
	* ע�⣺MPU_Init(); Ҫ��mpu_dmp_init()֮ǰִ��
	**/
	while(mpu_dmp_init())                            //��ʼ��mpu_dmp��
 	{
		printf("Initialization failed��\r\n");		//���ڳ�ʼ��ʧ���ϱ�
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
//		EXTI->PR=1<<5; //����жϱ�־λ
//		if(mpu_dmp_get_data(&pitch1,&roll1,&yaw1)==0)
//		{
//			MPU_Get_Gyroscope(&GX1,&GY1,&GZ1);
//		}	
//	}	
//}

int main(void) 
{	
	//SystemHardwareDriverInit();			//Ӳ����ʼ��
	//SysTick_Init(72);
	HardWareInit();
//	vTaskFunction();
//	vTaskStartScheduler();          //�����������
	while(1)   
	{
		vTaskFunction();
		vTaskStartScheduler();          //�����������
	}
}

