#include "sys.h"


void delay_myms(int ms){    
    for(int i = 0;i < ms;i++){
        delay_us(1000);  
    }
}
/*******************************************************************************
* Function Name  : Scence_Show
* Description    : 开机逐帧显示"Balance_Car"
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



void SystemHardwareInit(void){	
	NVIC_Configuration();
	delay_init();	
    //	Bluttooth_Init();
	uart_init(115200);      // 与蓝牙模块二选一
//	Air780E_init(115200);
//    GPIO_Config();
//    delay_ms(10);
//	Servo_Init();
    MPU_Init();	                              //初始化MPU6050
	delay_ms(10);
//    MyCAN_Init();
	/**
	* 注意：MPU_Init(); 要在mpu_dmp_init()之前执行
	**/ 
	while(mpu_dmp_init())                            //初始化mpu_dmp库
 	{
		printf("Initialization failed！\r\n");		//串口初始化失败上报
	}
    
    MPU6050_EXTI_Init();
    printf("Initialization SUCCESS！\r\n");
    delay_ms(10);
}
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA,GPIOB,GPIOC,AFIO;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         //PC13是LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //对选中管脚初始化
	GPIO_SetBits(GPIOC,GPIO_Pin_13);                 //上电点亮LED
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;          //PB9是motor1的使能
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);                  //低电平解除,Motor_init()中使能
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
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;	 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
		NVIC_Init(&NVIC_InitStructure); 
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


