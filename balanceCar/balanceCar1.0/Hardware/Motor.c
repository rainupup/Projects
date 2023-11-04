#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
void Forward(uint16_t PWMSpeed){
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	TIM_SetCompare1(TIM3,15000);
	TIM_SetCompare2(TIM3,15000);
//	PWM_SetCompare1_1(PWMSpeed);
//	PWM_SetCompare1_2(PWMSpeed);
//	

//	PWM_SetCompare2_1(0);
//	PWM_SetCompare2_2(0);
}
void Back(uint16_t PWMSpeed){
//	TIM3->CCR2 = 5000;
//	TIM3->CCR3 = 0;
//	TIM3->CCR1 = 0;
//	TIM3->CCR4 = 5000;
	
//	TIM_SetCompare1(TIM3,0);
//	TIM_SetCompare2(TIM3,0);
//	TIM_SetCompare3(TIM3,15000);
//	TIM_SetCompare4(TIM3,15000);
	
//	PWM_SetCompare1_1(PWMSpeed);
//	PWM_SetCompare1_2(0);
//	PWM_SetCompare2_1(0);
//	PWM_SetCompare2_2(PWMSpeed);
}

void Right(uint16_t PWMSpeed){	
//	PWM_SetCompare1_1(0);
//	PWM_SetCompare1_2(PWMSpeed);
//	PWM_SetCompare2_1(0);
//	PWM_SetCompare2_2(PWMSpeed);
}
void Left(uint16_t PWMSpeed){
//	PWM_SetCompare2_1(PWMSpeed);
//	PWM_SetCompare2_2(0);
//	PWM_SetCompare1_1(PWMSpeed);
//	PWM_SetCompare1_2(0);
}
void Stop(void){
	PWM_SetCompare1_1(0);
	PWM_SetCompare1_2(0);
	PWM_SetCompare2_1(0);
	PWM_SetCompare2_2(0);
}






//void Forward(uint16_t PWMSpeed){
//	PWM_SetCompare1_1(PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_7);
//	
//	PWM_SetCompare2_1(PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_4);
//}
//void Back(uint16_t PWMSpeed){
//	PWM_SetCompare1_1(PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_7);
//	//GPIO_ResetBits (GPIOA,GPIO_Pin_7);
//	PWM_SetCompare2_1(PWMSpeed);
//	//GPIO_SetBits (GPIOA,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//}

//void Right(uint16_t PWMSpeed){
//	PWM_SetCompare1_1(PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_7);
//	
//	PWM_SetCompare2_1(~PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_4);
//	//GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//}
//void Left(uint16_t PWMSpeed){
//	PWM_SetCompare2_1(PWMSpeed);
//	GPIO_SetBits (GPIOA,GPIO_Pin_4);
//	
//	PWM_SetCompare1_1(~PWMSpeed);
//	GPIO_ResetBits (GPIOA,GPIO_Pin_7);
//}