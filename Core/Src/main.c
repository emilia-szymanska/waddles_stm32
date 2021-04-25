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
#include "bluetooth.h"
#include "temperature_sensor.h"
#include "motors.h"
#include "encoders.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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

volatile uint8_t main_flag = 0;
volatile uint8_t first_echo_flag = 0;
volatile uint32_t difference = 0;
volatile uint16_t distance = 0;

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
		ENCODERS_get_rpm();
	}
}

//////////////////////////////////////////////////////////////////
void delay(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	while (__HAL_TIM_GET_COUNTER(&htim11) <  time);
	__HAL_TIM_SET_COUNTER(&htim11, 0);
}


void HCSR04_Read (void)
{
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low
	first_echo_flag = 1;
	while(first_echo_flag != 0);
	distance = (uint16_t)((float)difference * .034/2.0f);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == ECHO_Pin)
	{
		if (first_echo_flag == 1) // if the first value is not captured
		{
			__HAL_TIM_SET_COUNTER(&htim11, 0);
			first_echo_flag = 2;  // set the first captured as true

		}
		else if (first_echo_flag == 2)   // if the first is already captured
		{
			difference = __HAL_TIM_GET_COUNTER(&htim11);  // read second value
			//distance = difference * .034/2;
			first_echo_flag = 0; // set it back to false
		}
	}
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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

  BT_start();
  MOTORS_start();
  ENCODERS_start();
  HAL_TIM_Base_Start_IT(&htim10);
  HAL_TIM_Base_Start(&htim11);


  float temperature = 0.0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(main_flag)
	  {

		  if(strcmp(command, "nn") == 0)
		  {
			  BT_send_message("PWM: 0\r\n");
		  	  MOTORS_set_speed(1, 0);
		  	  MOTORS_set_speed(2, 0);
		  }
		  else if(strcmp(command, "ll") == 0)
		  {
			  BT_send_message("PWM: 25\r\n");
			  MOTORS_set_speed(1, 25);
			  MOTORS_set_speed(2, 25);
		  }
		  else if(strcmp(command, "rr") == 0)
		  {
			  BT_send_message("PWM: 50\r\n");
			  MOTORS_set_speed(1, 50);
			  MOTORS_set_speed(2, 50);
		  }
		  else if(strcmp(command, "bb") == 0)
		  {
			  BT_send_message("PWM: 75\r\n");
			  MOTORS_set_speed(1, 75);
			  MOTORS_set_speed(2, 75);
		  }
		  else if(strcmp(command, "ff") == 0)
		  {
			  BT_send_message("PWM: 100\r\n");
			  MOTORS_set_speed(1, 100);
			  MOTORS_set_speed(2, 100);
		  }
		  temperature = TEMP_get_data();
		  HCSR04_Read();
		  printf("dist: %d cm\r\n", distance);
		  printf("temp: %.2f \r\n", temperature);
		  printf("encoder: %d, %d, %d, %d \r\n", E1_rpm, E2_rpm, E3_rpm, E4_rpm);

		  main_flag = 0;
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
