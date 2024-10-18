#include "lamps.h"

TIM_HandleTypeDef pwm_handle;

void Lamp_pwm_Init(uint16_t arr, uint16_t psc)
{
    // 时基工作参数配置
    pwm_handle.Instance = TIM4;             // 指定tim4定时器
    pwm_handle.Init.Prescaler = psc;        // 预分频
    pwm_handle.Init.Period = arr;           // 重装载值
    pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;   // 向上计数
    pwm_handle.Init.AutoReloadPreload = ENABLE;         // 使能自动重装载

    HAL_TIM_PWM_Init(&pwm_handle);  

    // pwm模式, CCR寄存器设置
    TIM_OC_InitTypeDef pwm_config;
    pwm_config.OCMode = TIM_OCMODE_PWM1;            // 选择pwm1模式
    pwm_config.Pulse = 0;                           // 占空比配置
    pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;     // 极性高电平有效
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&pwm_handle, &pwm_config, TIM_CHANNEL_4);
    
    // 使能输出 并启动定时器
    HAL_TIM_PWM_Start(&pwm_handle, TIM_CHANNEL_3);  
    HAL_TIM_PWM_Start(&pwm_handle, TIM_CHANNEL_4);  
}


/// @brief msp初始化（即GPIO, NVIC, CLOCK等初始化）该函数不用声明, 由HAL_TIM_PWM_Init()自动调用
/// @param htim 
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)
    {
        // 使能APB1总线tim4时钟，APB2总线GPIOB时钟
        __HAL_RCC_TIM4_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
                       
        GPIO_InitTypeDef gpio_Structure;
        gpio_Structure.Pin = BEDROOM_LAMP | LIVROOM_LAMP;
        gpio_Structure.Mode = GPIO_MODE_AF_PP;       // 复用推挽输出
        gpio_Structure.Pull = GPIO_PULLUP;
        gpio_Structure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &gpio_Structure);
    }
}

/// @brief 修改pwm值
/// @param val 
void Set_PWM_BEDROOM_LAMP_Value(uint8_t val)
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, TIM_CHANNEL_3, val);
}

void Set_PWM_LIVROOM_LAMP_Value(uint8_t val)
{
    __HAL_TIM_SET_COMPARE(&pwm_handle, TIM_CHANNEL_4, val);
}

void bedroom_lamp_off(void)
{
	Set_PWM_BEDROOM_LAMP_Value(0);
}

void bedroom_lamp_low(void)
{
	Set_PWM_BEDROOM_LAMP_Value(10);
}

void bedroom_lamp_mid(void)
{
	Set_PWM_BEDROOM_LAMP_Value(50);
}

void bedroom_lamp_high(void)
{
	Set_PWM_BEDROOM_LAMP_Value(100);
}

void livroom_lamp_off(void)
{
	Set_PWM_LIVROOM_LAMP_Value(0);
}

void livroom_lamp_low(void)
{
	Set_PWM_LIVROOM_LAMP_Value(10);
}

void livroom_lamp_mid(void)
{
	Set_PWM_LIVROOM_LAMP_Value(50);
}

void livroom_lamp_high(void)
{
	Set_PWM_LIVROOM_LAMP_Value(100);
}

