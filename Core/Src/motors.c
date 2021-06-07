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

void MOTORS_stop()
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
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
	if(polarity != FORWARD && polarity != BACKWARD) return;
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

void MOTORS_M1_forward()
{
	MOTORS_set_polarity(1, FORWARD);
}

void MOTORS_M2_forward()
{
	MOTORS_set_polarity(2, BACKWARD);
}

void MOTORS_M3_forward()
{
	MOTORS_set_polarity(3, FORWARD);
}

void MOTORS_M4_forward()
{
	MOTORS_set_polarity(4, BACKWARD);
}

void MOTORS_M1_backward()
{
	MOTORS_set_polarity(1, BACKWARD);
}

void MOTORS_M2_backward()
{
	MOTORS_set_polarity(2, FORWARD);
}

void MOTORS_M3_backward()
{
	MOTORS_set_polarity(3, BACKWARD);
}

void MOTORS_M4_backward()
{
	MOTORS_set_polarity(4, FORWARD);
}

void MOTORS_go_forward()
{
	MOTORS_M1_forward();
	MOTORS_M2_forward();
	MOTORS_M3_forward();
	MOTORS_M4_forward();
}

void MOTORS_go_backward()
{
	MOTORS_M1_backward();
	MOTORS_M2_backward();
	MOTORS_M3_backward();
	MOTORS_M4_backward();
}

void MOTORS_go_left()
{
	MOTORS_M1_backward();
	MOTORS_M2_forward();
	MOTORS_M3_backward();
	MOTORS_M4_forward();
}

void MOTORS_go_right()
{
	MOTORS_M1_forward();
	MOTORS_M2_backward();
	MOTORS_M3_forward();
	MOTORS_M4_backward();
}

void MOTORS_rotate()
{
	MOTORS_M1_backward();
	MOTORS_M2_backward();
	MOTORS_M3_forward();
	MOTORS_M4_forward();
}

void MOTORS_go_forwardleft()
{
	MOTORS_M2_forward();
	MOTORS_M4_forward();
}

void MOTORS_go_forwardright()
{
	MOTORS_M1_forward();
	MOTORS_M3_forward();
}

void MOTORS_go_backwardright()
{
	MOTORS_M2_backward();
	MOTORS_M4_backward();
}

void MOTORS_go_backwardleft()
{
	MOTORS_M1_backward();
	MOTORS_M3_backward();
}

void setpoints_to_zeros(uint16_t *setpoints_array)
{
	setpoints_array[0] = SPEED_STOP;
	setpoints_array[1] = SPEED_STOP;
	setpoints_array[2] = SPEED_STOP;
	setpoints_array[3] = SPEED_STOP;
}

void setpoints_to_const(uint16_t *setpoints_array)
{
	setpoints_array[0] = SPEED_CONST;
	setpoints_array[1] = SPEED_CONST;
	setpoints_array[2] = SPEED_CONST;
	setpoints_array[3] = SPEED_CONST;
}

void setpoints_to_fr_bl(uint16_t *setpoints_array)
{
	setpoints_array[0] = SPEED_CONST;
	setpoints_array[1] = SPEED_STOP;
	setpoints_array[2] = SPEED_CONST;
	setpoints_array[3] = SPEED_STOP;
}

void setpoints_to_fl_br(uint16_t *setpoints_array)
{
	setpoints_array[0] = SPEED_STOP;
	setpoints_array[1] = SPEED_CONST;
	setpoints_array[2] = SPEED_STOP;
	setpoints_array[3] = SPEED_CONST;
}
