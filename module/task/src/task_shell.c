/**
 ******************************************************************************
 * @file    task_shell.c
 * @author  TP-Thread
 * @brief   Function implementing the Shell thread.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "artos.h"
#include "semphr.h"
#include "shell.h"

/* Private variables ---------------------------------------------------------*/
Shell shell;
char shellBuffer[512];

extern osMutexId_t shell_mutexHandle;

/* Private functions ---------------------------------------------------------*/
/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际写入的数据长度
 */
short userShellWrite(char *data, unsigned short len)
{
	HAL_UART_Transmit(&duart, (uint8_t *)data, len, 0x1FF);
    return len;
}

/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际读取到
 */
short userShellRead(char *data, unsigned short len)
{
    return HAL_UART_Receive(&duart, (uint8_t *)&data, len, 0);
}

//uint8_t recv_buf = 0;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    /* 判断是哪个串口触发的中断 */
//    if(huart ->Instance == USART1)
//    {
//        //调用shell处理数据的接口
//     shellHandler(&shell, recv_buf);
//        //使能串口中断接收
//     HAL_UART_Receive_IT(&huart1, (uint8_t*)&recv_buf, 1);
//    }
//}

int test(int i, char ch, char *str)
{
    printf("input int: %d, char: %c, string: %s\r\n", i, ch, str);
 
 return 0;
}

//导出到命令列表里
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), test, test, test);


/**
 * @brief 用户shell上锁
 * 
 * @param shell shell
 * 
 * @return int 0
 */
int userShellLock(Shell *shell)
{
    xSemaphoreTakeRecursive(shell_mutexHandle, portMAX_DELAY);
    return 0;
}

/**
 * @brief 用户shell解锁
 * 
 * @param shell shell
 * 
 * @return int 0
 */
int userShellUnlock(Shell *shell)
{
    xSemaphoreGiveRecursive(shell_mutexHandle);
    return 0;
}

/**
 * @brief shell 任务
 * 
 * @param param 参数(shell对象)
 * 
 */
void taskShell(void *argument)
{
    shell.write = userShellWrite;
    shell.read = userShellRead;
    shell.lock = userShellLock;
    shell.unlock = userShellUnlock;
    shellInit(&shell, shellBuffer, 512);
	
    char data;
#if SHELL_TASK_WHILE == 1
    while(1)
    {
#endif
        if (shell.read && shell.read(&data, 1) == 1)
        {
            shellHandler(&shell, data);
        }
#if SHELL_TASK_WHILE == 1
    }
#endif
}
