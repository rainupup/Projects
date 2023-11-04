#ifndef __MOTOR_H
#define __MOTOR_H
void MOTOR_Init(void);
void Limit(int *motor1,int *motor2);
void Set_PWM(int motor1,int motor2);
void Stop(void);
#endif
