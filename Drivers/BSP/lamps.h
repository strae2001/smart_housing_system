#ifndef __LAMP_H
#define __LAMP_H

#define BEDROOM_LAMP	GPIO_PIN_8
#define LIVROOM_LAMP	GPIO_PIN_9

#include "sys.h"

/// @brief pwm 时基,Msp,CCR 初始化
/// @param arr 
/// @param psc 
void Lamp_pwm_Init(uint16_t arr, uint16_t psc);

// 调节卧室灯亮度
void bedroom_lamp_off(void);
void bedroom_lamp_low(void);
void bedroom_lamp_mid(void);
void bedroom_lamp_high(void);

// 调节客厅灯亮度
void livroom_lamp_off(void);
void livroom_lamp_low(void);
void livroom_lamp_mid(void);
void livroom_lamp_high(void);

// 获取当前卧室、客厅灯状态
uint8_t get_bedroom_lamp_status(void);
uint8_t get_livroom_lamp_status(void);

#endif
