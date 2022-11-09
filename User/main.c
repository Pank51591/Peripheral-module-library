#include "MyFlag.h"

struct Flag_Class MyFlag;

// N = 2^32/365/24/60/60 = 136 年

/*时间结构体，默认时间2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

/*时间结构体，闹钟时间2000-01-01 00:00:08*/
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	/*系统滴答定时器初始化*/
  SysTick_Init();
	
	/*TIM4初始化*/
	GENERAL_TIM_Init();
	
	/*LED Init*/
	LED_GPIO_Config();
	
	/*按键初始化*/
	Key_GPIO_Config();
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	/*数码管GPIO初始化*/
	Digital_Tube_Config();  

  /*RTC中断优先级配置*/
  RTC_NVIC_Config();
	
	/*设置初始时间*/
  RTC_CheckAndConfig(&systmtime);
	
	/*默认开时间显示*/
	Set_DISPLAY_ON_Flag;
	
	/**/
	Clr_Count1s_Flag;
 
	#if 0     //暂时关闭数码管显示
		number_Display();  
	#endif
			
  while(1)
	{	
			
		
		  /*10ms进一次*/
			if(gc10mscount >= 10)
			{
				gc10mscount = 0;
				gc250mscount++;				
				
				 if (TimeDisplay == 1)
					{
						#if 1
						/* 当前时间 */
						current_timestamp = RTC_GetCounter();
						Time_Display( current_timestamp,&systmtime);         //可以把这个用来做数码管显示的函数
						#endif
						
						TimeDisplay = 0;
					}
					
				 /*按键的处理*/
			   Key_Process();
					
//        /*设置时间(可选串口或者按键设置)*/	
//				Time_Set();
					
				/*250ms运行一次*/
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
