#ifndef __MAIN_H
#define	__MAIN_H

#include "sys.h"
#include "delay.h"
#include "lamps.h"
#include "uart1.h"
#include "keyboard.h"
#include "OLED.h"
#include "oled_show.h"
#include "W25Q128.h"
#include "myRTC.h"
#include "pwd.h"
#include "beep.h"
#include "SU_03T.h"
#include "BlueTooth.h"
#include "my_ADC.h"
#include "fan.h"
#include "systick_Task.h"
#include "door_switch.h"
#include "esp8266.h"
#include "onenet.h"
#include "DHT11.h"
#include <stdio.h>


/* -------- 变量定义和声明 ---------	 */





/* -------- 函数声明 ---------	 */

/*	 门禁模块	*/
void myRTC_Time_Init(void);			// 初始化RTC时钟
void OLED_Show_RTC_Time(void);		// 实时显示RTC时钟

void unlock_State(void);			// 解锁状态执行代码
void locked_State(void);			// 锁定状态执行代码

void DoorLock_System(void);			// 门禁系统运行任务（main函数调用）


/*  火灾警报模块  */
void fire_alarm_system(void);		// 火灾警报系统运行任务（main函数调用）

#endif
