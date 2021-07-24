#ifndef __WCNM_H
#define __WCNM_H
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

int fputc(int ch, FILE *f);
extern void Delay_us(uint32_t t);
extern void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif

