#include "systick_Task.h"
#include "main.h"

// ����ģʽ��־λ
extern uint8_t Alarm_Mode;

// ������������
uint16_t alarm_work_cnt = 0;

/*	 ����ʱ�����	*/
uint16_t task_fireAlarm_cnt = 0;
uint16_t task_voiceCheck_cnt = 0;
uint16_t task_uploadtoMQTT_cnt = 0;

// �ƿ�״̬λ
uint8_t light_status = 0;										// �������Ƶ�״̬
uint8_t voice_light_status = 0, voice_light_status_old = 0;		// ���ص�״̬

/*  ���־���ģ��  */
float Voltage;					 // ��ѹ
float limit = 3.0;				 // ��ѹ��ֵ
uint8_t Alarm_Mode = OFF;		 // ����ģʽĬ�Ϲر�

// ADת��ֵ
extern uint16_t ADvlaue[2];	

/*	 �ϴ�����	*/
double temperature = 0;
double humid = 0;
double light_val = 0;

void alarm_work_timer(void)
{
	alarm_work_cnt++;
	if(alarm_work_cnt == 2000)
	{
		// ����ģʽ����2s��ر�
		Alarm_Mode = 0;
		alarm_work_cnt = 0;
	}
}

void task_fireAlarm(void)
{
	task_fireAlarm_cnt++;
	if(task_fireAlarm_cnt == 500)		// 500msִ��һ�λ��ֱ�������
	{
		fire_alarm_system();		
		task_fireAlarm_cnt = 0;
	}
}

void task_light_control(void)
{
	task_voiceCheck_cnt++;
	if(task_voiceCheck_cnt == 1000)		// 1sִ��һ�εƿ�����
	{
		light_control();
		task_voiceCheck_cnt = 0;
	}
}

void task_uploadtoMQTT(void)
{
	task_uploadtoMQTT_cnt++;
	if(task_uploadtoMQTT_cnt == 10000)		// 10s�ϴ�һ�λ������ݵ�onenet
	{
		mqtt_upload();
		task_uploadtoMQTT_cnt = 0;
	}
}

void mqtt_upload(void)
{
	uint8_t dht11_data[4] = {0};		
	memset(dht11_data, 0, sizeof(dht11_data));
	
	recv_Data_fromDHT11(dht11_data);			// �ɼ���ʪ������
	
	// ���측������ʪ������
	temperature = dht11_data[2] + (double)dht11_data[3]/10;
	humid = dht11_data[0] + (double)dht11_data[1]/10;
	light_val = (100 - ADvlaue[LIGHT]*100/4096);			// ����ֵ������0~100
	
	printf("TEMP:%.lf��\r\n", temperature);
	printf("Hmid:%.lf%%\r\n", humid);
	printf("light:%.f%%\r\n", light_val);
	
	// ������ʪ�����ݵ�OneNet
	OneNet_SendData();
	
	printf("���ݳɹ��ϴ�!\r\n");
}

void light_control(void)
{
	light_status = get_bluetooth_cmd();
	
	voice_light_status = get_voice_val();
	if(voice_light_status != voice_light_status_old)
	{
		light_status = voice_light_status;
		voice_light_status_old = voice_light_status;
	}
	
	switch(light_status)
	{
		case 0:
			livroom_lamp_off();
			break;
		case 1:
			livroom_lamp_low();
			break;
		case 2:
			livroom_lamp_mid();
			break;
		case 3:
			livroom_lamp_high();
			break;
		case 4:
			bedroom_lamp_low();
			break;
		case 5:
			bedroom_lamp_mid();
			break;
		case 6:
			bedroom_lamp_high();
			break;
		case 7:
			bedroom_lamp_off();
			break;
		case 8:
			livroom_lamp_high();
			bedroom_lamp_high();
			break;
		case 9:
			livroom_lamp_off();
			bedroom_lamp_off();
			break;
	}
}

void fire_alarm_system(void)
{
	Voltage = (float)ADvlaue[GAS] / 4096 * 3.3;
	
	if(Voltage > limit)		// ��ѹ�ﵽԤ��ֵ ��������ģʽ(����Ũ�Ⱥ͵�ѹ������) 
	{
		Alarm_Mode = ON;	// ����ģʽ����ά��2s, ��sysTick�������б��ر�
	}
	
	if(Alarm_Mode == ON)         
	{
		fan_on();
		beep_on();
	}
	else if(Alarm_Mode == OFF)
	{
		fan_off();
		beep_off();
	}
}
