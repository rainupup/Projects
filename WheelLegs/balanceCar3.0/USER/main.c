#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"



int main(void) 
{				
	SysTick_Init(72);
    SystemHardwareInit();        //Ӳ����ʼ��
//    Scence_Show();

	vTaskFunction();
	vTaskStartScheduler();          //�����������
}

