#include "MyFlag.h"

struct Flag_Class MyFlag;

// N = 2^32/365/24/60/60 = 136 ��

/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

/*ʱ��ṹ�壬����ʱ��2000-01-01 00:00:08*/
struct rtc_time clocktime=
{
8,0,0,1,1,2000,0
};

extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;


uint8_t gc10mscount = 0; 
uint8_t gc250mscount = 0;
uint16_t gi1scount = 0;
uint32_t clock_timestamp;
uint32_t current_timestamp;


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	/*ϵͳ�δ�ʱ����ʼ��*/
  SysTick_Init();
	
	/*TIM4��ʼ��*/
	GENERAL_TIM_Init();
	
	/*LED Init*/
	LED_GPIO_Config();
	
	/*������ʼ��*/
	Key_GPIO_Config();
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/*�����GPIO��ʼ��*/
	Digital_Tube_Config();  

  /*RTC�ж����ȼ�����*/
  RTC_NVIC_Config();
	
	/*���ó�ʼʱ��*/
  RTC_CheckAndConfig(&systmtime);
	
	/*Ĭ�Ͽ�ʱ����ʾ*/
	Set_DISPLAY_ON_Flag;
	
	/**/
	Clr_Count1s_Flag;
 
	#if 0     //��ʱ�ر��������ʾ
		number_Display();  
	#endif
			
  while(1)
	{	
			
		
		  /*10ms��һ��*/
			if(gc10mscount >= 10)
			{
				gc10mscount = 0;
				gc250mscount++;				
				
				 if (TimeDisplay == 1)
					{
						#if 1
						/* ��ǰʱ�� */
						current_timestamp = RTC_GetCounter();
						Time_Display( current_timestamp,&systmtime);         //���԰�����������������ʾ�ĺ���
						#endif
						
						TimeDisplay = 0;
					}
					
				 /*�����Ĵ���*/
			   Key_Process();
					
//        /*����ʱ��(��ѡ���ڻ��߰�������)*/	
//				Time_Set();
					
				/*250ms����һ��*/
			  if(gc250mscount >= 25)
				{
					gc250mscount = 0;
					
					#if 1
						Time_Process();
					#endif
				}
				
			}
	}
}
/*********************************************END OF FILE**********************/
