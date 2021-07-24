/*
l298n��������ļ�
ʹ������(���in1���ұ�in2)
���1��PA5,PA6,PB4(PWM)
���2��PB2,PB10,PB5(PWM)
���3��PB9,PB8,PB0(PWM)
���4��PB7,PB6,PB1(PWM)
������         ������
 ���2         ���1







 ���3          ���4
*/
#include "motor_drive.h"
/*
��������motor_init
���ã�l298n���������ʼ��
��ע��
*/
pid_type_def motor_pid_struct[4];//�������̵��pid�ṹ��
motor_data *speed_data;
fp32  motor_pid[3] = { 0.0f ,0.0f ,0.0f };

//typedef struct
//{
//    uint8_t mode;
//    //PID ������
//    fp32 Kp;
//    fp32 Ki;
//    fp32 Kd;

//    fp32 max_out;  //������
//    fp32 max_iout; //���������

//    fp32 set;
//    fp32 fdb;

//    fp32 out;
//    fp32 Pout;
//    fp32 Iout;
//    fp32 Dout;
//    fp32 Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
//    fp32 error[3]; //����� 0���� 1��һ�� 2���ϴ�

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
��������motor_drive
���ã�l298n�������
��ע��pwm��ֵ��600-1000���е���
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
��������Coordinate_system_velocity
���ã�����ϵת��Ϊ��ʽ�ٶ�
��ע����λm/s
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
