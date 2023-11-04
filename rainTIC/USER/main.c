//#include "bsp.h"
#include "config.h"
UnionData data;
UnionData2 data2;
float Ta;
float Vdd;
float emissivity=0.95;      // ��������
paramsMLX90640 mlx90640;    // MLX90640�ṹ��

// USB�豸
usbd_core_handle_struct  usb_device_dev = 
{
    .dev_desc = (uint8_t *)&device_descripter,
    .config_desc = (uint8_t *)&configuration_descriptor,
    .strings = usbd_strings,
    .class_init = msc_init,
    .class_deinit = msc_deinit,
    .class_req_handler = msc_req_handler,
    .class_data_handler = msc_data_handler
};
int main(void)  
{  
    uint16_t statusRegister;
	FATFS fs;       // �ļ�ϵͳ
	
	delay_1ms(200);
	mGPIO_Init();
	ADC_DMA_Init();
	SPI_Flash_Init();	
	f_mount(&fs,"0:",1);        // �����ļ�ϵͳ
	
	exmc_lcd_init();            
	lcd_init();                 // LCD��ʼ��
	Lcd_GramScan();             // ����ɨ�跽��
	MLX90640_I2CInit();
	MLX90640_SetRefreshRate(MLX90640_ADDR, RefreshRate);            // ����֡��
	MLX90640_SetChessMode(MLX90640_ADDR);	                        // ����Ϊ����ģʽ
	// ʹ��UnionData�������mlx90640_Zoom10������ʱ�����ȡ����У������
    MLX90640_DumpEE(MLX90640_ADDR, data.mlx90640_Zoom10);  
    // ����У�����������Ϸ�����У������������paramsMLX90640�ṹ��
	MLX90640_ExtractParameters(data.mlx90640_Zoom10, &mlx90640);	
    // ���˲���UnionData�������mlx90640_Zoom10������ʼ�洢֡����
    
	ILI9341_BK_ON; 
    while(1)
	{		
		MLX90640_I2CRead(MLX90640_ADDR, 0x8000, 1, &statusRegister);
		if(statusRegister & 0x0008)
		{
			MLX90640_GetFrameData(MLX90640_ADDR, data.mlx90640_Zoom10);     // ��ȡһ֡ԭʼ����
			Ta = MLX90640_GetTa(data.mlx90640_Zoom10, &mlx90640);           //��ȡMLX90640 ����¶�	
			Vdd = MLX90640_GetVdd(data.mlx90640_Zoom10,&mlx90640);          // ���MLX90640��ѹ��3.3VΪ������ѹ��ʹ��USB �� ��ص�ѹ����
            MLX90640_CalculateTo(data.mlx90640_Zoom10, &mlx90640, emissivity , Ta - TA_SHIFT, data2.mlx90640To);     
            Disp_TempPic();
		}
	
		if(ADCValue[1]<300){    // ADC���ֵС��300 ˵��SW2���£�����U��ģ��
//			ILI9341_BK_OFF;     // �رձ���
            LCD_Fill(0,0,320,240,WHITE);
            LCD_ShowString(40, 100,"USB flash drive MODE", RED,WHITE);
            Delay_us(20);
			break;              // �˳�������ѭ��
		}
		else if(ADCValue[1]<2350&&ADCValue[1]>1750) // SW1���£���ͼ
		{
			bmp_encode();                           // �洢ΪBMP�ļ�            
		}
    }
    
    // �·����� ��ʼ��ʱ�ӣ�USB��NVIC������
    rcu_config();                            /* system clocks configuration */	 
	usbd_core_init(&usb_device_dev);         /* USB device configuration */
	nvic_config();                           /* NVIC configuration */
	USB_PULLUP_H();                          /* enabled USB pull-up */
	usb_device_dev.status = USBD_CONNECTED;  /* now the usb device is connected */
	while(usb_device_dev.status != USBD_CONFIGURED);

	while(1)
	{
		if(ADCValue[1]<200)         // ���ٴΰ��£��˳�U��ģʽ�������ٴδ�ͷִ��
		{
			NVIC_SystemReset();	
		}		
	}		
}

static void system_clock_96m_hxtal(void)
{
    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_HXTAL;
	
	RCU_CTL &= ~RCU_CTL_PLLEN;  //PLLʧ��
	
    /* CK_PLL = (CK_HXTAL/2) * 24 = 96 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_4);
    RCU_CFG0 |= RCU_PLL_MUL24;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLL;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLL)){
    }
}

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
	system_clock_96m_hxtal();
	
    /* enable USB pull-up pin clock */ 
    rcu_periph_clock_enable(RCU_GPIOA);
	
    /* enable the power clock */
    rcu_periph_clock_enable(RCU_PMU);

    /* configure USB model clock from PLL clock */
    rcu_usb_clock_config(RCU_CKUSB_CKPLL_DIV2); // USB������48HMz,����GD32���õ���96HMZ

    /* enable USB APB1 clock */
    rcu_periph_clock_enable(RCU_USBD);
}

/*!
    \brief      configure interrupt priority
    \param[in]  none
    \param[out] none
    \retval     none
*/
void nvic_config(void)
{
    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    /* enable the USB low priority interrupt */
    nvic_irq_enable(USBD_LP_CAN0_RX0_IRQn, 1, 0);
}

