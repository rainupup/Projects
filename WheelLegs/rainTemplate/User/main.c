#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "can.h"
#include "usart.h"
#include <stdlib.h>
#include "servo.h"

void commander_run(void);
float target;
int main(void)
{	
    uart_init(115200);
    Servo_Init();
//    MyCAN_Init();
    int c = 0;
	while(1){
//        printf("%f ",target);
        
//        CAN_SendData(target,0);
//        for(int i = 0;i < 8;i++){
//            printf("%d ",rxData[i]);
//            if(i == 7) printf("\r\n");
//        }
        
        //Serial_SendByte(0x12);
        
        uint16_t i =  Usart_GetData();

        printf("%d \r\n ",i);
//        Servo_SetAngle(8);

        Delay_ms(100);
//        commander_run();
//        printf("%f \r\n ",target);
	}
}
//void commander_run(void)
//{
//	if((USART_RX_STA&0x8000)!=0)
//	{
//		switch(USART_RX_BUF[0])
//		{
//			case 'H':
//				printf("Hello World!\r\n");
//				break;
//			case 'T':   //T6.28
//				target=atof((const char *)(USART_RX_BUF+1));
//				printf("RX=%.4f\r\n", target);
//				break;
//		}
//		USART_RX_STA=0;
//	}
//}

