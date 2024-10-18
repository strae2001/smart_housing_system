#ifndef __SU03T_H
#define __SU03T_H

#define LIGHT_CLK_ENABLE	__HAL_RCC_GPIOB_CLK_ENABLE()

#define LIGHT_PORT	GPIOB

#define VOICE_LIVROOM_LAMP	GPIO_PIN_4
#define VOICE_BEDROOM_LAMP	GPIO_PIN_5

#include "sys.h"

void SU03T_init(void);

void SU03T_check(void);

// »ñÈ¡Éù¿ØµÆÁÁ¶È
uint8_t get_voice_bedroom_bright(void);
uint8_t get_voice_livroom_bright(void);

uint8_t get_voice_val(void);

#endif
