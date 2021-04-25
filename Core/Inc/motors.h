#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "tim.h"
#include "gpio.h"

void MOTORS_start();

void MOTORS_set_speed(uint8_t motor_nr, uint8_t speed);

#endif /* INC_MOTORS_H_ */
