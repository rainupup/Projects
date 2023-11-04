#include "sys.h"                 // Device header

uint8_t motorID = 1;
void MyCAN_Init(void)//CAN初始化函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStructure;                        //GPIO配置
    //RX
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;            //配置为复用推挽
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;                //打开11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;            //配置为复用推挽
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;                //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1);//PA11 复用为 CAN1 
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1);//PA12 复用为 CAN1 

    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);        //开CAN时钟
	CAN_InitTypeDef CAN_InitStructure;                          //配置CAN

    
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;                   //最大调整步长2Tq
	CAN_InitStructure.CAN_BS1  = CAN_BS1_9tq;                   //TBS1长度5Tq
	CAN_InitStructure.CAN_BS2  = CAN_BS2_8tq;                   //TBS2长度5Tq
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;               //工作模式选择
//    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack; 
//    CAN_InitStructure.CAN_Prescaler = 80;                       //80分频（最终得到10kB速率）
    CAN_InitStructure.CAN_Prescaler = 4;
    


	CAN_InitStructure.CAN_ABOM = DISABLE;                       //关动休眠
	CAN_InitStructure.CAN_AWUM = DISABLE;                       //关动唤醒
	CAN_InitStructure.CAN_NART = DISABLE;                        //禁止重发
	CAN_InitStructure.CAN_RFLM = DISABLE;                       //不锁定FIFO
	CAN_InitStructure.CAN_TTCM = DISABLE;                       //关闭时间触发
	CAN_InitStructure.CAN_TXFP = DISABLE;                       //发送按ID优先级，不按邮箱顺序
	CAN_Init(CAN1, &CAN_InitStructure);
	
    
	CAN_FilterInitTypeDef CAN_FilterInitStructure;              //CAN筛选器配置
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//掩码模式
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//32位长度	
    
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;      //使能筛选器
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//启用FIFO0
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x00;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x00;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x00;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x00;         //实际上可通过任意ID

	CAN_FilterInitStructure.CAN_FilterNumber = 0;               //选择筛选器组0
	
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2个抢占2个响应
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  //指向CAN接收中断，定义在中容量量产非互联型，需要注意一下
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //最高抢占等级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //第2响应等级
	NVIC_Init(&NVIC_InitStructure);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);                    //使能接收中断
}
//void MyCAN_Init(void){
//    CAN_InitTypeDef CAN_InitStructure;
//    CAN_FilterInitTypeDef CAN_FilterInitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE); 
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//    
//    
//   
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //CAN_RX
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //CAN_TX
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//    
//    
//    CAN_InitStructure.CAN_Prescaler = 2;          // CAN分频
//    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//    CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
//    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
//    CAN_InitStructure.CAN_TTCM = DISABLE;       // 是否使能 TTCM 时间触发功能
//    CAN_InitStructure.CAN_ABOM = ENABLE;        // 自动离线
//    CAN_InitStructure.CAN_AWUM = DISABLE;       // 自不动唤醒
//    CAN_InitStructure.CAN_NART = ENABLE;        // 重新发送
//    CAN_InitStructure.CAN_RFLM = DISABLE;       // 不锁定 FIFO 功能
//    CAN_InitStructure.CAN_TXFP = ENABLE;        // FIFO优先发送
//    
//    CAN_Init(CAN1,&CAN_InitStructure);
//    
//    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;              /* 过滤器使能 */
//    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;     // 掩码
//    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterNumber = 0;                       /* 选择过滤器组 */  
//    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;    /* 过滤器位宽 */
//    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0; /* 过滤器关联FIFO */

