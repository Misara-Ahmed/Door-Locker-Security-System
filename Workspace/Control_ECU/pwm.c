/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the ATmega32 PWM driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "pwm.h"
#include <avr/io.h>

/*
 * Description :
 * Function to setup Timer0 to generate PWM signal for the motor.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC */
	SET_BIT(DDRB,PB3);

	/* Set Timer Initial Value to 0 */
	TCNT0 = 0;

//	DDRB  = DDRB | (1<<PB3);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	CLEAR_BIT(TCCR0,FOC0);
	CLEAR_BIT(TCCR0,COM00);
	CLEAR_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS02);
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	/* setting the compare value */
	switch (duty_cycle)
	{
	case 0 :
		OCR0 =0;
		break;
	case 25 :
		OCR0 = 64;
		break;
	case 50 :
		OCR0 = 128;
		break;
	case 75 :
		OCR0 = 191;
		break;
	case 100 :
		OCR0 = 255;
		break;
	}
}

