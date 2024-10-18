#include "BlueTooth.h"
#include "string.h"
#include "lamps.h"
#include "uart1.h"

uint8_t Rx2Buf[Rx2BUF_SIZE] = {0};

UART_HandleTypeDef huart2;

uint8_t bluetooth_cmd;

void BlueTooth_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;    // 不使用流控      
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    HAL_UART_Init(&huart2);

    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);     // 使能UART2 并开启UART_IT_RXNE触发中断
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);	 // 使能UART2 空闲中断
}

void USART2_IRQHandler(void)
{
    static uint8_t cnt = 0;
    static uint8_t recv;
    if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
    {
        HAL_UART_Receive(&huart2, &recv, 1, 10);
        if(cnt >= Rx2BUF_SIZE)
            cnt = 0;
        Rx2Buf[cnt++] = recv;
    }

    if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE) != RESET)
    {
		bluetooth_cmd = Rx2Buf[0];
        Bluetooth_sendString((char*)Rx2Buf);
		
        cnt = 0;
		memset(Rx2Buf, 0, sizeof(Rx2Buf));	// 清空数据缓冲区
	
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);     	// 清除串口空闲挂起标志位
    }
}

void serial2_sendByte(uint8_t Byte)
{
    HAL_UART_Transmit(&huart2, &Byte, 1, 10);
}

void Bluetooth_sendString(char* str)
{
    for (uint8_t i = 0; str[i]!='\0'; i++)
    {
        serial2_sendByte(str[i]);
    }
}

uint8_t get_bluetooth_cmd(void)
{
	uint8_t temp = bluetooth_cmd - '0';
	bluetooth_cmd = 0;
	
	return temp;
}
