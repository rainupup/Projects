#include "sys.h"
#include "Application_PID.h"              //����1

//��KPʱ�ر���������KP������󣬵���KD����ȷ��KD���ԣ�ȷ��KD����ʱ�ر�����
 //ȷ��KP���ԣ��ر�������ʹС����ǰ��ʻʱ����������ת
//  //ȷ��KD���ԣ��ر�������ʹС����ǰ��ʻʱ��������ǰת
float 
	balance_KP = 290*0.6,             
	balance_KD = -1*0.6;//0.8;        // ��Ƶ�񵴣���֪��ͣ��ԭ�򣺿������������������ܴ�ʹ��ͣ��
//float 
//	Velocity_KP = 0.18,       // ȷ��KP���ԣ��ر�����������ǰת������ʱ�����ӻ���һ����ǰ�ļ��ٶȣ�Ϊ����С�������ƽ��
//	Velocity_KI = 0.018;//0.02;
//float 
//	Turn_KP = 2,
//	Turn_KD = 0;

//float 
//	balance_KP = 0,             
//	balance_KD = 0;
float Velocity_KP = -3;
float Velocity_KI =-3/200;
float 
	Turn_KP = 0,
	Turn_KD = 0;
/**
*	ֱ������PD��������
*   ֱ�������=Kp1���Ƕ�ƫ��+Kd���Ƕ�ƫ���΢��
*	�Ƕ�ƫ��=��ʵ�Ƕ�-�����Ƕ�
*	
*	Med�������Ƕȣ�Angle����ʵ�Ƕȣ�gyro_Y����ʵ�Ƕ�
**/
// ����ֱ�����޷���ɳ���ƽ��
int Vertical(float Med,float Angle,float gyro_Y){
	float Bias;
	int balance;
	Bias=Med-Angle;   
	balance=(balance_KP*Bias)+(balance_KD*gyro_Y);  	
	return balance;
}
/**
*	�ٶȻ���PI����������Ϊ�˸�ֱֵ����
*	�ٶȻ����=Kp2������ٶ�ƫ��+Ki2������ٶ�ƫ��Ļ���
*	����ٶ�ƫ��=��ʵ�ٶ�-�����ٶ�
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	static int  Velocity,Encoder_Least,Encoder,Encoder_Integral;
	float a = 0.7;
	
	//��ȡ�����ٶ�ƫ��;�����ٶȣ����ұ�����֮�ͣ�- Ŀ���ٶ�
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;
	
	Encoder *= 0.7;	

	Encoder += Encoder_Least*0.3;
	
	
	//���ٶ�ƫ����е�ͨ�˲�
	//Encoder = (Encoder * a) + (Encoder_Least * (1-a));
	
	//���ٶ�ƫ����ֳ�λ��
	Encoder_Integral += Encoder;
	

	//�����޷�
	Encoder_Integral = Encoder_Integral > 8000 ? 8000 : (Encoder_Integral < -8000 ? -8000 : Encoder_Integral);
	
    //�ٶȿ���	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;

    // С������
    //if()
    
	return Velocity;
}


//int Velocity(int Target,int encoder_left,int encoder_right)
//{
////	OLED_ShowSignedNum(2,1,encoder_left, 5);
////	OLED_ShowSignedNum(4,1,encoder_right, 8);
//  // ����ɾ�̬�����������ھ�̬�洢����ʹ�ñ���������
//  static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;
//  float a=0.7;
//  
//  // 1.�����ٶ�ƫ��
//  // ��ȥ���--�ҵ���⣺�ܹ����ٶ�Ϊ"0"�ĽǶȣ����ǻ�е��ֵ��
//  Encoder_Err = ((encoder_left+encoder_right)-Target);
//  // 2.���ٶ�ƫ����е�ͨ�˲�
//  // low_out = (1-a)*Ek+a*low_out_last
//  EnC_Err_Lowout = (1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // ʹ�ò��θ���ƽ�����˳���Ƶ���ţ������ٶ�ͻ��
//  EnC_Err_Lowout_last = EnC_Err_Lowout;   // ��ֹ�ٶȹ���Ӱ��ֱ��������������
//  // 3.���ٶ�ƫ����ֳ�λ��
//  Encoder_S+=EnC_Err_Lowout;
//  // 4.�����޷�
//  Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);
//  
//  // 5.�ٶȻ��������
//  PWM_out = Velocity_KP*EnC_Err_Lowout+Velocity_KI*Encoder_S;
//  
//  return PWM_out;
//}
/**
*	ת��
*	ת�����=ϵ����Z����ٶ�
**/
int Turn(int gyro_Z,int Turn_Speed,int Turn_KD){
//	return Turn_Speed * Turn_KP + gyro_Z * Turn_KD;
	return 0;
}

