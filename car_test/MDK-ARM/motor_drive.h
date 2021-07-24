#ifndef __MOTOR_DRIVE_H
#define __MOTOR_DRIVE_H


#include "motor_data.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "wcnm.h"
#include "pid.h"
#define MOTOR_NORMAL   			1
#define MOTOR_STOP					2
#define MOTOR_CONTROL				3


extern void  motor_drive (uint8_t mode ,fp32 motor[4]);

extern void motor_drive_init(void);

#endif
