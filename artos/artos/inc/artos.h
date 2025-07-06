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
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include "drv_key.h"
#include "drv_exti.h"
#include "drv_uart.h"
#include "drv_tim.h" 
#include "drv_ist8310.h"
#include "drv_bmi088.h"

#include "prot_ano.h"
#include "prot_sbus.h"

#include "algo_pid.h"
#include "algo_remote_ctrl.h"
#include "algo_attitude_ctrl.h"
// #include "algo_position_ctrl.h"

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define ABS_MAX_LIMIT(input, max)		(input > max ? max : (input < -max ? max : input))
#define ABS_MIN_LIMIT(input, min)		(input < min ? 0 : (input > -min ? 0 : input))
#define PWM_LIMIT(input, min, max)		(input > max ? max : (input < min ? min : input))

#define TIP

#if defined(TIP)
	extern ADC_HandleTypeDef hadc1;
	extern ADC_HandleTypeDef hadc3;

	extern CAN_HandleTypeDef hcan1;
	// extern CAN_HandleTypeDef hcan2;

	extern I2C_HandleTypeDef hi2c3;

	extern SPI_HandleTypeDef hspi1;

	extern TIM_HandleTypeDef htim1;
	extern TIM_HandleTypeDef htim4;
	extern TIM_HandleTypeDef htim10;

	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart3;
	extern DMA_HandleTypeDef hdma_usart3_rx;
	extern UART_HandleTypeDef huart6;

	#define LED_R_On()              HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)    
	#define LED_R_Off()  	        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)     
	#define LED_R_Toggle()          HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)

	#define LED_G_On()		        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)    
	#define LED_G_Off()  	        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET)     
	#define LED_G_Toggle()          HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)	

	#define LED_B_On()		        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)    
	#define LED_B_Off()  	        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)     
	#define LED_B_Toggle()          HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

	//#define BEEP_On()		        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)    
	//#define BEEP_Off()  	        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)     
	//#define BEEP_Toggle()           HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin)

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
