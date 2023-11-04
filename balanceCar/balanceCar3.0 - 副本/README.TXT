
************************************************** 文件夹说明 *************************************************

FWLIB文件夹       			STM32库文件
CORE文件夹       		 	STM32启动文件和内核函数文件
SYSTEM文件夹      			必要的延时函数和调试串口 
USER文件夹        			main函数
FreeRTOS_Cor文件夹     		freertos内核文件
FreeRTOS_Por文件夹 			freertos接口文件
MPU6050文件夹 				MPU6050相关文件库
HARDWARE文件夹    			硬件初始化文件
APPLICATION_PID				任务创建和PID计算
README              		说明文档

************************************************** 硬件连接说明 *************************************************
PB8  - SDA_OLED    OLED通讯
PB9  - SCL_OLED

PB3  - SCL_MPU     MPU6050通讯
PB4  - SDA_MPU
PB5  - INT

PA13 - SWDIO       下载调试
PA14 - SWCLK

PA9  - USART1_TX   串口通讯
PA10 - USART1_RX

PA8  - PWMA        左电机控制口
PB12 - AIN2        左电机接线
PB13 - AIN1
PA6  - OPLB        左电机编码器
PA7  - OPLA

PA11 - PWMB        右电机控制口
PB14 - BIN1        右电机接线
PB15 - BIN2
PA0  - OPRA        右电机编码器
PA1  - OPRB

PA2  - RXD_ECB02   蓝牙通讯
PA3  - TXD_ECB02
PC13 - STA_ECB02   蓝牙连接状态

PB0  - LED         前后LED灯
