/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: source file for main
 *
 * Author: Yahia Hamimi
 ******************************************************************************/

#include "adc.h"
#include "lcd.h"
#include "dcmotor.h"
#include "timer0_pwm.h"
#include "lm35_sensor.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
void display_states(uint8 temp)
{
	LCD_moveCursor(1, 7);
	LCD_intgerToString(temp);
	LCD_displayCharacter(' ');
	LCD_moveCursor(0, 7);
}

int main(void)
{
	ADC_ConfigType ADC_config_data = {Internal_AREF, F_cpu_8};
	uint8 temperature;
#ifdef INTERRUPT_TECHNIQUE
	SREG |= (1 << 7); /* Enable Global Interrupts */
#endif

	ADC_init(&ADC_config_data);
	DcMotor_Init();
	PWM_Timer0_Start(0);
	LCD_init();
	LCD_displayString("FAN is  ");
	LCD_moveCursor(1, 0);
	LCD_displayString("Temp =     C");

	while (1)
	{
		temperature = LM35_getTemperature();
		if (temperature < 30)
		{
			DcMotor_Rotate(Stop, 0);
			PWM_Timer0_Start(g_dutyCycle);
			display_states(temperature);
			LCD_displayString("OFF");
		}
		else if (temperature >= 30 && temperature < 60)
		{
			DcMotor_Rotate(CW, 25);
			PWM_Timer0_Start(g_dutyCycle);
			display_states(temperature);
			LCD_displayString("ON ");
		}
		else if (temperature >= 60 && temperature < 90)
		{
			DcMotor_Rotate(CW, 50);
			PWM_Timer0_Start(g_dutyCycle);
			display_states(temperature);
			LCD_displayString("ON ");
		}
		else if (temperature >= 90 && temperature < 120)
		{
			DcMotor_Rotate(CW, 75);
			PWM_Timer0_Start(g_dutyCycle);
			display_states(temperature);
			LCD_displayString("ON ");
		}
		else if (temperature >= 120)
		{
			DcMotor_Rotate(CW, 100);
			PWM_Timer0_Start(g_dutyCycle);
			display_states(temperature);
			LCD_displayString("ON ");
		}
	}
}
