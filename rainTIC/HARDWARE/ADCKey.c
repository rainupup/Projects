#include "ADCKey.h"
uint16_t ADCValue[2];       // [0] ��ʾ��ص�ѹ��[1] ��ʾ����
void ADC_DMA_Init(void){
    dma_parameter_struct dma_Init_Structure;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_ADC0);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);        // ADC��Ƶ
    
    gpio_init(GPIOA,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_0 | GPIO_PIN_1);   // ADC ���ų�ʼ����ģ������

    
    dma_deinit(DMA0,DMA_CH0);     // ʧ��
    dma_Init_Structure.periph_addr  = (uint32_t)(&ADC_RDATA(ADC0)); // ADC0
    dma_Init_Structure.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;  // ���費����
    dma_Init_Structure.memory_addr  = (uint32_t)(ADCValue);         // �������ݵ�����
    dma_Init_Structure.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;   // ����
    dma_Init_Structure.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;   // 16λ��ȣ�����
    dma_Init_Structure.memory_width = DMA_MEMORY_WIDTH_16BIT;       // 16λ��ȣ�����    
    dma_Init_Structure.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_Init_Structure.number       = 2;                            // ͨ������
    dma_Init_Structure.priority     = DMA_PRIORITY_HIGH;            // �����ȼ�
    
    dma_init(DMA0, DMA_CH0, &dma_Init_Structure);                   
    dma_circulation_enable(DMA0, DMA_CH0);                          // DMAѭ��ģʽ
    dma_channel_enable(DMA0, DMA_CH0);	
    
    /*
        GD �� STM32 ������GDû��ADC�Ľṹ��
    */
    adc_deinit(ADC0);                                           // ����ADC
    adc_mode_config(ADC_MODE_FREE);                             // ADC �����ڶ���ģʽ
    adc_special_function_config(ADC0,ADC_SCAN_MODE,ENABLE);            // ɨ��ģʽ
    adc_special_function_config(ADC0,ADC_CONTINUOUS_MODE,ENABLE);      // ����ģʽ
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);       // �Ҷ���
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 2);    // ͨ������
    
    adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_0, ADC_SAMPLETIME_55POINT5);                    // ʹ�ù����飬����ʱ��55.5����
    adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_1, ADC_SAMPLETIME_55POINT5);	
    
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);   // �������
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

    adc_enable(ADC0);               // ʹ��
    delay_1ms(1);       
    adc_calibration_enable(ADC0);   // У׼��λ
    adc_dma_mode_enable(ADC0);      // adc dma
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL); // �������
}
