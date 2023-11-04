#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"



int main(void) 
{				
	SysTick_Init(72);
    SystemHardwareInit();        //硬件初始化
//    Scence_Show();

	vTaskFunction();
	vTaskStartScheduler();          //开启任务调度
}

