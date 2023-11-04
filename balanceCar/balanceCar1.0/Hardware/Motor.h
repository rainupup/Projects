#ifndef __MOTOR_H
#define __MOTOR_H
void Forward(uint16_t PWMSpeed);
void Back(uint16_t PWMSpeed);
void Right(uint16_t PWMSpeed);
void Left(uint16_t PWMSpeed);
void Stop(void);
#endif
