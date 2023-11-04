#include "mpu_exti.h"
#include "sys.h"

/**
*   MPU6050�жϳ�ʼ�� PB5
**/
void MPU6050_EXTI_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		  //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef  NVIC_InitStructure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure); 
}
