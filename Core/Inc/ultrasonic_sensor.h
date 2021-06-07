#ifndef INC_ULTRASONIC_SENSOR_H_
#define INC_ULTRASONIC_SENSOR_H_

#include "gpio.h"
#include "tim.h"


void USONIC_start();

void USONIC_stop();

uint16_t USONIC_get_distance();

void delay(uint16_t time);

void set_to_rising_edge();

void set_to_falling_edge();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* INC_ULTRASONIC_SENSOR_H_ */
