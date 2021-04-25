#include "motors.h"

void MOTORS_start()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

	HAL_GPIO_WritePin(M1_PHASE_GPIO_Port, M1_PHASE_Pin, SET);
	HAL_GPIO_WritePin(M2_PHASE_GPIO_Port, M2_PHASE_Pin, SET);
	HAL_GPIO_WritePin(M3_PHASE_GPIO_Port, M3_PHASE_Pin, SET);
	HAL_GPIO_WritePin(M4_PHASE_GPIO_Port, M4_PHASE_Pin, SET);
}


void MOTORS_set_speed(uint8_t motor_nr, uint8_t speed)
{
	if(speed > 100) return;
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


void MOTORS_set_polarity(uint8_t motor_nr, uint8_t polarity)
{
	if(polarity != 0 && polarity != 1) return;
	switch(motor_nr)
	{
		case 1: HAL_GPIO_WritePin(M1_PHASE_GPIO_Port, M1_PHASE_Pin, polarity);
				return;

		case 2: HAL_GPIO_WritePin(M2_PHASE_GPIO_Port, M2_PHASE_Pin, polarity);
				return;

		case 3: HAL_GPIO_WritePin(M3_PHASE_GPIO_Port, M3_PHASE_Pin, polarity);
				return;

		case 4: HAL_GPIO_WritePin(M4_PHASE_GPIO_Port, M4_PHASE_Pin, polarity);
				return;
	}
}
