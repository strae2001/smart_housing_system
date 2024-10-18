#include "door_switch.h"

void door_switch_init(void)
{
	// ��ʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// ��ʼ��GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = GPIO_PIN_11;
	gpio_initStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initStruct.Pull = GPIO_PULLUP;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio_initStruct);
	
	// Ĭ�Ϲر�����
	door_switch_off();
}

void door_switch_on(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
}

void door_switch_off(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
}

