#include "wcnm.h"
/*
��������Delay_us
���ã���ʱ΢�루��ʵ��̫���ܣ�����ֻҪ��֤���ڵ���20us���ɣ�
��ע��
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
��������HAL_TIM_IC_CaptureCallback��ຯ��
���ã���ຯ��
��ע�����ϳ���
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
			if(Edge == 0)          //����������
			{
				RisingTime = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);    //��ȡ������ʱ���
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);   //�л������� �½���
				HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);     //�л��������ж�
 
				Edge = 1;          	 //�����Ա�ֵ��Ϊ�½���
			}
			else if(Edge == 1)     //�����½���
			{
				FallingTime = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);    //��ȡ�½���ʱ���
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);     //�л������� ������
				HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);   	 //�л������Ժ������ж�
 
				HighTime = FallingTime < RisingTime ? FallingTime + 0xffff - RisingTime + 1 : FallingTime - RisingTime;
				//�ߵ�ƽʱ��=�½���ʱ�� - ������ʱ��(���½���ʱ��<������ʱ��FallingTime + 0xffff - RisingTime + 1)
				dis_fm = HighTime * 17/ 100; //������� HighTime*��1/100000����*34000����/2
				printf("distance = %dcm \r\n", dis_fm);		
				Edge = 0;		  			 //һ�βɼ���ϣ����������ر�־
			}
		} 
	}
}
/*
��������fputc��printf�ض���
���ã����������Ϳ���printf��
��ע��
*/
int fputc(int ch, FILE *f)
{
      HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1, 0xFFFF);
      return ch;
}
/*
��������get_distance_data
���ã���ȡ��������
��ע����������trig�ߵ�ƽ����20us���ܴ������������
*/
void get_distance_data(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	
	Delay_us (20);
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	
}
