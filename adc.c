/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Yahia Hamimi
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/interrupt.h>


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
#ifdef INTERRUPT_TECHNIQUE
volatile uint16 g_adcResult = 0;
#endif
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
#ifdef INTERRUPT_TECHNIQUE
ISR(ADC_vect)
{
	/*Interrupt will happen after value read operation then in ISR only save
	 * this value in a global variable
	 */
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = given ref_volt in the configuration structure
	 * whether ( AREF,AVCC,InternalAREF)
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 * (leave it to it's default)
	 */
	ADMUX=(ADMUX&0x3F)|((Config_Ptr->ref_volt)<<REFS0);
#ifdef POLLING_TECHNIQUE
	/* ADCSRA Register Bits (in polling) Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = given prescaler in the configuration structure
	 * whether (N=2,4,8,16,32,64,128) then frequency = F_CPU/N
	 * (Note that:ADC must operate in range 50-200Khz)
	 */
	ADCSRA=(ADCSRA&0xF8)|(Config_Ptr->prescaler)|(1 << ADEN);
#endif
#ifdef INTERRUPT_TECHNIQUE
	/* ADCSRA Register Bits (in interrupt) Description:
		 * ADEN    = 1 Enable ADC
		 * ADIE    = 1 Enable ADC Interrupt
		 * ADATE   = 0 Disable Auto Trigger
		 * ADPS2:0 = given prescaler in the configuration structure
		 * whether (N=2,4,8,16,32,64,128) then frequency = F_CPU/N
		 * (Note that:ADC must operate in range 50-200Khz)
		 */
	ADCSRA=(ADCSRA&0xF8)|(Config_Ptr->prescaler)|(1 << ADEN)|(1<<ADIE);
#endif
}
#ifdef POLLING_TECHNIQUE
uint16 ADC_readChannel(uint8 channel_num)
{
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);
	/* Choose the correct channel by setting the channel number in MUX4:0 bits
	 *Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	SET_BIT(ADCSRA, ADSC); /* Start conversion write '1' to ADSC */
	while (BIT_IS_CLEAR(ADCSRA, ADIF))
		;				   /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA, ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC;
	/* Read the digital value from the data register */
}
#endif
#ifdef INTERRUPT_TECHNIQUE
void ADC_readChannel(uint8 channel_num)
{
	 /* Input channel number must be from 0 --> 7
	  *Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = (ADMUX&0xE0) | (channel_num&0x07); /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}
#endif


