#include "SU_03T.h"
#include "lamps.h"

void SU03T_init(void)
{
	LIGHT_CLK_ENABLE;
	
	// 开启AFIO时钟 准备重映射PB4
	__HAL_RCC_AFIO_CLK_ENABLE();
	
	// 初始化GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = VOICE_BEDROOM_LAMP;
	gpio_initStruct.Mode = GPIO_MODE_INPUT;
	gpio_initStruct.Pull = GPIO_PULLUP;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LIGHT_PORT, &gpio_initStruct);
	
	gpio_initStruct.Pin = VOICE_LIVROOM_LAMP;
	gpio_initStruct.Mode = GPIO_MODE_AF_INPUT;
	HAL_GPIO_Init(LIGHT_PORT, &gpio_initStruct);
}

uint8_t get_voice_val(void)
{
	return ((HAL_GPIO_ReadPin(LIGHT_PORT, VOICE_BEDROOM_LAMP) << 1) | HAL_GPIO_ReadPin(LIGHT_PORT, VOICE_LIVROOM_LAMP));
}

