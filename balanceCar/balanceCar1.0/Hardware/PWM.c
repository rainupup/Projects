#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"



void vTaskPWM(void* p);

void PWM_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_InternalClockConfig(TIM3);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 7199;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 100;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);	
	TIM_OC3Init(TIM3,&TIM_OCInitStructure); 
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);

//	TIM_ITConfig(TIM3,  TIM_IT_Update,ENABLE);
	
//	NVIC_PriorityGroupConfig(2);
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

//void TIM3_IRQHandler(){
//	}
//	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//		vTaskPWM();
//		v = 1;
//	}
//	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != SET){
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//		vTaskPWM();
//		v = 0;
//	}
//}

void vTaskPWM(void * p){
	while(1){
		if(TIM3->CNT < TIM3->CCR3){
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
		}else {
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		}
		if(TIM3->CNT < TIM3->CCR4){
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
		}else {
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		}
		vTaskDelay(1);
	} 
}

//电机1的软件PWM
void PWM_SetCompare1_1(uint16_t compare){
	TIM_SetCompare4(TIM3,compare);
}
//电机1的硬件PWM
void PWM_SetCompare1_2(uint16_t compare){
	TIM_SetCompare2(TIM3,compare);
}
//电机2的软件PWM
void PWM_SetCompare2_1(uint16_t compare){
	TIM_SetCompare3(TIM3,compare);
}
//电机2的硬件PWM
void PWM_SetCompare2_2(uint16_t compare){
	TIM_SetCompare1(TIM3,compare);
}	

// 硬件控制PWM,这个为单电机两个PWM输出
//void PWM_Init(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

//	TIM_InternalClockConfig(TIM3);
//	TIM_InternalClockConfig(TIM2);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
//	
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure); 
//	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	
//	TIM_OC4Init(TIM2,&TIM_OCInitStructure);        //PA3电机1PWM
//	TIM_OC2Init(TIM3,&TIM_OCInitStructure);        //PA7电机1PWM
//	
//	TIM_OC3Init(TIM2,&TIM_OCInitStructure);        //PA2电机2PWM
//	TIM_OC1Init(TIM3,&TIM_OCInitStructure);        //PA6电机2PWM

//	TIM_Cmd(TIM3, ENABLE);
//	TIM_Cmd(TIM2, ENABLE);
//}
////设置电机1的通道1PWM
//void PWM_SetCompare1_1(uint16_t compare){
//	TIM_SetCompare4(TIM2,compare);
//}
////设置电机1的通道2PW
//void PWM_SetCompare1_2(uint16_t compare){
//	TIM_SetCompare2(TIM3,compare);
//}

////设置电机2的通道1PWM
//void PWM_SetCompare2_1(uint16_t compare){
//	TIM_SetCompare1(TIM3,compare);
//}
////设置电机2的通道2PWM
//void PWM_SetCompare2_2(uint16_t compare){
//	TIM_SetCompare3(TIM2,compare);
//}


//void PWM1_Init(void){
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

//	TIM_InternalClockConfig(TIM2);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             // 输出PWM，控制速度
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;             // 控制方向
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);

//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
//	
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure); 
//	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC4Init(TIM2,&TIM_OCInitStructure);

//	TIM_Cmd(TIM2, ENABLE);
//}

//void PWM2_Init(void){
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

//	TIM_InternalClockConfig(TIM3);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
//	
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure); 
//	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	
//	TIM_OC1Init(TIM3,&TIM_OCInitStructure);

//	TIM_Cmd(TIM3, ENABLE);
//}

