/**
 ******************************************************************************
 * @file    task_rc.c
 * @author  TP-Thread
 * @brief   Function implementing the Rc thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  Function implementing the Mixer thread.
 * @param  argument: Not used
 * @retval None
 */
void rcTask(void *argument)
{
    sbusStart();
	timStart();
	
	acPpidInit();
	
    while (1)
    {	
		rcRemoteCtrl();
        osDelay(10);
    }
}
