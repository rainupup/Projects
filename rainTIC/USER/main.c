//#include "bsp.h"
#include "config.h"
UnionData data;
UnionData2 data2;
float Ta;
float Vdd;
float emissivity=0.95;      // 反射因子
paramsMLX90640 mlx90640;    // MLX90640结构体

// USB设备
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
	FATFS fs;       // 文件系统
	
	delay_1ms(200);
	mGPIO_Init();
	ADC_DMA_Init();
	SPI_Flash_Init();	
	f_mount(&fs,"0:",1);        // 挂载文件系统
	
	exmc_lcd_init();            
	lcd_init();                 // LCD初始化
	Lcd_GramScan();             // 设置扫描方向
	MLX90640_I2CInit();
	MLX90640_SetRefreshRate(MLX90640_ADDR, RefreshRate);            // 设置帧率
	MLX90640_SetChessMode(MLX90640_ADDR);	                        // 设置为棋盘模式
	// 使用UnionData共用体的mlx90640_Zoom10参数临时保存读取像素校正参数
    MLX90640_DumpEE(MLX90640_ADDR, data.mlx90640_Zoom10);  
    // 解析校正参数，将上方像素校正参数解析至paramsMLX90640结构体
	MLX90640_ExtractParameters(data.mlx90640_Zoom10, &mlx90640);	
    // 到此步骤UnionData共用体的mlx90640_Zoom10参数开始存储帧数据
    
	ILI9341_BK_ON; 
    while(1)
	{		
		MLX90640_I2CRead(MLX90640_ADDR, 0x8000, 1, &statusRegister);
		if(statusRegister & 0x0008)
		{
			MLX90640_GetFrameData(MLX90640_ADDR, data.mlx90640_Zoom10);     // 读取一帧原始数据
			Ta = MLX90640_GetTa(data.mlx90640_Zoom10, &mlx90640);           //读取MLX90640 外壳温度	
			Vdd = MLX90640_GetVdd(data.mlx90640_Zoom10,&mlx90640);          // 获得MLX90640电压，3.3V为正常电压，使用USB 或 电池电压正常
            MLX90640_CalculateTo(data.mlx90640_Zoom10, &mlx90640, emissivity , Ta - TA_SHIFT, data2.mlx90640To);     
            Disp_TempPic();
		}
	
		if(ADCValue[1]<300){    // ADC获得值小于300 说明SW2按下，进入U盘模拟
//			ILI9341_BK_OFF;     // 关闭背光
            LCD_Fill(0,0,320,240,WHITE);
            LCD_ShowString(40, 100,"USB flash drive MODE", RED,WHITE);
            Delay_us(20);
			break;              // 退出本次死循环
		}
		else if(ADCValue[1]<2350&&ADCValue[1]>1750) // SW1按下，截图
		{
			bmp_encode();                           // 存储为BMP文件            
		}
    }
    
    // 下方代码 初始化时钟，USB、NVIC等内容
    rcu_config();                            /* system clocks configuration */	 
	usbd_core_init(&usb_device_dev);         /* USB device configuration */
	nvic_config();                           /* NVIC configuration */
	USB_PULLUP_H();                          /* enabled USB pull-up */
	usb_device_dev.status = USBD_CONNECTED;  /* now the usb device is connected */
	while(usb_device_dev.status != USBD_CONFIGURED);

	while(1)
	{
		if(ADCValue[1]<200)         // 当再次按下，退出U盘模式，重启再次从头执行
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
	
	RCU_CTL &= ~RCU_CTL_PLLEN;  //PLL失能
	
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
    rcu_usb_clock_config(RCU_CKUSB_CKPLL_DIV2); // USB工作在48HMz,本身GD32设置的是96HMZ

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

