#ifndef __SYSTICK_TASK_H
#define __SYSTICK_TASK_H

#include "sys.h"

enum ADC_VAL
{
	GAS = 0,
	LIGHT,
};

// ����ģʽ�����蹤����ʱ��
void alarm_work_timer(void);

// ���־�������
void task_fireAlarm(void);

// ��������
void task_light_control(void);

// �����ϴ�����
void task_uploadtoMQTT(void);


// �ƹ����
void light_control(void);

// �����ϴ�mqtt������
void mqtt_upload(void);

#endif
