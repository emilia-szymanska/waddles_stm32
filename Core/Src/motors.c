#include "motors.h"

void MOTORS_start()
{
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

	HAL_GPIO_WritePin(M1_PHASE_GPIO_Port, M1_PHASE_Pin, SET);
	HAL_GPIO_WritePin(M2_PHASE_GPIO_Port, M2_PHASE_Pin, SET);
}


void MOTORS_set_speed(uint8_t motor_nr, uint8_t speed)
{
	switch(motor_nr)
	{
		case 1: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
				return;

		case 2: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
				return;

		case 3: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, speed);
				return;

		case 4: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, speed);
				return;
	}
}
