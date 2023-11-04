#include "sys.h"
#include "Application_PID.h"              //����1

// ��KPʱ�ر���������KP������󣬵���KD����ȷ��KD���ԣ�ȷ��KD����ʱ�ر�����
// ȷ��KP���ԣ��ر�������ʹС����ǰ��ʻʱ��������ǰת
// ȷ��KD���ԣ��ر�������ʹС����ǰ��ʻʱ����������ת
float 
	balance_KP = 500*0.6,           // ���Ե���Ƶ��Χ��
	balance_KD = -1.5*0.6;          // ���Ե���Ƶ�ͷ�Χ�񵴣���֪��ͣ��ԭ�򣺿������������������ܴ�ʹ��ͣ��
float 
    Velocity_KP = 28,               // ���Ե�ȷ�����ر���������ǰת���ӣ������ٶȻؼ��ٵ����
    Velocity_KI = 28/200;
float 
	Turn_KP = -5,
	Turn_KD = 0;

/**
*	ֱ������PD��������������ֱ�����޷���ɳ���ƽ��
*   ֱ�������=Kp1���Ƕ�ƫ��+Kd���Ƕ�ƫ���΢��
*	�Ƕ�ƫ��=��ʵ�Ƕ�-�����Ƕ�
*	
*	Med�������Ƕȣ�Angle����ʵ�Ƕȣ�gyro_Y����ʵ�Ƕ�
**/
int Vertical(float Med,float Angle,float gyro_Y){
	float Bias;
	int balance;
	Bias=Med-Angle;   
	balance=(balance_KP*Bias)+(balance_KD*gyro_Y);  	
	return balance;
}
/**
*	�ٶȻ���PI��������������ֱ���������챣��ƽ��
*	�ٶȻ����=Kp2������ٶ�ƫ��+Ki2������ٶ�ƫ��Ļ���
*	����ٶ�ƫ��=��ʵ�ٶ�-�����ٶ�
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	// ����ɾ�̬�����������ھ�̬�洢����ʹ�ñ���������
    static int  
        Velocity,              // �����ٶ�
        Encoder_Least,         // �����ٶ�
        Encoder,               // ��һ�ε��ٶ�
        Encoder_Integral;      // ����

	
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;   //��ȡ�����ٶ�ƫ��;�����ٶȣ����ұ�����֮�ͣ�- Ŀ���ٶ�
	
    // ���ٶ�ƫ����е�ͨ�˲�
	Encoder *= 0.7;	               // ��һ���ٶ�ռ70%Ȩ��
	Encoder += Encoder_Least*0.3;  // �����ٶ�ռ30%Ȩ��
	
	// ���ٶ�ƫ����ֳ�λ��
	Encoder_Integral += Encoder;
	// �����޷�
	Encoder_Integral = Encoder_Integral > 8000 ? 8000 : (Encoder_Integral < -8000 ? -8000 : Encoder_Integral);
	
    // �����ٶȻ��ٶ�	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;

    if(pitch > 75 || pitch < -75) Encoder_Integral = 0;           // С��������������
    
	return Velocity;
}

/**
*	ת��
*	ת�����=ϵ����Z����ٶ�
**/
int Turn(int gyro_Z,int Turn_Speed,float Turn_KD){
	return Turn_Speed * Turn_KP + gyro_Z * Turn_KD;
}

