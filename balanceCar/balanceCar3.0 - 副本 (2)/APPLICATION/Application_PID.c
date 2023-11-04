#include "sys.h"
#include "Application_PID.h"              //问题1

//调KP时关闭其他，当KP调整完后，调试KD，先确定KD极性，确定KD极性时关闭其他
 //确定KP极性：关闭其他后，使小车往前行驶时，轮子往后转
//  //确定KD极性：关闭其他后，使小车往前行驶时，轮子往前转
float 
	balance_KP = 290*0.6,             
	balance_KD = -1*0.6;//0.8;        // 高频振荡，不知名停机原因：可能是正反反馈电流很大，使的停机
//float 
//	Velocity_KP = 0.18,       // 确定KP极性：关闭其他，当往前转到轮子时，轮子会获得一个往前的加速度；为了让小车更快的平衡
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
*	直立环（PD控制器）
*   直立环输出=Kp1×角度偏差+Kd×角度偏差的微分
*	角度偏差=真实角度-期望角度
*	
*	Med：期望角度；Angle：真实角度；gyro_Y：真实角度
**/
// 单靠直立环无法完成持续平衡
int Vertical(float Med,float Angle,float gyro_Y){
	float Bias;
	int balance;
	Bias=Med-Angle;   
	balance=(balance_KP*Bias)+(balance_KD*gyro_Y);  	
	return balance;
}
/**
*	速度环（PI控制器）：为了赋值直立环
*	速度环输出=Kp2×电机速度偏差+Ki2×电机速度偏差的积分
*	电机速度偏差=真实速度-期望速度
**/
int Velocity(int Target,int Encoder_Left,int Encoder_Right){
	static int  Velocity,Encoder_Least,Encoder,Encoder_Integral;
	float a = 0.7;
	
	//获取最新速度偏差;测量速度（左右编码器之和）- 目标速度
	Encoder_Least = (Encoder_Left + Encoder_Right) - Target;
	
	Encoder *= 0.7;	

	Encoder += Encoder_Least*0.3;
	
	
	//对速度偏差进行低通滤波
	//Encoder = (Encoder * a) + (Encoder_Least * (1-a));
	
	//对速度偏差积分出位移
	Encoder_Integral += Encoder;
	

	//积分限幅
	Encoder_Integral = Encoder_Integral > 8000 ? 8000 : (Encoder_Integral < -8000 ? -8000 : Encoder_Integral);
	
    //速度控制	
	Velocity = Encoder * Velocity_KP + Encoder_Integral * Velocity_KI;

    // 小车跌倒
    //if()
    
	return Velocity;
}


//int Velocity(int Target,int encoder_left,int encoder_right)
//{
////	OLED_ShowSignedNum(2,1,encoder_left, 5);
////	OLED_ShowSignedNum(4,1,encoder_right, 8);
//  // 定义成静态变量，保存在静态存储器，使得变量不丢掉
//  static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;
//  float a=0.7;
//  
//  // 1.计算速度偏差
//  // 舍去误差--我的理解：能够让速度为"0"的角度，就是机械中值。
//  Encoder_Err = ((encoder_left+encoder_right)-Target);
//  // 2.对速度偏差进行低通滤波
//  // low_out = (1-a)*Ek+a*low_out_last
//  EnC_Err_Lowout = (1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // 使得波形更加平滑，滤除高频干扰，放置速度突变
//  EnC_Err_Lowout_last = EnC_Err_Lowout;   // 防止速度过大影响直立环的正常工作
//  // 3.对速度偏差积分出位移
//  Encoder_S+=EnC_Err_Lowout;
//  // 4.积分限幅
//  Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);
//  
//  // 5.速度环控制输出
//  PWM_out = Velocity_KP*EnC_Err_Lowout+Velocity_KI*Encoder_S;
//  
//  return PWM_out;
//}
/**
*	转向环
*	转向环输出=系数×Z轴角速度
**/
int Turn(int gyro_Z,int Turn_Speed,int Turn_KD){
//	return Turn_Speed * Turn_KP + gyro_Z * Turn_KD;
	return 0;
}

