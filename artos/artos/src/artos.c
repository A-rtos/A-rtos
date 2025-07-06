/**
  ******************************************************************************
  * @file    artos.c
  * @author  TP-Thread
  * @brief   Thread Initialization.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Private includes ----------------------------------------------------------*/
#include "SEGGER_SYSVIEW.h"

/* Private variables ---------------------------------------------------------*/
/* Definitions for shell */
osThreadId_t shellHandle;
const osThreadAttr_t shell_attributes = {
  .name = "shell",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for imu */
osThreadId_t imuHandle;
const osThreadAttr_t imu_attributes = {
  .name = "imu",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for rc */
osThreadId_t rcHandle;
const osThreadAttr_t rc_attributes = {
  .name = "rc",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for shell_mutex */
osMutexId_t shell_mutexHandle;
const osMutexAttr_t shell_mutex_attributes = {
  .name = "shell_mutex"
};
/* Definitions for imu_event */
osEventFlagsId_t imu_eventHandle;
const osEventFlagsAttr_t imu_event_attributes = {
  .name = "imu_event"
};

/* Private function prototypes -----------------------------------------------*/
extern void taskShell(void *argument);
extern void taskIMU(void *argument);
extern void taskRC(void *argument);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Thread initialization
  * @param  None
  * @retval None
  */
void osThreadInitialize(void)
{
	/* SystemView Init */
	SEGGER_SYSVIEW_Conf();

	/* Create the thread(s) */
	/* creation of shell */
    // shellHandle = osThreadNew(shellTask, NULL, &shell_attributes);

	/* creation of imu */
	imuHandle = osThreadNew(taskIMU, NULL, &imu_attributes);
	
	/* creation of rc */
	rcHandle = osThreadNew(taskRC, NULL, &rc_attributes);
	
	/* Create the mutex(es) */
	/* creation of shell_mutex */
	shell_mutexHandle = osMutexNew(&shell_mutex_attributes);
	
	/* Create the event(s) */
	/* creation of imu_event */
	imu_eventHandle = osEventFlagsNew(&imu_event_attributes);
}
