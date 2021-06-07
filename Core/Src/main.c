/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "bluetooth.h"
#include "temperature_sensor.h"
#include "motors.h"
#include "encoders.h"
#include "ultrasonic_sensor.h"
#include "pid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMPERATURE_ALERT 100
#define DISTANCE_LIMIT 8
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

extern volatile char command[2];
extern volatile uint16_t E1_rpm;
extern volatile uint16_t E2_rpm;
extern volatile uint16_t E3_rpm;
extern volatile uint16_t E4_rpm;
extern volatile uint8_t command_flag;

volatile uint8_t main_flag = 0;
volatile uint8_t control_flag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write (int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart2, ptr, len, 50);
	return len;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim10)	// main loop
	{
		main_flag = 1;
	}
	if(htim == &htim9) // encoders
	{
		control_flag = 1;
	}
}

void start_peripherals()
{
	BT_start();
	USONIC_start();
	MOTORS_start();
	ENCODERS_start();
	HAL_TIM_Base_Start_IT(&htim10);
}

void stop_peripherals()
{
	BT_stop();
	USONIC_stop();
	MOTORS_stop();
	ENCODERS_stop();
	HAL_TIM_Base_Stop_IT(&htim10);
}

void temperature_alert()
{
	stop_peripherals();
	float temperature = TEMPERATURE_ALERT;
	while(temperature >= TEMPERATURE_ALERT)
		temperature = TEMP_get_data();
	start_peripherals();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  float temperature = 0.0;
  uint8_t measurements = 8;
  uint16_t distance_array[8];
  uint16_t distance = 0;
  uint16_t setpoints[4] = {SPEED_STOP};
  uint16_t average_distance = 0;
  PID_handler pid_m1, pid_m2, pid_m3, pid_m4;
  float p = 1.0f, i = 20.0f, d = 0.00f;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART2_UART_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
  start_peripherals();
  PID_init(&pid_m1, p, i, d);
  PID_init(&pid_m2, p, i, d);
  PID_init(&pid_m3, p, i, d);
  PID_init(&pid_m4, p, i, d);

  distance = USONIC_get_distance();
  for(uint8_t i = 0; i < measurements; i++)
	  distance_array[i] = distance;
  uint8_t current_index = 0;
  uint8_t distance_sum = measurements * distance;

  average_distance = 1000;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(main_flag)
	  {
		  temperature = TEMP_get_data();
		  if(temperature >= TEMPERATURE_ALERT)
		  {
		  	  setpoints_to_zeros(setpoints);
			  temperature_alert();
		  }
		  distance = USONIC_get_distance();
		  distance_sum = distance_sum - distance_array[current_index] +  distance;
		  distance_array[current_index] = distance;
		  current_index = (current_index + 1) % measurements;
		  average_distance = distance_sum / measurements;
		  main_flag = 0;
	  }
	  if(command_flag)
	  {
		  printf("%s\r\n", command);

		  if(strcmp(command, "nn") == 0)
		  {
			  setpoints_to_zeros(setpoints);
		  }
		  else if(strcmp(command, "ll") == 0)
		  {
		  	  setpoints_to_const(setpoints);
		  	  MOTORS_go_left();
		  }
		  else if(strcmp(command, "rr") == 0)
		  {
		  	  setpoints_to_const(setpoints);
		  	  MOTORS_go_right();
		  }
		  else if(strcmp(command, "bb") == 0)
		  {
		  	  setpoints_to_const(setpoints);
		  	  MOTORS_go_backward();
		  }
		  else if(strcmp(command, "ff") == 0)
		  {
			  if(average_distance <= DISTANCE_LIMIT)
			  {
			  	  setpoints_to_zeros(setpoints);
			  }
			  else
			  {
				  setpoints_to_const(setpoints);
				  MOTORS_go_forward();
			  }
		  }
		  else if(strcmp(command, "fl") == 0)
		  {
			  if(average_distance <= DISTANCE_LIMIT)
			  {
			  	  setpoints_to_zeros(setpoints);
			  }
			  else
			  {
				  setpoints_to_fl_br(setpoints);
				  MOTORS_go_forwardleft();
			  }
		  }
		  else if(strcmp(command, "fr") == 0)
		  {
			  if(average_distance <= DISTANCE_LIMIT)
			  {
				  setpoints_to_zeros(setpoints);
			  }
			  else
			  {
				  setpoints_to_fr_bl(setpoints);
		  	  	  MOTORS_go_forwardright();
			  }
		  }
		  else if(strcmp(command, "bl") == 0)
		  {
		  	  setpoints_to_fr_bl(setpoints);
		  	  MOTORS_go_backwardleft();
		  }
		  else if(strcmp(command, "br") == 0)
		  {
		  	  setpoints_to_fl_br(setpoints);
		  	  MOTORS_go_backwardright();
		  }
		  else if(strcmp(command, "cc") == 0)
		  {
		  	  MOTORS_rotate();
		  	  setpoints_to_const(setpoints);
		  }
		  command_flag = 0;
	  }
	  if(control_flag)
	  {
		  ENCODERS_get_rpm();
		  MOTORS_set_speed(1, PID_output(&pid_m1, setpoints[0], E1_rpm));
		  MOTORS_set_speed(2, PID_output(&pid_m2, setpoints[1], E2_rpm));
		  MOTORS_set_speed(3, PID_output(&pid_m3, setpoints[2], E3_rpm));
		  MOTORS_set_speed(4, PID_output(&pid_m4, setpoints[3], E4_rpm));
		  control_flag = 0;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
