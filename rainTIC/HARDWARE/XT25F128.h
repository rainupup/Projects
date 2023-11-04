#ifndef __XT25F128_H
#define __XT25F128_H
#include "CONFIG.h"
#define  SPI_FLASH_PAGE_SIZE           0x100
#define SPI_PORT            GPIOA
#define SPI_CS_PIN          GPIO_PIN_4
#define SPI_SCK_PIN          GPIO_PIN_5
#define SPI_MISO_PIN          GPIO_PIN_6
#define SPI_MOSI_PIN          GPIO_PIN_7
#define SPI_FLASH_CS_HIGH() gpio_bit_set(SPI_PORT,GPIO_PIN_4)
#define SPI_FLASH_CS_LOW()  gpio_bit_reset(SPI_PORT,GPIO_PIN_4)

//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void SPI_Flash_Init(void);
uint16_t  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
uint8_t	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void SPI_FLASH_Write_SR(uint8_t sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Enable(void);  //дʹ�� 
void SPI_FLASH_Write_Disable(void);	//д����
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);//��������
void SPI_Flash_Wait_Busy(void);           //�ȴ�����
void SPI_Flash_PowerDown(void);           //�������ģʽ
void SPI_Flash_WAKEUP(void);			  //����

#endif


