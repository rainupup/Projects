#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "TaskManage.h"



//int fputc( int ch, FILE *f )
//{
//	//while((USART1->SR >> 7) == 0);
//	while((USART3->SR & (1 << 7)) == 0);
//	USART3->DR = ch;
//	return ch;
//}
void HardWareInit(void){
	delay_init();	
	OLED_Init();
	mpu_dmp_init();
	MPU_Init();
	PWM_Init();
	Encoder_Init();
	Bluttooth_Init();
	MOTOR_Init();
}

int main(void)
{	
	
	HardWareInit();
	
	vTaskFunction();
	vTaskStartScheduler();
}


