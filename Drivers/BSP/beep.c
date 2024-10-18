#include "beep.h"

void beep_init(void)
{
	// ��ʱ��
	BEEP_CLK_ENABLE;
	
	// ��ʼ��GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = BEEP_PIN;
	gpio_initStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initStruct.Pull = GPIO_PULLUP;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BEEP_PORT, &gpio_initStruct);
	
	// Ĭ�Ϲر�
	beep_off();
}

void beep_on(void)
{
	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_RESET);
}

void beep_off(void)
{
	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_SET);
}

void beep_toggle(void)
{
	if(HAL_GPIO_ReadPin(BEEP_PORT, BEEP_PIN) == GPIO_PIN_RESET)
	{
		beep_off();
	}
	else
		beep_on();
}
