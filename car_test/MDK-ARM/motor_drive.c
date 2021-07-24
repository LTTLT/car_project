/*
l298n驱动电机文件
使用引脚(左边in1，右边in2)
电机1：PA5,PA6,PB4(PWM)
电机2：PB2,PB10,PB5(PWM)
电机3：PB9,PB8,PB0(PWM)
电机4：PB7,PB6,PB1(PWM)
超声波         超声波
 电机2         电机1







 电机3          电机4
*/
#include "motor_drive.h"
/*
函数名：motor_init
作用：l298n电机驱动初始化
备注：
*/
pid_type_def motor_pid_struct[4];//声明底盘电机pid结构体
motor_data *speed_data;
fp32  motor_pid[3] = { 0.0f ,0.0f ,0.0f };

//typedef struct
//{
//    uint8_t mode;
//    //PID 三参数
//    fp32 Kp;
//    fp32 Ki;
//    fp32 Kd;

//    fp32 max_out;  //最大输出
//    fp32 max_iout; //最大积分输出

//    fp32 set;
//    fp32 fdb;

//    fp32 out;
//    fp32 Pout;
//    fp32 Iout;
//    fp32 Dout;
//    fp32 Dbuf[3];  //微分项 0最新 1上一次 2上上次
//    fp32 error[3]; //误差项 0最新 1上一次 2上上次

//} pid_type_def;

void motor_drive_init(void)
{
	uint8_t i;
	HAL_GPIO_WritePin(GPIOA, motor1_in1_Pin|motor1_in2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, motor2_in1_Pin|motor2_in2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, motor3_in1_Pin|motor3_in2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, motor4_in1_Pin|motor4_in2_Pin, GPIO_PIN_RESET);
	*speed_data = *get_chassis_data_point();
	for (i=0; i<4; i++)
	{
	PID_init(&motor_pid_struct[i], PID_POSITION,motor_pid,5.0f, 5.0f);
	}
}
/*
函数名：motor_drive
作用：l298n电机驱动
备注：pwm数值从600-1000进行调速
*/
void motor_drive (uint8_t mode ,fp32 motor[4])
{
	switch(mode)
	{
		case MOTOR_NORMAL:	
			HAL_GPIO_WritePin(GPIOA, motor1_in1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, motor1_in2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, motor2_in1_Pin|motor3_in1_Pin|motor4_in1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, motor2_in2_Pin|motor3_in2_Pin|motor4_in2_Pin, GPIO_PIN_SET);			
		break;
		case MOTOR_STOP:
			HAL_GPIO_WritePin(GPIOA, motor1_in1_Pin|motor1_in2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, motor2_in1_Pin|motor2_in2_Pin, GPIO_PIN_RESET);			
			HAL_GPIO_WritePin(GPIOB, motor3_in1_Pin|motor3_in2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, motor4_in1_Pin|motor4_in2_Pin, GPIO_PIN_RESET);
			break;
		case MOTOR_CONTROL:
			HAL_GPIO_WritePin(GPIOA, motor1_in1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, motor1_in2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, motor2_in1_Pin|motor3_in1_Pin|motor4_in1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, motor2_in2_Pin|motor3_in2_Pin|motor4_in2_Pin, GPIO_PIN_SET);	
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, motor[1] );
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, motor[2]);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, motor[3]);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, motor[4] );		
		break;
	}
}

/*
函数名：Coordinate_system_velocity
作用：坐标系转化为轮式速度
备注：单位m/s
*/

void Coordinate_system_velocity(uint32_t  vx, uint32_t vy,uint32_t vz)
{
	uint8_t i ;
	fp32 v[4] ;
	v[0] = vy-vx+vz*(7.5f+5.8f)/100;
	v[1]= vy+vx-vz*(7.5f+5.8f)/100;
	v[2] = vy-vx-vz*(7.5f+5.8f)/100;
	v[3] = vy+vx+vz*(7.5f+5.8f)/100;
	for(i=0;i<4;i++)
	{
			PID_calc(&motor_pid_struct[i], speed_data->v [i] , v[i]);
			speed_data->speed_set[i] = motor_pid_struct[i].out ;
	}
		motor_drive (3 ,speed_data->speed_set);
}
