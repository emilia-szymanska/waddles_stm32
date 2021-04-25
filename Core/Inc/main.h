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
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

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
#define ENC_M4_A_Pin GPIO_PIN_0
#define ENC_M4_A_GPIO_Port GPIOA
#define ENC_M4_B_Pin GPIO_PIN_1
#define ENC_M4_B_GPIO_Port GPIOA
#define BT_TX_Pin GPIO_PIN_2
#define BT_TX_GPIO_Port GPIOA
#define BT_RX_Pin GPIO_PIN_3
#define BT_RX_GPIO_Port GPIOA
#define ENC_M1_A_Pin GPIO_PIN_5
#define ENC_M1_A_GPIO_Port GPIOA
#define ENC_M2_A_Pin GPIO_PIN_6
#define ENC_M2_A_GPIO_Port GPIOA
#define ENC_M2_B_Pin GPIO_PIN_7
#define ENC_M2_B_GPIO_Port GPIOA
#define M1_PHASE_Pin GPIO_PIN_0
#define M1_PHASE_GPIO_Port GPIOB
#define M2_PHASE_Pin GPIO_PIN_1
#define M2_PHASE_GPIO_Port GPIOB
#define M3_PHASE_Pin GPIO_PIN_2
#define M3_PHASE_GPIO_Port GPIOB
#define M4_PHASE_Pin GPIO_PIN_10
#define M4_PHASE_GPIO_Port GPIOB
#define ECHO_Pin GPIO_PIN_12
#define ECHO_GPIO_Port GPIOB
#define ECHO_EXTI_IRQn EXTI15_10_IRQn
#define TRIG_Pin GPIO_PIN_13
#define TRIG_GPIO_Port GPIOB
#define MOTOR_1_Pin GPIO_PIN_8
#define MOTOR_1_GPIO_Port GPIOA
#define MOTOR_2_Pin GPIO_PIN_9
#define MOTOR_2_GPIO_Port GPIOA
#define MOTOR_3_Pin GPIO_PIN_10
#define MOTOR_3_GPIO_Port GPIOA
#define MOTOR_4_Pin GPIO_PIN_11
#define MOTOR_4_GPIO_Port GPIOA
#define ENC_M1_B_Pin GPIO_PIN_3
#define ENC_M1_B_GPIO_Port GPIOB
#define ENC_M3_A_Pin GPIO_PIN_6
#define ENC_M3_A_GPIO_Port GPIOB
#define ENC_M3_B_Pin GPIO_PIN_7
#define ENC_M3_B_GPIO_Port GPIOB
#define TEMP_SCL_Pin GPIO_PIN_8
#define TEMP_SCL_GPIO_Port GPIOB
#define TEMP_SDA_Pin GPIO_PIN_9
#define TEMP_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
