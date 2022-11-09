/*This file is used to process time related functions. */

#include "TimerProcess.h"
#include "MyFlag.h"
uint8_t gc500msCount = 0;

void Time_Process(void)
{
	gc500msCount++;
	Clr_Count500ms_Flag;
	if(gc500msCount > 2)
	{
		gc500msCount = 0;
		Set_Count500ms_Flag;
		
		
	}
}


