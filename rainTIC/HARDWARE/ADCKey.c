#include "ADCKey.h"
uint16_t ADCValue[2];       // [0] 显示电池电压，[1] 显示开关
void ADC_DMA_Init(void){
    dma_parameter_struct dma_Init_Structure;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_ADC0);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);        // ADC分频
    
    gpio_init(GPIOA,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_0 | GPIO_PIN_1);   // ADC 引脚初始化，模拟输入

    
    dma_deinit(DMA0,DMA_CH0);     // 失能
    dma_Init_Structure.periph_addr  = (uint32_t)(&ADC_RDATA(ADC0)); // ADC0
    dma_Init_Structure.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;  // 外设不自增
    dma_Init_Structure.memory_addr  = (uint32_t)(ADCValue);         // 储存数据的数组
    dma_Init_Structure.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;   // 自增
    dma_Init_Structure.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;   // 16位宽度，半字
    dma_Init_Structure.memory_width = DMA_MEMORY_WIDTH_16BIT;       // 16位宽度，半字    
    dma_Init_Structure.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_Init_Structure.number       = 2;                            // 通道数量
    dma_Init_Structure.priority     = DMA_PRIORITY_HIGH;            // 高优先级
    
    dma_init(DMA0, DMA_CH0, &dma_Init_Structure);                   
    dma_circulation_enable(DMA0, DMA_CH0);                          // DMA循环模式
    dma_channel_enable(DMA0, DMA_CH0);	
    
    /*
        GD 与 STM32 有区别，GD没有ADC的结构体
    */
    adc_deinit(ADC0);                                           // 重置ADC
    adc_mode_config(ADC_MODE_FREE);                             // ADC 运行于独立模式
    adc_special_function_config(ADC0,ADC_SCAN_MODE,ENABLE);            // 扫描模式
    adc_special_function_config(ADC0,ADC_CONTINUOUS_MODE,ENABLE);      // 连续模式
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);       // 右对齐
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 2);    // 通道长度
    
    adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_0, ADC_SAMPLETIME_55POINT5);                    // 使用规则组，采样时间55.5周期
    adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_1, ADC_SAMPLETIME_55POINT5);	
    
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);   // 软件触发
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

    adc_enable(ADC0);               // 使能
    delay_1ms(1);       
    adc_calibration_enable(ADC0);   // 校准复位
    adc_dma_mode_enable(ADC0);      // adc dma
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL); // 软件触发
}
