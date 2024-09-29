/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: Yahia Hamimi
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"



/*******************************************************************************
 *                              Typedefs & Definitions                                  *
 *******************************************************************************/
/*Only one of them must be activated*/

#define POLLING_TECHNIQUE
//#define INTERRUPT_TECHNIQUE


#define ADC_MAXIMUM_VALUE 1023
#define ADC_REF_VOLT_VALUE 2.56




//#ifdef  POLLING_TECHNIQUE
//typedef enum{
//	Polling_technique,
//	Interrupt_technique
//}ADC_Technique_driver;

typedef enum{
AREF,
AVCC,
Internal_AREF=3
}ADC_ReferenceVolatge;

typedef enum{
	F_cpu,
	F_cpu_2,
	F_cpu_4,
	F_cpu_8,
	F_cpu_16,
	F_cpu_32,
	F_cpu_64,
	F_cpu_128
}ADC_Prescaler;


typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
#ifdef INTERRUPT_TECHNIQUE
/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;
#endif
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#ifdef POLLING_TECHNIQUE
uint16 ADC_readChannel(uint8 channel_num);
#endif
#ifdef INTERRUPT_TECHNIQUE
void ADC_readChannel(uint8 channel_num);
#endif



#endif /* ADC_H_ */
