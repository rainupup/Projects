#include "sys.h"
float balance_KP,balance_KD;
float Velocity_KP,Velocity_KI;
float Turn_KP;
/**
*	ֱ������PD��������
*   ֱ�������=Kp1���Ƕ�ƫ��+Kd���Ƕ�ƫ���΢��
*	�Ƕ�ƫ��=��ʵ�Ƕ�-�����Ƕ�
*	
*	Med�������Ƕȣ�Angle����ʵ�Ƕȣ�gyro_Y����ʵ�Ƕ�
**/
int vertical(float Med,float Angle,float gyro_Y){
	int balance;
	
	balance = balance_KP*(Angle - Med) + balance_KD*gyro_Y;
	
	return balance;
}
/**
*	�ٶȻ���PI��������
*	�ٶȻ����=Kp2������ٶ�ƫ��+Ki2������ٶ�ƫ��Ļ���
*	����ٶ�ƫ��=��ʵ�ٶ�-�����ٶ�
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	static int  Velocity,Encoder_Least,Encoder,Encoder_Integral;
	float a = 0.7;
	
	//��ȡ�����ٶ�ƫ��;�����ٶȣ����ұ�����֮�ͣ�- Ŀ���ٶ�
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;

	//���ٶ�ƫ����е�ͨ�˲�
	Encoder = (Encoder * a) + (Encoder_Least * (1-a));
	
	//���ٶ�ƫ����ֳ�λ��
	Encoder_Integral += Encoder;
	

	//�����޷�
	Encoder_Integral = Encoder_Integral > 15000 ? 15000 : (Encoder_Integral < -15000 ? -15000 : Encoder_Integral);
	
	//�ٶȿ���	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;
//		if(angle[0]<-70 || angle[0]>70 || STA_ECB02 || encoder_left>70 || encoder_left<-70) 			
//		Encoder_Integral=0; 
    
	return Velocity;
}
/**
*	ת��
*	ת�����=ϵ����Z����ٶ�
**/
int Turn(int gyro_Z){
	return 
		Turn_KP * gyro_Z;
}

