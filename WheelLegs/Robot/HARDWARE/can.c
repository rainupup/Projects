#include "sys.h"                 // Device header

uint8_t motorID = 1;
void MyCAN_Init(void)//CAN��ʼ������
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��GPIOAʱ��
	GPIO_InitTypeDef GPIO_InitStructure;                        //GPIO����
    //RX
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;            //����Ϊ��������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;                //��11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;            //����Ϊ��������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;                //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1);//PA11 ����Ϊ CAN1 
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1);//PA12 ����Ϊ CAN1 

    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);        //��CANʱ��
	CAN_InitTypeDef CAN_InitStructure;                          //����CAN

    
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;                   //����������2Tq
	CAN_InitStructure.CAN_BS1  = CAN_BS1_9tq;                   //TBS1����5Tq
	CAN_InitStructure.CAN_BS2  = CAN_BS2_8tq;                   //TBS2����5Tq
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;               //����ģʽѡ��
//    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack; 
//    CAN_InitStructure.CAN_Prescaler = 80;                       //80��Ƶ�����յõ�10kB���ʣ�
    CAN_InitStructure.CAN_Prescaler = 4;
    


	CAN_InitStructure.CAN_ABOM = DISABLE;                       //�ض�����
	CAN_InitStructure.CAN_AWUM = DISABLE;                       //�ض�����
	CAN_InitStructure.CAN_NART = DISABLE;                        //��ֹ�ط�
	CAN_InitStructure.CAN_RFLM = DISABLE;                       //������FIFO
	CAN_InitStructure.CAN_TTCM = DISABLE;                       //�ر�ʱ�䴥��
	CAN_InitStructure.CAN_TXFP = DISABLE;                       //���Ͱ�ID���ȼ�����������˳��
	CAN_Init(CAN1, &CAN_InitStructure);
	
    
	CAN_FilterInitTypeDef CAN_FilterInitStructure;              //CANɸѡ������
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//����ģʽ
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//32λ����	
    
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;      //ʹ��ɸѡ��
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//����FIFO0
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x00;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x00;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x00;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x00;         //ʵ���Ͽ�ͨ������ID

	CAN_FilterInitStructure.CAN_FilterNumber = 0;               //ѡ��ɸѡ����0
	
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2����ռ2����Ӧ
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  //ָ��CAN�����жϣ������������������ǻ����ͣ���Ҫע��һ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //�����ռ�ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��2��Ӧ�ȼ�
	NVIC_Init(&NVIC_InitStructure);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);                    //ʹ�ܽ����ж�
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
//    CAN_InitStructure.CAN_Prescaler = 2;          // CAN��Ƶ
//    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//    CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
//    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
//    CAN_InitStructure.CAN_TTCM = DISABLE;       // �Ƿ�ʹ�� TTCM ʱ�䴥������
//    CAN_InitStructure.CAN_ABOM = ENABLE;        // �Զ�����
//    CAN_InitStructure.CAN_AWUM = DISABLE;       // �Բ�������
//    CAN_InitStructure.CAN_NART = ENABLE;        // ���·���
//    CAN_InitStructure.CAN_RFLM = DISABLE;       // ������ FIFO ����
//    CAN_InitStructure.CAN_TXFP = ENABLE;        // FIFO���ȷ���
//    
//    CAN_Init(CAN1,&CAN_InitStructure);
//    
//    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;              /* ������ʹ�� */
//    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;     // ����
//    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//    CAN_FilterInitStructure.CAN_FilterNumber = 0;                       /* ѡ��������� */  
//    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;    /* ������λ�� */
//    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0; /* ����������FIFO */

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
    
//    if(CanRxMsgStructure.StdId == 0x100 && motorID == 1){           // ���IDΪ1������0x100����֡
//        for(int i = 0;i < 8;i++){
//            rxData[i] = CanRxMsgStructure.Data[i];
//        }
//    }else if(CanRxMsgStructure.StdId == 0x200 && motorID == 2){     // ���IDΪ2������0x200����֡ 
//        for(int i = 0;i < 8;i++){
//            rxData[i] = CanRxMsgStructure.Data[i];
//        }
//    }
}
//void USB_LP_CAN1_RX0_IRQHandler()   //CAN�����жϷ��������ǻ�����ʹ��PA11��12����ʱ��ʹ�ø��жϺ�����
//{
////	CanRxMsg RxMessage;             //�������ݽṹ��
////	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);   //���պ���
//	int i = 0;
//    CanRxMsg CanRxMsgStructure;
//    CAN_Receive(CAN1,CAN_FIFO0,&CanRxMsgStructure);
//    printf("*************************************************\r\n");
//    printf("%d \r\n",CanRxMsgStructure.StdId);
//    for(i = 0;i < 8;i++){
//        rxData[i] = CanRxMsgStructure.Data[i];  
//        printf("%d \r\n",rxData[i]);
//    }
////	get_DLC = RxMessage.DLC;//�������ݳ���
////	get_EXID = RxMessage.ExtId;//������չID
////	get_FMI = RxMessage.FMI;//������������ɸѡ��
////	get_IDE = RxMessage.IDE;//��׼/��չIDʶ��
////	get_RTR = RxMessage.RTR;//����/ң��֡ʶ��
////	get_STID = RxMessage.StdId;//���±�׼ID
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
////    CanTxMsgStructure.StdId = motorID + 0x100;   // ָ������ID
//    
//    CanTxMsgStructure.StdId = 0x100;   // ָ������ID
//    CanTxMsgStructure.ExtId = 0x0000;
//    CanTxMsgStructure.IDE = CAN_ID_STD;     // ��׼֡
//    CanTxMsgStructure.RTR = CAN_RTR_DATA;   // ����֡
//    CanTxMsgStructure.DLC = 8;              // ���ݳ���
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
    
    printf("���ͳɹ�\r\n");
}
//#include "stm32f10x.h"                  // Device header
//#include "MyProject.h"
//uint32_t get_STID;//�洢��׼ID
//uint32_t get_EXID;//�洢��չID
//uint8_t get_IDE;//��׼/��չIDʶ��
//uint8_t get_RTR;//����/ң��֡ʶ��
//uint8_t get_DLC;//���ݳ���ʶ��
//uint8_t get_DATA[8];//�洢����
//uint8_t get_FMI;//ʶ����������ɸѡ��
 


 
//void send_CAN(uint32_t STID, uint32_t EXID, uint8_t IDE, uint8_t RTR, uint8_t DLC, uint8_t DATA[8])//CAN���ͺ���
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
