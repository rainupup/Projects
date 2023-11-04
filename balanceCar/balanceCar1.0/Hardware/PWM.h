#ifndef __PWM_H
#define __PWM_H
void PWM_Init(void);
void vTaskPWM(void* p);
//设置电机1的通道1PWM
void PWM_SetCompare1_1(uint16_t compare);
//设置电机1的通道2PW
void PWM_SetCompare1_2(uint16_t compare);

//设置电机2的通道1PWM
void PWM_SetCompare2_1(uint16_t compare);
//设置电机2的通道2PWM
void PWM_SetCompare2_2(uint16_t compare);
#endif
