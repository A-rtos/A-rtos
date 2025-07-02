#ifndef DRV_TIM_H
#define DRV_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Exported functions prototypes ---------------------------------------------*/
void timStart(void);
void timTempStart(void);
void beepSet(uint16_t compare);
void pwmSet(uint32_t channe, uint16_t compare);

void HAL_Delay_us(uint16_t Delay_us);
// uint8_t TIM6_CheckIrqStatus(void);

#endif
