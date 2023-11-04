#ifndef __ENCODER_H
#define __ENCODER_H
//void Encoder_Init(void);
//uint32_t Get_EncoderLeft(void);
//uint32_t Get_EncoderRight(void);

void Encoder1_Init(void);
void Encoder2_Init(void);
int Read_Speed(int TIMx);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif
