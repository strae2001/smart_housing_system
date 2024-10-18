#include "my_ADC.h"

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma;

void myADC_Init(uint32_t* desArr, uint32_t len)
{
    hadc.Instance = ADC1;
    hadc.Init.ContinuousConvMode = ENABLE;             	// 连续转换模式
    hadc.Init.NbrOfConversion = 2;                      // 规则组转换个数(菜单中菜的个数)
    hadc.Init.DiscontinuousConvMode = DISABLE;          // 失能间断转换模式
    hadc.Init.NbrOfDiscConversion = 0;
    hadc.Init.ScanConvMode = ADC_SCAN_ENABLE;               // 使能扫描模式
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;        // 软件触发转换
	HAL_ADC_Init(&hadc);
    HAL_ADCEx_Calibration_Start(&hadc);         // ADC自动校准
    
    // ADC规则组通道配置(Rank菜单配置)
    myADC_channelConfig(ADC_CHANNEL_0, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_239CYCLES_5);
	myADC_channelConfig(ADC_CHANNEL_1, ADC_REGULAR_RANK_2, ADC_SAMPLETIME_239CYCLES_5);

    // ADC结合DMA
    __HAL_RCC_DMA1_CLK_ENABLE();
    myADC_DMA_Init();
    __HAL_LINKDMA(&hadc, DMA_Handle, hdma);  
    HAL_ADC_Start_DMA(&hadc, desArr, len);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_ADC1_CLK_ENABLE();

        RCC_PeriphCLKInitTypeDef  PeriphClkInit;
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;        // 6分频72mhz时钟 得到12mhz 符合ADC时钟频率
        HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInit);

        GPIO_InitTypeDef GPIO_Init;
        GPIO_Init.Pin = GAS_SENSOR | LIGHT_SENSOR;
        GPIO_Init.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOA, &GPIO_Init);
    }
}

void myADC_channelConfig(uint32_t channel, uint32_t rank, uint32_t stime)
{
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = channel;
    sConfig.Rank = rank;
    sConfig.SamplingTime = stime;
    HAL_ADC_ConfigChannel(&hadc, &sConfig);
}

void myADC_DMA_Init(void)
{
    hdma.Instance = DMA1_Channel1;
    hdma.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma.Init.MemInc = DMA_MINC_ENABLE;
    hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma.Init.Mode = DMA_CIRCULAR;
    hdma.Init.Priority = DMA_PRIORITY_MEDIUM;
    HAL_DMA_Init(&hdma);
}

// 单次转换模式
//uint16_t get_ADvalue(void)
//{
//	HAL_ADC_Start(&hadc);       // 开始规则组AD转换
//    HAL_ADC_PollForConversion(&hadc, 10);       // 等待规则组转换完成，超时时间设定位10
//	
//    return (uint16_t)HAL_ADC_GetValue(&hadc);  	  // 返回AD转换值
//}
