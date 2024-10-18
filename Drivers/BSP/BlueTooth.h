#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "sys.h"

#define TX2 GPIO_PIN_2
#define RX2 GPIO_PIN_3

#define Rx2BUF_SIZE 128

void BlueTooth_Init(void);

void Bluetooth_sendString(char* str);

uint8_t get_bluetooth_cmd(void);

#endif
