#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"
#include "TaskManage.h"

void HardWareInit(void){
	NVIC_Configuration();
	delay_init();	
	OLED_Init();
	OLED_Clear();	
	delay_ms(100);
	MPU_Init();	                                     //��ʼ��MPU6050
	delay_ms(10);
	MPU6050_EXTI_Init();
	while(mpu_dmp_init())                            //��ʼ��mpu_dmp��
 	{
		printf("Initialization failed��\r\n");		//���ڳ�ʼ��ʧ���ϱ�
	}
//	PWM_Init();
//	Encoder_Init();
//	Bluttooth_Init();
//	MOTOR_Init();
}
float pitch1,roll1,yaw1;
short AX1, AY1, AZ1, GX1, GY1, GZ1;
void EXTI9_5_IRQHandler(void)
{	
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) 
	{
		EXTI->PR=1<<5; //����жϱ�־λ
		
		if(mpu_dmp_get_data(&pitch1,&roll1,&yaw1)==0)
		{
			MPU_Get_Gyroscope(&GX1,&GY1,&GZ1);
		}	
	}	
}
int main(void) 
{	
	//SystemHardwareDriverInit();			//Ӳ����ʼ��
	//SysTick_Init(72);
	HardWareInit();
	while(1)   
	{
//		delay_ms(20);
		OLED_ShowSignedNum(2, 1, GX1, 5);
		OLED_ShowSignedNum(3, 1, GY1, 5); 
		OLED_ShowSignedNum(4, 1, GZ1, 5); 
		OLED_ShowSignedNum(2, 7,pitch1 , 3);
		OLED_ShowSignedNum(3, 7,roll1, 3); 
		OLED_ShowSignedNum(4, 7,yaw1, 3); 
//		vTaskFunction();
//		vTaskStartScheduler();          //�����������
	}
}

