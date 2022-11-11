#include "bsp_buzzer.h"
#include "MyFlag.h"

uint8_t gcBuzzerTime;
uint8_t gcAliumBuzzerStatus;
uint16_t giAliunBuzzerTime;
uint8_t gcBuzzerCount;        //·äÃùÆ÷Ãù½ÐµÄÑ­»·´ÎÊý

void Buzzer_Process(void)
{
	/*°´¼üÒô*/
	if(KeyBuzzer_Flag)
	{
		if (gcBuzzerTime == 0)        //6.30
		{
			Set_41KHzBuzzer;    //4KHz
		}
		gcBuzzerTime++;
		if (gcBuzzerTime > 4)
		{
				gcBuzzerTime = 0;
				Clr_Buzzer;
				Clr_KeyBuzzer_Flag;
		}
	}
	else if(Key3s_Buzzer_Flag)
	{
		if (gcBuzzerTime == 0)
		{
			Set_41KHzBuzzer;
		}
		gcBuzzerTime++;
		if (gcBuzzerTime > 100)
		{
			gcBuzzerTime = 0;
			Clr_Buzzer;
			Clr_Key3s_Buzzer_Flag;
		}
	}
	else if(AlarmBuzzer_Flag)
	{
		switch(gcAliumBuzzerStatus)
		{
			case 0:
			{
				Set_2KHzBuzzer;
				giAliunBuzzerTime = 0;
				gcAliumBuzzerStatus = 1;
			}
			break;
			case 1:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 80)
				{
					Clr_Buzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 2;
				}		
			}
			break;
			case 2:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 200)
				{
					Set_2KHzBuzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 3;
				}
			}
			break;
			case 3:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 80)
				{
					Clr_Buzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 4;
				}		
			}
			break;
			case 4:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 200)
				{
					Set_2KHzBuzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 5;
				}
			}
			break;
			case 5:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 80)
				{
					Clr_Buzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 6;
				}	
			}
			break;
			case 6:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 200)
				{
					Set_2KHzBuzzer;
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 5;
				}
			}
			break;
			case 7:
			{
				giAliunBuzzerTime++;
				if(giAliunBuzzerTime > 1410)
				{
					giAliunBuzzerTime = 0;
					gcAliumBuzzerStatus = 0;
					gcBuzzerCount++;
					if(gcBuzzerCount > 26)
					{
						gcBuzzerCount = 0;
						Clr_AlarmBuzzer_Flag;
					}
				}
			}
			break;
		}
			
	}
	else
	{
		Clr_Buzzer;
	}
	
}





