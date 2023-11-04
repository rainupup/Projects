#include "sys.h"
float balance_KP,balance_KD;
float Velocity_KP,Velocity_KI;
float Turn_KP;
/**
*	直立环（PD控制器）
*   直立环输出=Kp1×角度偏差+Kd×角度偏差的微分
*	角度偏差=真实角度-期望角度
*	
*	Med：期望角度；Angle：真实角度；gyro_Y：真实角度
**/
int vertical(float Med,float Angle,float gyro_Y){
	int balance;
	
	balance = balance_KP*(Angle - Med) + balance_KD*gyro_Y;
	
	return balance;
}
/**
*	速度环（PI控制器）
*	速度环输出=Kp2×电机速度偏差+Ki2×电机速度偏差的积分
*	电机速度偏差=真实速度-期望速度
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	static int  Velocity,Encoder_Least,Encoder,Encoder_Integral;
	float a = 0.7;
	
	//获取最新速度偏差;测量速度（左右编码器之和）- 目标速度
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;

	//对速度偏差进行低通滤波
	Encoder = (Encoder * a) + (Encoder_Least * (1-a));
	
	//对速度偏差积分出位移
	Encoder_Integral += Encoder;
	

	//积分限幅
	Encoder_Integral = Encoder_Integral > 15000 ? 15000 : (Encoder_Integral < -15000 ? -15000 : Encoder_Integral);
	
	//速度控制	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;
//		if(angle[0]<-70 || angle[0]>70 || STA_ECB02 || encoder_left>70 || encoder_left<-70) 			
//		Encoder_Integral=0; 
    
	return Velocity;
}
/**
*	转向环
*	转向环输出=系数×Z轴角速度
**/
int Turn(int gyro_Z){
	return 
		Turn_KP * gyro_Z;
}

