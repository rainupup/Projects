#include "stm32f10x.h"                  // Device header
#include "PWM.h"
int PWM_MIN = -7200,PWM_MAX = 7200;

void MOTOR_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void Limit(int *motor1,int *motor2){
	if(*motor1 < PWM_MIN)*motor1 = PWM_MIN;
	if(*motor1 > PWM_MAX)*motor1 = PWM_MAX;
	
	if(*motor2 < PWM_MIN)*motor2 = PWM_MIN;
	if(*motor2 > PWM_MAX)*motor2 = PWM_MAX;
}

/**
*	ȡ����ֵ
**/
int abs(int p){
	p = p > 0 ? p : (-p);
	return p;
}
/**
*	���÷����PWM
**/
void Set_PWM(int motor1,int motor2){
	if(motor1 < 0){
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	}else{
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	PWM_SetCompare1(abs(motor1));
	
	if(motor2 < 0){		
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);

	}else{		
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	}
	PWM_SetCompare2(abs(motor2));
}
void Stop(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}
