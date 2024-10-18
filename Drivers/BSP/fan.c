#include "fan.h"

void fan_init(void)
{
	// ��ʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	// ��ʼ��GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = GPIO_PIN_12;
	gpio_initStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initStruct.Pull = GPIO_PULLUP;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio_initStruct);
	
	// Ĭ�Ϲرշ���
	fan_off();
}
	
void fan_on(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}
	
void fan_off(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}
