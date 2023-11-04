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

// 由于C8T6内存空间不足，使用共用体，特点：全部参数共用同一块空间
typedef union{
	uint16_t mlx90640_Zoom10[834];              // 起初保存MLX90640中EEPROM的全部832个字的温度计算校准数据，后来存储一帧原始数据 832个字节
	uint8_t  DisBuf[10*320];
	uint8_t  SPI_FLASH_BUF[4096];
}UnionData;

typedef union{
	uint16_t mlx90640To[768];                   // 保存像素点温度 32 * 24 = 768
	uint16_t databuf[640];  
	uint8_t  bbb_data[MSC_MEDIA_PACKET_SIZE];
}UnionData2;

void rcu_config(void);
void gpio_config(void);
void nvic_config(void);

extern UnionData data;
extern UnionData2 data2;

#endif

