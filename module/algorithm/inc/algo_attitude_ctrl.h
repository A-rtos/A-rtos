#ifndef ALGO_ATTITUDE_CTRL_H
#define ALGO_ATTITUDE_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	float thrust;
	float roll;
	float pitch;
	float yaw;
} rctrl_t;

extern float angle_m[3]; // 测量姿态角 deg
extern float angle_d[3]; // 期望姿态角 deg

extern float rate_m[3]; // 测量姿态角速度 dps
extern float rate_d[3]; // 期望姿态角速度 dps

extern uint16_t motor_pwm[4];	// 四个电机的PWM控制量

/* Exported functions prototypes ---------------------------------------------*/
void acPpidInit(void);
void acAttitudeCtrl(rctrl_t *act_control);
void acMixerCtrl(rctrl_t *act_control);

#endif
