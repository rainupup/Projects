#ifndef __APPLICATION_PID_H
#define __APPLICATION_PID_H

extern float Turn_KP,Turn_KD;

int Vertical(float Med,float Angle,float gyro_Y);
//int Vertical(float Med,float Angle,short gyro_Y);
int Velocity(int Target,int Encoder_Left,int Encoder_Right);
int Turn(int gyro_Z,int Turn_Speed,int Turn_KD);
#endif

