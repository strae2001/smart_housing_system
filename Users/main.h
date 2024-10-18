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


/* -------- ������������� ---------	 */





/* -------- �������� ---------	 */

/*	 �Ž�ģ��	*/
void myRTC_Time_Init(void);			// ��ʼ��RTCʱ��
void OLED_Show_RTC_Time(void);		// ʵʱ��ʾRTCʱ��

void unlock_State(void);			// ����״ִ̬�д���
void locked_State(void);			// ����״ִ̬�д���

void DoorLock_System(void);			// �Ž�ϵͳ��������main�������ã�


/*  ���־���ģ��  */
void fire_alarm_system(void);		// ���־���ϵͳ��������main�������ã�

#endif
