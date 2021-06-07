#include "pid.h"

void PID_init(PID_handler *pid, float p, float i, float d)
{
	PID_config config;
	config.max_p =  99;
	config.min_p = -99;
	config.max_i =  99;
	config.min_i = -99;
	config.max_d =  99;
	config.min_d = -99;
	config.max_out = 99;
	config.min_out = 0;
	config.p = p;
	config.i = i;
	config.d = d;
	config.dt_ms = 10;
	pid->config = config;
	pid->last_e = 0;
	pid->sum = 0;
	return;
}

uint32_t PID_output(PID_handler *pid, uint32_t desired_value, uint32_t measured_value)
{
	int32_t diff = desired_value - measured_value;
	pid->p_out = pid->config.p * diff;

	////// P limitations ///////////////////
	if(pid->p_out > pid->config.max_p)
			pid->p_out = pid->config.max_p;
	if(pid->p_out < pid->config.min_p)
			pid->p_out = pid->config.min_p;
	////////////////////////////////////////

	pid->sum += diff * (pid->config.i) * (pid->config.dt_ms) / 1000;
	pid->i_out = pid->sum;

	////// I limitations ///////////////////
	if(pid->i_out > pid->config.max_i)
			pid->i_out = pid->config.max_i;
	if(pid->i_out < pid->config.min_i)
			pid->i_out = pid->config.min_i;
	////////////////////////////////////////

	pid->sum = pid->i_out;
	pid->d_out = (pid->config.d) * (diff - pid->last_e) * 1000 / (pid->config.dt_ms);

	////// D limitations ///////////////////
	if(pid->d_out > pid->config.max_d)
			pid->d_out = pid->config.max_d;
	if(pid->d_out < pid->config.min_d)
			pid->d_out = pid->config.min_d;
	/////////////////////////////////////////

	pid->pid_out = (pid->p_out) + (pid->i_out) + (pid->d_out);

	/// PID output limitations /////////////////
	if( pid->pid_out > pid->config.max_out)
			pid->pid_out = pid->config.max_out;
	if( pid->pid_out < pid->config.min_out)
			pid->pid_out = pid->config.min_out;
	////////////////////////////////////////////

	pid->last_e = diff;

	return pid->pid_out;
}

