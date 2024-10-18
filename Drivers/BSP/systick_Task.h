#ifndef __SYSTICK_TASK_H
#define __SYSTICK_TASK_H

#include "sys.h"

enum ADC_VAL
{
	GAS = 0,
	LIGHT,
};

// 警报模式下外设工作计时器
void alarm_work_timer(void);

// 火灾警报任务
void task_fireAlarm(void);

// 声控任务
void task_light_control(void);

// 数据上传任务
void task_uploadtoMQTT(void);


// 灯光控制
void light_control(void);

// 数据上传mqtt服务器
void mqtt_upload(void);

#endif
