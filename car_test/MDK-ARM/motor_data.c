#include "motor_data.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "wcnm.h"
float motor_cnt1 = 0;
float motor1_speed;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    
    if (htim->Instance == TIM1)
			{
				motor1_speed = motor_cnt1/10;
				printf("speed= %f \r\n", motor1_speed);
				motor_cnt1 = 0;
			}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if(GPIO_Pin == GPIO_PIN_4)
		{
			motor_cnt1++;
		}
		//下面是预留接口
//		if(GPIO_Pin == GPIO_PIN_3)
//		{
//			Delay_ms(20);
//			if(GPIO_Pin == GPIO_PIN_3)
//		  {
//					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
//				   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//		  }
//		}
}


