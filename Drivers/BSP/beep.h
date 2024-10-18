#ifndef __BEEP_H
#define __BEEP_H

#define BEEP_PORT	GPIOC
#define BEEP_PIN	GPIO_PIN_13

#define BEEP_CLK_ENABLE  __HAL_RCC_GPIOC_CLK_ENABLE();

#include "sys.h"

void beep_init(void);
void beep_on(void);
void beep_off(void);
void beep_toggle(void);

#endif
