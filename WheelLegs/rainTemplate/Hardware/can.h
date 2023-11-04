#ifndef __CAN_H
#define __CAN_H
extern uint8_t rxData[8];
void MyCAN_Init(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void CAN_SendData(float angle,float speed);

#endif
