#include "DHT11.h"
#include "delay.h"
#include <stdio.h>

void DHT11_gpio_Input(void)
{
    DHT11_CLK_ENABLE;

    // 初始化GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = DHT11_PIN;
	gpio_initStruct.Mode = GPIO_MODE_INPUT;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_PORT, &gpio_initStruct);
}

void DHT11_gpio_Output(void)
{
    DHT11_CLK_ENABLE;

    // 初始化GPIO
	GPIO_InitTypeDef gpio_initStruct;
	gpio_initStruct.Pin = DHT11_PIN;
	gpio_initStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // gpio_initStruct.Pull = GPIO_PULLUP;
	gpio_initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_PORT, &gpio_initStruct);
    
}

void HDT11_start(void)
{
    DHT11_gpio_Output();     // 将DHT11连接的引脚配置为输出模式, 使能单片机向DHT11发送信号
    DHT11_DQ_OUT(1);
    DHT11_DQ_OUT(0);
    delay_ms(20);
    DHT11_DQ_OUT(1);

    DHT11_gpio_Input();     // 引脚配置为输入模式, 使能单片机接收DHT11发来的信号
    while (DHT11_DQ_IN);    // 等待DHT11将引脚电平拉低
    while (!DHT11_DQ_IN);   // 等待DHT11再次将引脚电平拉高
    while (DHT11_DQ_IN);    // 等待DHT11最后将引脚电平拉低, 开始传输数据
}

// 接收DHT11发来的1字节数据
uint8_t recv_Byte_fromDHT11(void)
{
    uint8_t rbyte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        while (!DHT11_DQ_IN);     // 等待DHT11将电平拉高, 单片机开始接收数据
        delay_us(50);
        rbyte <<= 1;
        if(DHT11_DQ_IN)           // 50us后总线仍为高电平, 则DHT11发来的数据位为1
        {
            rbyte |= 0x01;
        }
        while (DHT11_DQ_IN);    // 每传输1bit, 等待DHT11拉低总线, 1bit传输完毕  
    }
    return rbyte;
}

// 接收DHT11发来的所有40bit，即5字节数据
void recv_Data_fromDHT11(uint8_t* datas)
{
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_SWJ_NOJTAG();			// 禁用JTAG接口
	
    HDT11_start();          // 启动模块
    DHT11_gpio_Input();     // 使能单片机接收数据

    for (uint8_t i = 0; i < 5; i++)
    {
        datas[i] = recv_Byte_fromDHT11();
    }

    if(datas[0] + datas[1] + datas[2] + datas[3] == datas[4])
    {
//      printf("HIM: %d.%d %% \r\n", datas[0], datas[1]);
//		printf("TMP: %d.%d ℃ \r\n", datas[2], datas[3]);
    }
    else
        printf("数据校验有误\r\n");
	
	delay_ms(2000);			// 每隔2s接收并打印一次数据
}
