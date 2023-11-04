//#include "stm32f10x.h"                  // Device header

//int8_t data = 0;
//void Bluttooth_Init(void){
//	
////	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
////	
////	GPIO_InitTypeDef GPIO_InitStructure;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				//TX
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
////	
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               //RX
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_Init(GPIOB, &GPIO_InitStructure);

////	USART_InitTypeDef USART_InitStructure;
////	USART_InitStructure.USART_BaudRate = 9600;
////	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////	USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
////	USART_InitStructure.USART_Parity = USART_Parity_No;
////	USART_InitStructure.USART_StopBits = USART_StopBits_1;
////	USART_InitStructure.USART_WordLength = USART_WordLength_8b;

////	USART_Init(USART3,&USART_InitStructure);
////	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
////	
////	NVIC_InitTypeDef NVIC_InitStructure;
////	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
////	NVIC_Init(&NVIC_InitStructure);
////	
////	USART_Cmd(USART3,ENABLE);
//}
//void SentByte(uint8_t Byte){
////	USART_SendData(USART3,Byte);
////	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
//}
//void SentArr(uint8_t *Array,uint16_t length){
////	for(int i = 0;i < length;i++){
////		SentByte(Array[i]);
////	}
//}
//void SentString(char *String){
////	for(int i = 0;String[i] != '\0';i++){
////		SentByte(String[i]);
////	}
//}

//void USART3_IRQHandler (void){	
////	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) == SET){
////		data = USART_ReceiveData(USART3);
////	}	
//}
//int8_t GetBuleToothData(void){
////	return data;
//}


