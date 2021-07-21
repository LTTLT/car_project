#include "wcnm.h"
/*
函数名：Delay_us
作用：延时微秒（其实不太可能，不过只要保证大于等于20us即可）
备注：
*/
void Delay_us(uint32_t t)
{   
    int n  =  11;
    while(--t)
    {
        while(--n);
        n = 11;
    }
}
/*
函数名：HAL_TIM_IC_CaptureCallback测距函数
作用：测距函数
备注：网上抄的
*/
uint8_t Edge = 0;
uint8_t dis_fm;
uint32_t RisingTime ,FallingTime= 0;
uint16_t HighTime ;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  UNUSED(htim);
	
	if(htim->Instance == htim2.Instance)  //TIMER2
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  //CHANNEL_1
		{
			if(Edge == 0)          //捕获上升沿
			{
				RisingTime = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);    //获取上升沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);   //切换捕获极性 下降沿
				HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);     //切换后重启中断
 
				Edge = 1;          	 //捕获极性标值换为下降沿
			}
			else if(Edge == 1)     //捕获下降沿
			{
				FallingTime = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);    //获取下降沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);     //切换捕获极性 上升沿
				HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   	 //切换捕获极性后重启中断
 
				HighTime = FallingTime < RisingTime ? FallingTime + 0xffff - RisingTime + 1 : FallingTime - RisingTime;
				//高电平时间=下降沿时间 - 上升沿时间(若下降沿时间<上升沿时间FallingTime + 0xffff - RisingTime + 1)
				dis_fm = HighTime * 17/ 100; //距离计算 HighTime*（1/100000）秒*34000厘米/2
				printf("distance = %dcm \r\n", dis_fm);		
				Edge = 0;		  			 //一次采集完毕，捕获上升沿标志
			}
		} 
	}
}
/*
函数名：fputc（printf重定向）
作用：有了这个你就可以printf了
备注：
*/
int fputc(int ch, FILE *f)
{
      HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1, 0xFFFF);
      return ch;
}
/*
函数名：get_distance_data
作用：获取距离数据
备注：设置引脚trig高电平大于20us才能触发超声波测距
*/
void get_distance_data(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	
	Delay_us (20);
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	
}
