/******************************************************************************
 *
 * File Name: HMI_main.c
 *
 * Description: Source file for the HMI main code.
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "HMI_ECU_Functions.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/* UART configurations*/
UART_ConfigType uartConfig = { EIGHT_BIT , DISABLED , ONE , BAUD_RATE };

int main(void)
{
	/*Enabling the s-reg bit*/
	sei();

	/*Initializing the LCD*/
	LCD_init();

	_delay_ms(200);

	/*Initializing the UART the required configurations*/
	UART_init(&uartConfig);

	/*Creating the system password which is the first function to be called */
	HMI_createSystemPassword();
}
