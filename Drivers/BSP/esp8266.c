/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	esp8266.c
	*	作者： 		zh
	*	日期： 		
	*	版本： 		V1.0
	*	说明： 		ESP8266的简单驱动
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "sys.h"

//网络设备驱动
#include "esp8266.h"

//硬件驱动
#include "delay.h"
#include "uart1.h"

//C库
#include <string.h>
#include <stdio.h>

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"Honor100\",\"Cc.246850@\"\r\n"

//#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n"    //旧版OneNET地址
#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"  	//新版OneNET地址
//#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"192.168.11.125\",8080\r\n"   //调试地址

unsigned char esp8266_buf[128];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;

UART_HandleTypeDef huart3;

//==========================================================
//	函数名称：	ESP8266_Clear
//
//	函数功能：	清空缓存
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	函数名称：	ESP8266_WaitRecive
//
//	函数功能：	等待接收完成
//
//	入口参数：	无
//
//	返回参数：	REV_OK-接收完成		REV_WAIT-接收超时未完成
//
//	说明：		循环调用检测是否接收完成
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		esp8266_cnt = 0;							//清0接收计数
			
		return REV_OK;								//返回接收完成标志
	}
		
	esp8266_cntPre = esp8266_cnt;					//置为相同
	
	return REV_WAIT;								//返回接收未完成标志

}

//==========================================================
//	函数名称：	ESP8266_SendCmd
//
//	函数功能：	发送命令
//
//	入口参数：	cmd：命令
//				res：需要检查的返回指令
//
//	返回参数：	0-成功	1-失败
//
//	说明：		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;

	sendString_toEsp8266((unsigned char *)cmd, strlen((const char *)cmd));
	
	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//如果收到数据
		{
			if(strstr((const char *)esp8266_buf, res) != NULL)		//如果检索到关键词
			{
				ESP8266_Clear();									//清空缓存
				
				return 0;
			}
		}
		delay_ms(10);
	}
	
	return 1;

}

//==========================================================
//	函数名称：	ESP8266_SendData
//
//	函数功能：	发送数据
//
//	入口参数：	data：数据
//				len：长度
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_SendData(unsigned char *data, unsigned short len)
{

	char cmdBuf[200];
	
	ESP8266_Clear();								//清空接收缓存
	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//发送命令
	if(!ESP8266_SendCmd(cmdBuf, ">"))				//收到‘>’时可以发送数据
	{
		sendString_toEsp8266(data, len);	//发送设备连接请求数据
	}

}

//==========================================================
//	函数名称：	ESP8266_GetIPD
//
//	函数功能：	获取平台返回的数据
//
//	入口参数：	等待的时间(乘以10ms)
//
//	返回参数：	平台返回的原始数据
//
//	说明：		不同网络设备返回的格式不同，需要去调试
//				如ESP8266的返回格式为	"+IPD,x:yyy"	x代表数据长度，yyy是数据内容
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//如果接收完成
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//搜索“IPD”头
			if(ptrIPD != NULL)										
			{
				ptrIPD = strchr(ptrIPD, ':');							//找到':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		delay_ms(5);													//延时等待
	} while(timeOut--);
	
	return NULL;														//超时还未找到，返回空指针

}

//==========================================================
//	函数名称：	ESP8266_Init
//
//	函数功能：	初始化ESP8266
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================

void ESP8266_Init(void)
{
	huart3.Instance = USART3;
    huart3.Init.BaudRate = 9600;
    huart3.Init.Mode = UART_MODE_TX_RX;        // 收发模式
    huart3.Init.Parity = UART_PARITY_NONE;     // 不需要校验位
    huart3.Init.StopBits = UART_STOPBITS_1;    // 1位停止位
    huart3.Init.WordLength = UART_WORDLENGTH_8B;       // 每次数据传输8位
    HAL_UART_Init(&huart3);

    __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);    // 使能uart3 并使能UART_IT_RXNE触发接收中断
	
	ESP8266_Clear();

	while(ESP8266_SendCmd("AT\r\n", "OK"))
		delay_ms(500);
	
	while(ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK"))
		delay_ms(500);
	
	while(ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP"))
		delay_ms(500);
	
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
		delay_ms(500);

}

//==========================================================
//	函数名称：	USART3_IRQHandler
//
//	函数功能：	串口2收发中断
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART3_IRQHandler(void)
{
	static uint8_t recv = 0;
	if(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE) != RESET) //接收中断
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	
			esp8266_cnt = 0; 					//防止串口被刷爆
		HAL_UART_Receive(&huart3, &recv, 1, 1000);
		esp8266_buf[esp8266_cnt++] = recv;
	}
}


/*	 发送数据封装	*/
void serial3_sendByte(uint8_t Byte)
{
	HAL_UART_Transmit(&huart3, &Byte, 1, 100);
}

void sendString_toEsp8266(unsigned char* str, uint16_t len)
{
	ESP8266_Clear();
	for(uint8_t i=0; i<len; i++)
	{
		serial3_sendByte(str[i]);
	}
}
