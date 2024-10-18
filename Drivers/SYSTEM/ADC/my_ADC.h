#ifndef __MYADC_H
#define __MYADC_H

#define GAS_SENSOR			GPIO_PIN_0
#define LIGHT_SENSOR		GPIO_PIN_1

#include "sys.h"

// desArr: 数据转运目的地址
// len:    数据转运个数
void myADC_Init(uint32_t* desArr, uint32_t len);

void myADC_DMA_Init(void);

/// @brief AD转换通道配置
/// @param channel ADC对应通道(引脚对应的adc通道号)
/// @param rank    规则组顺序表（菜单表）
/// @param stime   采样时间
void myADC_channelConfig(uint32_t channel, uint32_t rank, uint32_t stime);

uint16_t get_ADvalue(void);

#endif
