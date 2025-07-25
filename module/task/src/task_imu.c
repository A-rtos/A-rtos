/**
 ******************************************************************************
 * @file    task_imu.c
 * @author  TP-Thread
 * @brief   Function implementing the Imu thread.
 *		    利用陀螺仪加速度计bmi088，磁力计ist8310，完成姿态解算，得出欧拉角，
 *          提供通过bmi088的data ready 中断完成外部触发，减少数据等待延迟
 *          通过DMA的SPI传输节约CPU时间.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "artos.h"

/* Private includes ----------------------------------------------------------*/
#include "algo_mahony_ahrs.h"

/* Private macro -------------------------------------------------------------*/
#define INT_EVENT (0x01 << 0) // 设置事件掩码的位 0
#define FIN_EVENT (0x01 << 1) // 设置事件掩码的位 1

/* Private variables ---------------------------------------------------------*/
extern osEventFlagsId_t imu_eventHandle;

// IMU温度PID
static pid_t temp_pid;

// IMU温度PID参数：kp ki kd ilimit outlimit
float temp_pid_param[5] = {1600, 0.1, 0, 4400, 4500};

/* Private function prototypes -----------------------------------------------*/
void imuQuaternionUpdate(float gyro[3], float accel[3], float mag[3]);
void imuAttitudeGet(float *angle, float *rate);
void imuTempCtrl(pid_t *pid);

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	imu任务, 初始化 bmi088, ist8310, 计算欧拉角
 * @param	argument: NULL
 */
void taskIMU(void *argument)
{
	bmi088Init();  // 初始化BMI088
    ist8310Init(); // 初始化IST8310

    // IMU温控PID初始化
    pidInit(&temp_pid, temp_pid_param);
    // 开启温控PWM通道，使定时器对应通道开始 PWM 输出
    timTempStart();

    osEventFlagsSet(imu_eventHandle, FIN_EVENT);

    while (1)
    {
        osEventFlagsWait(imu_eventHandle, INT_EVENT | FIN_EVENT, osFlagsWaitAll, portMAX_DELAY);
		
        // 读取数据
        bmi088Read(bmi088_data.gyro, bmi088_data.accel, &bmi088_data.temp);
        ist8310Read(ist8310_data.mag);

        imuQuaternionUpdate(bmi088_data.gyro, bmi088_data.accel, ist8310_data.mag);
        imuAttitudeGet(angle_m, rate_m);
        // printf("the Yaw value is :%f \n", Yaw);

		temp_pid.measured = bmi088_data.temp;
        imuTempCtrl(&temp_pid);
        //printf("the temp value is: %.2f \n", bmi088_data.temp);

        osEventFlagsSet(imu_eventHandle, FIN_EVENT);
    }
}

/**
 * @brief	更新四元数
 */
void imuQuaternionUpdate(float gyro[3], float accel[3], float mag[3])
{
    MahonyAHRSupdate(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], mag[0], mag[1], mag[2]);
    // MahonyAHRSupdateIMU(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2]);
}

/**
 * @brief	测量当前姿态角、角速度
 */
void imuAttitudeGet(float *angle, float *rate)
{
    angle[0] = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.3f;
    angle[1] = asinf(2.0f * (q0 * q2 - q1 * q3)) * 57.3f;
    angle[2] = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.3f;
	
	rate[0] = bmi088_data.gyro[0];
	rate[1] = bmi088_data.gyro[1];
	rate[2] = bmi088_data.gyro[2];
}

/**
 * @brief   控制bmi088的温度
 * @param	temp	bmi088的温度
 */
void imuTempCtrl(pid_t *pid)
{
    static uint16_t tempPWM;

	pid->desired = 40.0f;
    pidCalculate(&temp_pid);

    if (temp_pid.out < 0.0f)
    {
        temp_pid.out = 0.0f;
    }

    tempPWM = temp_pid.out;
    __HAL_TIM_SetCompare(&ttim, TTIM_CHANNEL, tempPWM);
}

/**
 * @brief	IMU数据更新中断回调函数
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == INT1_GYRO_Pin) // 加速度计数据更新中断
    {
        osEventFlagsSet(imu_eventHandle, INT_EVENT);
    }
}
