#include "sys.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "SysTick.h"

short X, Y, Z, X, Y, Z;
float pitch1,roll1,yaw1;
int main(void) 
{				
	SysTick_Init(72);
    SystemHardwareInit();        //硬件初始化

    
//    while(1){
////        delay_ms(1000);
////        MPU_Get_Gyroscope(&X,&Y,&Z);
////        mpu_dmp_get_data(&pitch1,&roll1,&yaw1);

//    }
	vTaskFunction();
	vTaskStartScheduler();          //开启任务调度
}

