#include "stm32f10x.h"                  // Device header


void Encoder_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM4);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0x0f;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising ;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //编码器接口初始化
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //编码器接口初始化

	
	TIM_SetCounter(TIM2,0);
	TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);

}
// 电机1测速
uint32_t Get_Encoder1(void){
	int Encoder_TIM;
	
	Encoder_TIM = TIM2->CNT;
	TIM2->CNT = 0;	
	
	return  Encoder_TIM;
}
uint32_t Get_Encoder2(void){
	int Encoder_TIM;
	
	Encoder_TIM = TIM4->CNT;
	TIM4->CNT = 0;
	
	return  Encoder_TIM;
}

