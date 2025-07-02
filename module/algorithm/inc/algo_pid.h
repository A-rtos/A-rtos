#ifndef ALGO_PID_H
#define ALGO_PID_H

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	float desired;	 //< set point
	float measured;	 //< current point

	float error;	 //< error
	float perror; 	 //< previous error
	float integ;	 //< integral
	float deriv;	 //< derivative
	
	float kp;		 //< proportional gain
	float ki;		 //< integral gain
	float kd;		 //< derivative gain
	
	float pout;		 //< proportional output
	float iout;		 //< integral output
	float dout;		 //< derivative output
	float out;
	
	float ilimit;	 //< limit
	float outlimit;
} pid_t;

/* Exported functions prototypes ---------------------------------------------*/
void pidInit(pid_t *pid, float *pid_param);
void pidReset(pid_t *pid);
float pidCalculate(pid_t *pid);

#endif
