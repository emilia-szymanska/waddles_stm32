#ifndef SRC_PID_H_
#define SRC_PID_H_

#include <stdint.h>

typedef  struct
{
	float p;
	float i;
	float d;
	int32_t max_p;
	int32_t min_p;
	int32_t max_i;
	int32_t min_i;
	int32_t max_d;
	int32_t min_d;
	int32_t max_out;
	int32_t min_out;
	uint32_t dt_ms;
} PID_config;

typedef struct
{
	PID_config config;
	int32_t sum;
	int32_t last_e;
	int32_t p_out;
	int32_t i_out;
	int32_t d_out;
	int32_t pid_out;
} PID_handler;

void PID_init(PID_handler *pid, float p, float i, float d);

uint32_t PID_output(PID_handler *pid, uint32_t desired_value, uint32_t measured_value);


#endif /* SRC_PID_H_ */
