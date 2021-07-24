/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define motor2_data_Pin GPIO_PIN_3
#define motor2_data_GPIO_Port GPIOA
#define motor2_data_EXTI_IRQn EXTI3_IRQn
#define motor1_data_Pin GPIO_PIN_4
#define motor1_data_GPIO_Port GPIOA
#define motor1_data_EXTI_IRQn EXTI4_IRQn
#define motor1_in1_Pin GPIO_PIN_5
#define motor1_in1_GPIO_Port GPIOA
#define motor1_in2_Pin GPIO_PIN_6
#define motor1_in2_GPIO_Port GPIOA
#define motor3_pwm_Pin GPIO_PIN_0
#define motor3_pwm_GPIO_Port GPIOB
#define motor4_pwm_Pin GPIO_PIN_1
#define motor4_pwm_GPIO_Port GPIOB
#define motor2_in1_Pin GPIO_PIN_2
#define motor2_in1_GPIO_Port GPIOB
#define motor2_in2_Pin GPIO_PIN_10
#define motor2_in2_GPIO_Port GPIOB
#define motor3_data_Pin GPIO_PIN_12
#define motor3_data_GPIO_Port GPIOB
#define motor3_data_EXTI_IRQn EXTI15_10_IRQn
#define motor4_data_Pin GPIO_PIN_13
#define motor4_data_GPIO_Port GPIOB
#define motor4_data_EXTI_IRQn EXTI15_10_IRQn
#define motor1_pwm_Pin GPIO_PIN_4
#define motor1_pwm_GPIO_Port GPIOB
#define motor2_pwm_Pin GPIO_PIN_5
#define motor2_pwm_GPIO_Port GPIOB
#define motor4_in2_Pin GPIO_PIN_6
#define motor4_in2_GPIO_Port GPIOB
#define motor4_in1_Pin GPIO_PIN_7
#define motor4_in1_GPIO_Port GPIOB
#define motor3_in2_Pin GPIO_PIN_8
#define motor3_in2_GPIO_Port GPIOB
#define motor3_in1_Pin GPIO_PIN_9
#define motor3_in1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
