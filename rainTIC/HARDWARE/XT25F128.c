#include "XT25F128.h"

// SPI 初始化
void SPI_Flash_Init(void){
    
    spi_parameter_struct spi_initStructure;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_SPI0);

    gpio_init(SPI_PORT,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,SPI_MOSI_PIN | SPI_SCK_PIN);   // 初始化MOSI 和 SCK
    gpio_init(SPI_PORT,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,SPI_MISO_PIN);           // 初始化 MISO 
    gpio_init(SPI_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,SPI_CS_PIN);                  // 初始化片选引脚
    
    SPI_FLASH_CS_HIGH();
    
    spi_initStructure.device_mode = SPI_MASTER;                 // 主机模式
    spi_initStructure.trans_mode = SPI_TRANSMODE_FULLDUPLEX;    // 下降沿
    spi_initStructure.frame_size = SPI_FRAMESIZE_8BIT;          // 8位数据位
    spi_initStructure.nss = SPI_NSS_SOFT;                       // 软件触发
    spi_initStructure.endian = SPI_ENDIAN_MSB;                  // 高位先行
    spi_initStructure.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;    // 低电平有效
    spi_initStructure.prescale = SPI_PSC_8;                     // 8分频
    spi_init(SPI0, &spi_initStructure);
    
    spi_crc_polynomial_set(SPI0,7);                             // CRC
    
    spi_enable(SPI0);
}

uint8_t spi_flash_send_byte(uint8_t byte)
{
    /* loop while data register in not emplty */
    while (RESET == spi_i2s_flag_get(SPI0,SPI_FLAG_TBE));

    /* send byte through the SPI0 peripheral */
    spi_i2s_data_transmit(SPI0,byte);

    /* wait to receive a byte */
    while(RESET == spi_i2s_flag_get(SPI0,SPI_FLAG_RBNE));

    /* return the byte read from the SPI bus */
    return(spi_i2s_data_receive(SPI0));
}

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
uint8_t SPI_Flash_ReadSR(void)   
{  
	uint8_t byte=0;   
	SPI_FLASH_CS_LOW();                             //使能器件   
	spi_flash_send_byte(W25X_ReadStatusReg);        //发送读取状态寄存器命令    
	byte=spi_flash_send_byte(0Xff);                 //读取一个字节  
	SPI_FLASH_CS_HIGH();                            //取消片选     
	return byte;   
} 
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void SPI_FLASH_Write_SR(uint8_t sr)   
{   
	SPI_FLASH_CS_LOW();                             //使能器件   
	spi_flash_send_byte(W25X_WriteStatusReg);       //发送写取状态寄存器命令    
	spi_flash_send_byte(sr);                        //写入一个字节  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
}   
//SPI_FLASH写使能	
//将WEL置位   
void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_WriteEnable);          //发送写使能  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 
//SPI_FLASH写禁止	
//将WEL清零  
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_WriteDisable);         //发送写禁止指令    
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 			    
//读取芯片ID W25X16的ID:0XEF14
//          XT25F128 ID:0XB7
uint16_t SPI_Flash_ReadID(void)
{
	uint16_t Temp = 0;	  
	SPI_FLASH_CS_LOW();				    
	spi_flash_send_byte(0x90);//发送读取ID命令	    
	spi_flash_send_byte(0x00); 	    
	spi_flash_send_byte(0x00); 	    
	spi_flash_send_byte(0x00); 	 			   
	Temp|=spi_flash_send_byte(0xFF)<<8;  
	Temp|=spi_flash_send_byte(0xFF);	 
	SPI_FLASH_CS_HIGH();				    
	return Temp;
}   		    
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	uint16_t i;    												    
	SPI_FLASH_CS_LOW();                                 //使能器件   
    spi_flash_send_byte(W25X_ReadData);                 //发送读取命令   
    spi_flash_send_byte((uint8_t)((ReadAddr)>>16));     //发送24bit地址    
    spi_flash_send_byte((uint8_t)((ReadAddr)>>8));   
    spi_flash_send_byte((uint8_t)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=spi_flash_send_byte(0XFF);           //循环读数  
    }
	SPI_FLASH_CS_HIGH();                                //取消片选     	      
}  
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void SPI_Flash_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
 	uint16_t i;  
    SPI_FLASH_Write_Enable();                           //SET WEL 
	SPI_FLASH_CS_LOW();                                 //使能器件   
    spi_flash_send_byte(W25X_PageProgram);              //发送写页命令   
    spi_flash_send_byte((uint8_t)((WriteAddr)>>16));    //发送24bit地址    
    spi_flash_send_byte((uint8_t)((WriteAddr)>>8));   
    spi_flash_send_byte((uint8_t)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)spi_flash_send_byte(pBuffer[i]);//循环写数  
	SPI_FLASH_CS_HIGH();                                //取消片选 
	SPI_Flash_Wait_Busy();					            //等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void SPI_Flash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)  

// W25Q128 有256个块，每个块有16个扇区，每个扇区有16页，每页有256个bit
// 256 * 16 * 16 * 256
// 一个扇区有4096个bit
void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
    
	secpos = WriteAddr / 4096;//扇区地址 0~511 for w25x16
	secoff = WriteAddr % 4096;//在扇区内的偏移
	secremain = 4096-secoff;//扇区剩余空间大小   

	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	
    while(1) 
	{	
        // 由于FLASH不能写入1，只能写入0，所以要先读出原有的数据，将内存擦除后(0XFF),再将读出的数据写入
		SPI_Flash_Read(data.SPI_FLASH_BUF,secpos*4096,4096);//读出整个扇区的内容
		
        for(i=0;i<secremain;i++)//校验数据
		{
			if(data.SPI_FLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			SPI_Flash_Erase_Sector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				data.SPI_FLASH_BUF[i+secoff]=pBuffer[i];    // 将刚才读出的数据 和 要写入的数据放在一起，再写入	  
			}
			SPI_Flash_Write_NoCheck(data.SPI_FLASH_BUF,secpos*4096,4096);//写入整个扇区  

		} else {
            SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 			
        }            
		
        if(NumByteToWrite==secremain){
            break;      //写入结束了
		}else {         //写入未结束，跨页
			secpos++;   //扇区地址增1
			secoff=0;   //偏移位置为0 	 
		   	pBuffer+=secremain;  //指针偏移
			WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
	};	 	 
}
//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr)   
{   
	Dst_Addr*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_SectorErase);      //发送扇区擦除指令 
    spi_flash_send_byte((uint8_t)((Dst_Addr)>>16));  //发送24bit地址    
    spi_flash_send_byte((uint8_t)((Dst_Addr)>>8));   
    spi_flash_send_byte((uint8_t)Dst_Addr);  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
    SPI_Flash_Wait_Busy();   				   //等待擦除完成
}  
//等待空闲
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void SPI_Flash_PowerDown(void)   
{ 
  	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_PowerDown);        //发送掉电命令  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
    Delay_us(3);                               //等待TPD  
}   
//唤醒
void SPI_Flash_WAKEUP(void)   
{  
  	SPI_FLASH_CS_LOW();                            //使能器件   
    spi_flash_send_byte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
    Delay_us(3);                               //等待TRES1
}   
