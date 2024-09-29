 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Yahia Hamimi
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"
#ifdef INTERRUPT_TECHNIQUE
#include<util/delay.h>
#endif

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */

uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

#ifdef POLLING_TECHNIQUE
	uint16 adc_value = 0;
	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
#endif
#ifdef INTERRUPT_TECHNIQUE
	ADC_readChannel(SENSOR_CHANNEL_ID);
	_delay_ms(5);
		/* Calculate the temperature from the ADC value*/
		temp_value = (uint8)(((uint32)g_adcResult * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));
#endif
		return temp_value;
}



