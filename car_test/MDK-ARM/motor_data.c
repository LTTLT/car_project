/*
文件：获取编码器数据
使用引脚
PA4（EXTI4）电机1，PA3（EXTI3）电机2，PB12（EXTI12）电机3，PB13（EXTI13）电机4
*/
#include "motor_data.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "wcnm.h"

float motor_cnt1,motor_cnt2 ,motor_cnt3,motor_cnt4= 0;
float motor1_speed,motor2_speed,motor3_speed,motor4_speed;
motor_data chassis_data;

/*
函数名：100ms中断
作用：每0.1s产生一次中断检测速度，并以/s单位输出为变量
备注：
*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
    if (htim->Instance == TIM1)
			{
				motor1_speed = motor_cnt1/10;
				motor2_speed = motor_cnt2/10;
				motor3_speed = motor_cnt3/10;
				motor4_speed = motor_cnt4/10;
				printf("speed= %f \r\n", motor1_speed);
				chassis_data.v[0] = motor_cnt1;//赋值
				chassis_data.v[1] = motor_cnt2;
				chassis_data.v[2] = motor_cnt3;
				chassis_data.v[3] = motor_cnt4;
				motor_cnt1 = 0;
				motor_cnt2 = 0;
				motor_cnt3	= 0;
				motor_cnt4	= 0;
			}
}
	
/*
函数名：读取编码器数值
作用：码盘每产生一次电平就进入中断并记录
备注：
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if(GPIO_Pin == GPIO_PIN_4)
		{
			motor_cnt1++;
		}
				if(GPIO_Pin == GPIO_PIN_3)
		{
			motor_cnt2++;
		}
				if(GPIO_Pin == GPIO_PIN_12)
		{
			motor_cnt3++;
		}
				if(GPIO_Pin == GPIO_PIN_13)
		{
			motor_cnt4++;
		}
}

/*
函数名：get_chassis_data_point
作用：	回调指针
备注：
*/
extern const  motor_data *get_chassis_data_point(void)
{
	
    return &chassis_data;
}

