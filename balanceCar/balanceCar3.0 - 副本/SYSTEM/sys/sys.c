#include "sys.h"

/*******************************************************************************
* Function Name  : Scence_Show
* Description    : 开机逐帧显示"Balance_Car"
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Scence_Show(void)
{
//	char k1=0;
//	char Show_array1[]={"Balance_Car"};
//	
//	for(k1=0;k1<11;k1++)
//	{
//		if(k1>0 && k1<4)
//		{
//			delay_ms(200);
//			OLED_ShowChar(2,3+k1,Show_array1[k1]);
//		}
//		else
//		{
//			delay_ms(200);
//			OLED_ShowChar(2,3+k1,Show_array1[k1]);
//		}		
//	}
//	delay_ms(500);
//	OLED_Clear();
}

/*******************************************************************************
* Function Name  : SystemHardwareDriverInit
* Description    : 硬件初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SystemHardwareDriverInit(void)
{	
//	NVIC_Configuration();
	delay_init();	    							
	OLED_Init();
	OLED_Clear();	
//	delay_ms(1000);
//	Scence_Show();
//	uart_init(115200);	 		
	
	PWM_Init();
	Encoder_Init();
	Bluttooth_Init();
//	MOTOR_Init();	
//	BlueTooth_init(115200);	
//	Encoder_Init_TIM2();					
//	Encoder_Init_TIM3();					
//	LED_Init();
//	TIM4_Int_Init(9999,7199);
//	
	MPU_Init();	                                     //初始化MPU6050
//	MPU6050_EXTI_Init();
	mpu_dmp_init();
//	while(mpu_dmp_init())                            //初始化mpu_dmp库
// 	{
//		printf("Initialization failed！\r\n");		//串口初始化失败上报
//	}
}


/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : 中断优先级配置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
		NVIC_InitTypeDef  NVIC_InitStructure;		
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x06;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
		
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x09;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
}


