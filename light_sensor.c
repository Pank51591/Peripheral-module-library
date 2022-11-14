// 由于ADC的最大时钟不超过14MHz，所以需要把时钟降下来。
// ADC时钟分频器；六分频；时钟从APB2总线来，最大为72MHz，所以需要六分频后12MHz。
RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	
float ADC_GetValue(void)
{
	uint32_t Value = 0;
	float ret = 0.0;
	
	for(uint8_t i = 0;i < 30;i++)
	{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));        //转换结束标志， 转换完成该标志就清零
	
		Value += ADC_GetConversionValue(ADC1);		
	}

	Value /= 30;   // 这里求的是平均值
	
	ret = 30.303 * (3.3 - Value *(3.3/4095));
	
	// 整体上表示模数转换后的光度；4095表示12为的ADC的精度（不能变）；
	// 3.3表示这个引脚最大承受电压
	/*光强最大100  */
	return ret;

}



int main (void)
{
	
	Light_Sensor_GPIOinit();       //光照传感器 GPIO初始化
	
	MyUsart_init();
	
	ADC_init();	
	
	while(1)
	{
		 
		
		printf("ADC = %.3f \n",ADC_GetValue());
		Delay_ms(500);			
	}
}
