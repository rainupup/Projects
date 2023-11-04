#include "stm32f10x.h"                  // Device header
#include "servo.h"


void Servo_Init(void){

    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef         TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStructure.TIM_Prescaler=72 - 1;
	TIM_TimeBaseInitStructure.TIM_Period=20000 - 1;  //50Hz
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}
void Servo_SetAngle(float Angle){
    TIM_SetCompare1(TIM2, Angle / 180 * 2000 + 500);
    TIM_SetCompare2(TIM2, Angle / 180 * 2000 + 500);
}
