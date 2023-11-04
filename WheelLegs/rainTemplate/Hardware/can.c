#include "stm32f10x.h"                  // Device header
#include "can.h"
uint8_t motorID;

void MyCAN_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //CAN_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //CAN_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    
    CAN_InitStructure.CAN_Prescaler = 2;          // CAN��Ƶ
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStructure.CAN_TTCM = DISABLE;       // �Ƿ�ʹ�� TTCM ʱ�䴥������
    CAN_InitStructure.CAN_ABOM = ENABLE;        // �Զ�����
    CAN_InitStructure.CAN_AWUM = DISABLE;       // �Բ�������
    CAN_InitStructure.CAN_NART = ENABLE;        // ���·���
    CAN_InitStructure.CAN_RFLM = DISABLE;       // ������ FIFO ����
    CAN_InitStructure.CAN_TXFP = ENABLE;        // FIFO���ȷ���
    
    CAN_Init(CAN1,&CAN_InitStructure);
    
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;              /* ������ʹ�� */
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;     // ����
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterNumber = 0;                       /* ѡ��������� */  
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;    /* ������λ�� */
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0; /* ����������FIFO */

    CAN_FilterInit(&CAN_FilterInitStructure);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}
uint8_t rxData[8];
void USB_LP_CAN1_RX0_IRQHandler(void){
    CanRxMsg CanRxMsgStructure;
    CAN_Receive(CAN1,CAN_FIFO0,&CanRxMsgStructure);
        
    for(int i = 0;i < 8;i++){
        rxData[i] = CanRxMsgStructure.Data[i];
    }
}
void CAN_SendData(float angle,float speed){
    CanTxMsg CanTxMsgStructure;
    CanTxMsgStructure.StdId = 0x100;   // ָ������ID
    CanTxMsgStructure.ExtId = 0x0000;
    CanTxMsgStructure.IDE = CAN_ID_STD;     // ��׼֡
    CanTxMsgStructure.RTR = CAN_RTR_DATA;   // ����֡
    CanTxMsgStructure.DLC = 8;              // ���ݳ���
    
     
    CanTxMsgStructure.Data[0] = angle;
    CanTxMsgStructure.Data[1] = speed;
    
    CAN_Transmit(CAN1,&CanTxMsgStructure);
}
