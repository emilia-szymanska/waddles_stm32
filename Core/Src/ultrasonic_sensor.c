#include "ultrasonic_sensor.h"

volatile uint8_t first_echo_flag = 0;
volatile uint32_t difference = 0;


void USONIC_start()
{
	set_to_rising_edge();
	HAL_TIM_Base_Start(&htim11);
}

void USONIC_stop()
{
	HAL_TIM_Base_Stop(&htim11);
}

uint16_t USONIC_get_distance()
{
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low
	first_echo_flag = 1;
	while(first_echo_flag != 0);
	uint16_t distance = (uint16_t)((float)difference * .034/2.0f);
	return distance;
}

void delay(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	while (__HAL_TIM_GET_COUNTER(&htim11) <  time);
	__HAL_TIM_SET_COUNTER(&htim11, 0);
}

void set_to_rising_edge()
{
	CLEAR_BIT(EXTI->FTSR,EXTI_FTSR_TR12);
	SET_BIT(EXTI->RTSR,EXTI_RTSR_TR12);
}

void set_to_falling_edge()
{
	CLEAR_BIT(EXTI->RTSR,EXTI_RTSR_TR12);
	SET_BIT(EXTI->FTSR,EXTI_FTSR_TR12);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == ECHO_Pin)
	{
		if (first_echo_flag == 1) // if the first value is not captured yet
		{
			__HAL_TIM_SET_COUNTER(&htim11, 0);
			first_echo_flag = 2;  // set the first captured as true
			set_to_falling_edge();
		}
		else if (first_echo_flag == 2)   // if the first is already captured
		{
			difference = __HAL_TIM_GET_COUNTER(&htim11);  // read second value
			first_echo_flag = 0; // set it back to false
			set_to_rising_edge();
		}
	}
}
