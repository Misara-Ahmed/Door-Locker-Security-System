/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the ATmega32 TIMER1 driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*
 * ISR for the overflow mode (normal mode).
 */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Setting the callback function */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * ISR for the compare mode.
 */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Setting the callback function */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * Function to setup the initialization for Timer1.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	// Initial start for the timer.
	TCNT1 = Config_Ptr->initial_value;

	// Setting compare value.
	OCR1A = Config_Ptr->compare_value;

	TCCR1A |= (1<<FOC1A);

	/*Setting the timer mode & Setting the prescaler */

	TCCR1B = (TCCR1B & 0xF8) | Config_Ptr->prescaler;
	TCCR1B = (TCCR1B & 0xF7) | (Config_Ptr->mode << 1);

	// Enabling the compare mode timer interrupt.
	TIMSK = (1<<OCIE1A);
}

/*
 * Description :
 * Function to stop Timer1.
 */
void Timer1_deInit(void)
{
	// Closing the clock source to stop the timer.
	TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12);
}

/*
 * Description :
 * Function to set the call back function of the Timer.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
