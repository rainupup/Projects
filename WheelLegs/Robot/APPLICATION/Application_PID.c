#include "sys.h"
#include "Application_PID.h"              //问题1

// 调KP时关闭其他，当KP调整完后，调试KD，先确定KD极性，确定KD极性时关闭其他
// 确定KP极性：关闭其他后，使小车往前行驶时，轮子往前转
// 确定KD极性：关闭其他后，使小车往前行驶时，轮子往后转
float 
	balance_KP = 500*0.6,           // 调试到低频大范围振荡
	balance_KD = -1.5*0.6;          // 调试到高频低范围振荡；不知名停机原因：可能是正反反馈电流很大，使的停机
float 
    Velocity_KP = 28,               // 极性的确定：关闭其他，往前转轮子，轮子速度回加速到最大
    Velocity_KI = 28/200;
float 
	Turn_KP = -5,
	Turn_KD = 0;

/**
*	直立环（PD控制器）：单靠直立环无法完成持续平衡
*   直立环输出=Kp1×角度偏差+Kd×角度偏差的微分
*	角度偏差=真实角度-期望角度
*	
*	Med：期望角度；Angle：真实角度；gyro_Y：真实角度
**/
int Vertical(float Med,float Angle,float gyro_Y){
	float Bias;
	int balance;
	Bias=Med-Angle;   
	balance=(balance_KP*Bias)+(balance_KD*gyro_Y);  	
	return balance;
}
/**
*	速度环（PI控制器）：辅助直立环，更快保存平衡
*	速度环输出=Kp2×电机速度偏差+Ki2×电机速度偏差的积分
*	电机速度偏差=真实速度-期望速度
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	// 定义成静态变量，保存在静态存储器，使得变量不丢掉
    static int  
        Velocity,              // 最终速度
        Encoder_Least,         // 最新速度
        Encoder,               // 上一次的速度
        Encoder_Integral;      // 积分

	
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;   //获取最新速度偏差;测量速度（左右编码器之和）- 目标速度
	
    // 对速度偏差进行低通滤波
	Encoder *= 0.7;	               // 上一次速度占70%权重
	Encoder += Encoder_Least*0.3;  // 最新速度占30%权重
	
	// 对速度偏差积分出位移
	Encoder_Integral += Encoder;
	// 积分限幅
	Encoder_Integral = Encoder_Integral > 8000 ? 8000 : (Encoder_Integral < -8000 ? -8000 : Encoder_Integral);
	
    // 最终速度环速度	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;

    if(pitch > 75 || pitch < -75) Encoder_Integral = 0;           // 小车跌倒积分清零
    
	return Velocity;
}

/**
*	转向环
*	转向环输出=系数×Z轴角速度
**/
int Turn(int gyro_Z,int Turn_Speed,float Turn_KD){
	return Turn_Speed * Turn_KP + gyro_Z * Turn_KD;
}