//    CAN_FilterInit(&CAN_FilterInitStructure);
//    
//    
//    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_Init(&NVIC_InitStructure);
//}
uint8_t  rxData[8];
void USB_LP_CAN1_RX0_IRQHandler(void){
    int i = 0;
    CanRxMsg CanRxMsgStructure;
    CAN_Receive(CAN1,CAN_FIFO0,&CanRxMsgStructure);
    printf("*************************************************\r\n");
    printf("%d \r\n",CanRxMsgStructure.StdId);
    for(i = 0;i < 8;i++){
        rxData[i] = CanRxMsgStructure.Data[i];  
        printf("%d \r\n",rxData[i]);
    }
    
//    if(CanRxMsgStructure.StdId == 0x100 && motorID == 1){           // 电机ID为1，接收0x100数据帧
//        for(int i = 0;i < 8;i++){
//            rxData[i] = CanRxMsgStructure.Data[i];
//        }
//    }else if(CanRxMsgStructure.StdId == 0x200 && motorID == 2){     // 电机ID为2，接收0x200数据帧 
//        for(int i = 0;i < 8;i++){
//            rxData[i] = CanRxMsgStructure.Data[i];
//        }
//    }
}
//void USB_LP_CAN1_RX0_IRQHandler()   //CAN接收中断服务函数。非互联型使用PA11、12引脚时，使用该中断函数名
//{
////	CanRxMsg RxMessage;             //接收数据结构体
////	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);   //接收函数
//	int i = 0;
//    CanRxMsg CanRxMsgStructure;
//    CAN_Receive(CAN1,CAN_FIFO0,&CanRxMsgStructure);
//    printf("*************************************************\r\n");
//    printf("%d \r\n",CanRxMsgStructure.StdId);
//    for(i = 0;i < 8;i++){
//        rxData[i] = CanRxMsgStructure.Data[i];  
//        printf("%d \r\n",rxData[i]);
//    }
////	get_DLC = RxMessage.DLC;//接下数据长度
////	get_EXID = RxMessage.ExtId;//接下拓展ID
////	get_FMI = RxMessage.FMI;//接下所经过的筛选器
////	get_IDE = RxMessage.IDE;//标准/拓展ID识别
////	get_RTR = RxMessage.RTR;//数据/遥控帧识别
////	get_STID = RxMessage.StdId;//接下标准ID
////	
////	get_DATA[0] = RxMessage.Data[0];
////	get_DATA[1] = RxMessage.Data[1];
////	get_DATA[2] = RxMessage.Data[2];
////	get_DATA[3] = RxMessage.Data[3];
////	get_DATA[4] = RxMessage.Data[4];
////	get_DATA[5] = RxMessage.Data[5];
////	get_DATA[6] = RxMessage.Data[6];
////	get_DATA[7] = RxMessage.Data[7];
//}
//void CAN_SendData(float angle,float speed){
void CAN_SendData(uint8_t angle,uint8_t speed){
//    CanTxMsg CanTxMsgStructure;
////    CanTxMsgStructure.StdId = motorID + 0x100;   // 指定发送ID
//    
//    CanTxMsgStructure.StdId = 0x100;   // 指定发送ID
//    CanTxMsgStructure.ExtId = 0x0000;
//    CanTxMsgStructure.IDE = CAN_ID_STD;     // 标准帧
//    CanTxMsgStructure.RTR = CAN_RTR_DATA;   // 数据帧
//    CanTxMsgStructure.DLC = 8;              // 数据长度
//    
//     
//    CanTxMsgStructure.Data[0] = angle;
//    CanTxMsgStructure.Data[1] = speed;
//    
//    CAN_Transmit(CAN1,&CanTxMsgStructure);
    
    CanTxMsg TxMessage;
	TxMessage.DLC = 8;
	TxMessage.StdId = 0x100;
	TxMessage.ExtId = 0x0000;
//	TxMessage.IDE = CAN_Id_Standard;
    TxMessage.IDE = CAN_Id_Extended;
	TxMessage.RTR = CAN_RTR_DATA;	
	
	TxMessage.Data[0] = 0;
	TxMessage.Data[1] = 1;
	TxMessage.Data[2] = 2;
	TxMessage.Data[3] = 4;
	TxMessage.Data[4] = 5;
	TxMessage.Data[5] = 6;
	TxMessage.Data[6] = 7;
	TxMessage.Data[7] = 8;
	
    uint8_t TransmitMailbox;
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);  
    printf("box %d\r\n",TransmitMailbox);
    while(CAN_TransmitStatus(CAN1,TransmitMailbox) ==  CAN_TxStatus_Failed);
    
    printf("发送成功\r\n");
}
//#include "stm32f10x.h"                  // Device header
//#include "MyProject.h"
//uint32_t get_STID;//存储标准ID
//uint32_t get_EXID;//存储拓展ID
//uint8_t get_IDE;//标准/拓展ID识别
//uint8_t get_RTR;//数据/遥控帧识别
//uint8_t get_DLC;//数据长度识别
//uint8_t get_DATA[8];//存储数据
//uint8_t get_FMI;//识别所经过的筛选器
 


 
//void send_CAN(uint32_t STID, uint32_t EXID, uint8_t IDE, uint8_t RTR, uint8_t DLC, uint8_t DATA[8])//CAN发送函数
//{
//	CanTxMsg TxMessage;
//	TxMessage.DLC = DLC;
//	TxMessage.StdId = STID;
//	TxMessage.ExtId = EXID;
//	TxMessage.IDE = IDE;
//	TxMessage.RTR = RTR;	
//	
//	TxMessage.Data[0] = DATA[0];
//	TxMessage.Data[1] = DATA[1];
//	TxMessage.Data[2] = DATA[2];
//	TxMessage.Data[3] = DATA[3];
//	TxMessage.Data[4] = DATA[4];
//	TxMessage.Data[5] = DATA[5];
//	TxMessage.Data[6] = DATA[6];
//	TxMessage.Data[7] = DATA[7];
//	
//	CAN_Transmit(CAN1, &TxMessage);
//}
