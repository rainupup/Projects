#ifndef __CONFIG_H
#define	__CONFIG_H
#include "gd32f10x.h"
#include "systick.h"
#include "GPIO.h"
#include "TIM.h"
#include "gd32f103c_lcd_eval.h"
#include <stdio.h>
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"
#include "MLX90640.h"
#include "usbd_std.h"
#include "msc_core.h"
#include "ADCKey.h"
#include "XT25F128.h"
#include <string.h>
#include "MLX90640.h"
#include <MLX90640_API.h>
#include "MLX90640_I2C_Driver.h"


#include "diskio.h"
#include "ff.h"
#include "bmp.h"

// ����C8T6�ڴ�ռ䲻�㣬ʹ�ù����壬�ص㣺ȫ����������ͬһ��ռ�
typedef union{
	uint16_t mlx90640_Zoom10[834];              // �������MLX90640��EEPROM��ȫ��832���ֵ��¶ȼ���У׼���ݣ������洢һ֡ԭʼ���� 832���ֽ�
	uint8_t  DisBuf[10*320];
	uint8_t  SPI_FLASH_BUF[4096];
}UnionData;

typedef union{
	uint16_t mlx90640To[768];                   // �������ص��¶� 32 * 24 = 768
	uint16_t databuf[640];  
	uint8_t  bbb_data[MSC_MEDIA_PACKET_SIZE];
}UnionData2;

void rcu_config(void);
void gpio_config(void);
void nvic_config(void);

extern UnionData data;
extern UnionData2 data2;

#endif

