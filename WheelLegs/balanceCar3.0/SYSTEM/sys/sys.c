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
void Scence_Show(void){  
    OLED_ShowString(1, 1,"Balance Car Init"); 
    OLED_ShowString(4, 1,"www.rainupup.cn");
    
    delay_myms(100);
    /**
    *   >10%
    *   >>20%
    *   >>>30%
    *   ......
    **/
    for(int i = 1;i <=10;i++){
        
        if(i<10){
            OLED_ShowString(2, i + 2,">");
            OLED_ShowNum(2,i+3,i *10,2);
            OLED_ShowString(2, i+5,"%");
        }else{
            OLED_ShowString(2, i + 2,">");
            OLED_ShowNum(2,i+3,i *10,3);
            OLED_ShowString(2, i+6,"%");
        }
        delay_myms(100);       
    }
}

void SystemHardwareInit(void){	
	NVIC_Configuration();
	delay_init();	
	OLED_Init();
	OLED_Clear();	
	delay_ms(100);
	   
	MPU_Init();	                                     //��ʼ��MPU6050
	delay_ms(10);
	
	/**
	* ע�⣺MPU_Init(); Ҫ��mpu_dmp_init()֮ǰִ��
	**/ 
	while(mpu_dmp_init())                            //��ʼ��mpu_dmp��
 	{
		printf("Initialization failed��\r\n");		//���ڳ�ʼ��ʧ���ϱ�
	}
    MPU6050_EXTI_Init();
    delay_ms(100);

//    OLED_Clear();
//	PWM_Init();
//	Encoder1_Init();
//	Encoder2_Init();
//	Bluttooth_Init();
//	MOTOR_Init();
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


