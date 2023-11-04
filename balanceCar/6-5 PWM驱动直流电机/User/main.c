#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "PWM.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
	//Motor_Init();
	PWM_Init();
	Key_Init();
	int16_t PWMSpeed;
	OLED_ShowString(1, 1, "Speed:");
	while(1){
		KeyNum = Key_GetNum();
		
		if(KeyNum == 1){
			PWMSpeed+=10;
		}
		if(PWMSpeed >= 100){
			PWMSpeed = 0;
		}
//		
//		PWM_SetCompare1_1(0);
//		PWM_SetCompare1_2(PWMSpeed);

		//PWM_SetCompare1_1(PWMSpeed);
		PWM_SetCompare2_4(PWMSpeed);
		OLED_ShowSignedNum(1, 10, PWMSpeed, 3);
			
	}
//	while (1)
//	{
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			Speed += 20;
//			if (Speed > 100)
//			{
//				Speed = -100;
//			}
//			
//		}
//		PWM_SetCompare2_4(Speed);
////		PWM_SetCompare2_4(0);
////		PWM_SetCompare3_2(Speed);
//		//GPIO_SetBits(GPIOA,GPIO_Pin_7);
//		//GPIO_ResetBits(GPIOA,GPIO_Pin_7 );
//		//PWM_SetCompare3_2(0);
//		OLED_ShowSignedNum(1, 7, Speed, 3);
//	}
}
