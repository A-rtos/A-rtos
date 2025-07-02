#ifndef DRV_IST8310_H
#define DRV_IST8310_H

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t status;
	float mag[3];
} ist8310_t;

extern ist8310_t ist8310_data;	//x,y,z轴磁场数组

/* Exported functions prototypes ---------------------------------------------*/
uint8_t ist8310Init(void);
void ist8310Read(float * mag);

#endif
