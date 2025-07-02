/**
  ******************************************************************************
  * @file    artos.h
  * @author  TP-Thread
  * @brief   Application specific definitions.
  *          These definitions should be adjusted for your particular hardware and application requirements.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ARTOS_H
#define ARTOS_H

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define ABS_MAX_LIMIT(input, max)		(input > max ? max : (input < -max ? max : input))
#define ABS_MIN_LIMIT(input, min)		(input < min ? 0 : (input > -min ? 0 : input))
#define PWM_LIMIT(input, min, max)		(input > max ? max : (input < min ? min : input))

#if defined(TIP)
	#define xtim	htim1
	#define XTIM_CHANNEL_1	TIM_CHANNEL_1
	#define XTIM_CHANNEL_2	TIM_CHANNEL_2
	#define XTIM_CHANNEL_3	TIM_CHANNEL_3
	#define XTIM_CHANNEL_4	TIM_CHANNEL_4
	
	#define btim	htim4
	#define BTIM_CHANNEL	TIM_CHANNEL_3
	
	#define ttim	htim10
	#define TTIM_CHANNEL	TIM_CHANNEL_1
	
    #define duart	huart1
	#define hdma_susart_rx	hdma_usart3_rx
	
	#define suart	huart3
#endif

#if defined(TIP1)
    #define duart	huart1
	#define suart	huart3
	#define hdma_susart_rx	hdma_usart3_rx
#endif

/* Exported functions prototypes ---------------------------------------------*/

#endif /* ARTOS_H */
