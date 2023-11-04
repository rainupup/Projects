#include "sys.h"


void delay_myms(int ms){    
    for(int i = 0;i < ms;i++){
        delay_us(1000);  
    }
}
/*******************************************************************************
* Function Name  : Scence_Show
* Description    : ������֡��ʾ"Balance_Car"
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



void SystemHardwareInit(void){	
	NVIC_Configuration();
	delay_init();	
    //	Bluttooth_Init();
	uart_init(115200);      // ������ģ���ѡһ
//	Air780E_init(115200);
//    GPIO_Config();
//    delay_ms(10);
//	Servo_Init();
    MPU_Init();	                              //��ʼ��MPU6050
	delay_ms(10);
//    MyCAN_Init();
	/**
	* ע�⣺MPU_Init(); Ҫ��mpu_dmp_init()֮ǰִ��
	**/ 
	while(mpu_dmp_init())                            //��ʼ��mpu_dmp��
 	{
		printf("Initialization failed��\r\n");		//���ڳ�ʼ��ʧ���ϱ�
	}
    
    MPU6050_EXTI_Init();
    printf("Initialization SUCCESS��\r\n");
    delay_ms(10);
}
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOA,GPIOB,GPIOC,AFIO;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         //PC13��LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //�ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //��ѡ�йܽų�ʼ��
	GPIO_SetBits(GPIOC,GPIO_Pin_13);                 //�ϵ����LED
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;          //PB9��motor1��ʹ��
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);                  //�͵�ƽ���,Motor_init()��ʹ��
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : �ж����ȼ�����
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


