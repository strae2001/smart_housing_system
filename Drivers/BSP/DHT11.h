#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"

#define DHT11_PORT                  GPIOB
#define DHT11_PIN                   GPIO_PIN_3
#define DHT11_CLK_ENABLE            __HAL_RCC_GPIOB_CLK_ENABLE()

// DHT11输出引脚配置
#define DHT11_DQ_OUT(x)             do{ x ? \
                                        HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET): \
                                        HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET); \
                                    }while (0)

// #define DHT11_DQ_OUT(x)             HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, (GPIO_PinState)(x))

// DHT11输入引脚配置
#define DHT11_DQ_IN                 HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)


// 接收并打印温湿度
void recv_Data_fromDHT11(uint8_t* datas);

#endif
