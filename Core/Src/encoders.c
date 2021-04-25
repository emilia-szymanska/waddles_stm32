#include "encoders.h"

volatile uint16_t E1_rpm = 0;
volatile uint16_t E2_rpm = 0;
volatile uint16_t E3_rpm = 0;
volatile uint16_t E4_rpm = 0;


void ENCODERS_start()
{
	HAL_TIM_Base_Start_IT(&htim9);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
}

void ENCODERS_get_rpm()
{
	uint16_t E1_value = 0;
	uint16_t E2_value = 0;
	uint16_t E3_value = 0;
	uint16_t E4_value = 0;
	uint16_t E1_ticks = 0;
	uint16_t E2_ticks = 0;
	uint16_t E3_ticks = 0;
	uint16_t E4_ticks = 0;


	E1_value = __HAL_TIM_GET_COUNTER(&htim2);
	E2_value = __HAL_TIM_GET_COUNTER(&htim3);
	E3_value = __HAL_TIM_GET_COUNTER(&htim4);
	E4_value = __HAL_TIM_GET_COUNTER(&htim5);

	if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2))	// 32bit
		E1_ticks = 0xFFFFFFFF - E1_value + 1;
	else E1_ticks = E1_value;

	if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3))	// 16bit
		E2_ticks = 0xFFFF - E2_value + 1;
	else E2_ticks = E2_value;

	if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))	// 16bit
		E3_ticks = 0xFFFF - E3_value + 1;
	else E3_ticks = E3_value;

	if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5))	// 32bit
		E4_ticks = 0xFFFFFFFF - E4_value + 1;
	else E4_ticks = E4_value;

	E1_rpm = E1_ticks * 10 / 3;
	E2_rpm = E2_ticks * 10 / 3;
	E3_rpm = E3_ticks * 10 / 3;
	E4_rpm = E4_ticks * 10 / 3;

	__HAL_TIM_SET_COUNTER(&htim2, 0);
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	__HAL_TIM_SET_COUNTER(&htim5, 0);
}
