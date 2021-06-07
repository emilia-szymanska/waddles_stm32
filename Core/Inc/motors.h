#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "tim.h"
#include "gpio.h"

#define FORWARD 1
#define BACKWARD 0
#define SPEED_CONST 50
#define SPEED_STOP 0

void MOTORS_start();

void MOTORS_stop();

void MOTORS_set_speed(uint8_t motor_nr, uint8_t speed);

void MOTORS_set_polarity(uint8_t motor_nr, uint8_t polarity);

void MOTORS_go_forward();
void MOTORS_go_backward();
void MOTORS_go_left();
void MOTORS_go_right();
void MOTORS_rotate();
void MOTORS_go_forwardleft();
void MOTORS_go_forwardright();
void MOTORS_go_backwardright();
void MOTORS_go_backwardleft();

void MOTORS_M1_forward();
void MOTORS_M2_forward();
void MOTORS_M3_forward();
void MOTORS_M4_forward();

void MOTORS_M1_backward();
void MOTORS_M2_backward();
void MOTORS_M3_backward();
void MOTORS_M4_backward();

void setpoints_to_zeros(uint16_t *setpoints_array);
void setpoints_to_const(uint16_t *setpoints_array);
void setpoints_to_fr_bl(uint16_t *setpoints_array);
void setpoints_to_fl_br(uint16_t *setpoints_array);

#endif /* INC_MOTORS_H_ */
