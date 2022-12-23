/******************************************************************************
 *
 * File Name: CONTROL_main.c
 *
 * Description: Source file for the CONTROL main code.
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "twi.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "CONTROL_ECU_Functions.h"

/*
 * Configuring the UART and TWI.
 */
UART_ConfigType uartConfig = { EIGHT_BIT , DISABLED , ONE , BAUD_RATE };
TWI_ConfigType twiConfig = { 0x01 , FAST};

int main(void){
	/*Enabling the s-reg bit*/
	sei();

	/*Initializing the TWI the required configurations*/
	TWI_init(&twiConfig);

	/*Variable to store the chosen option*/
	uint8 option;

	/*Initializing the UART the required configurations*/
	UART_init(&uartConfig);

	while(1)
	{
		option = 0;

		/* Making sure that both micros are ready */
		while(UART_recieveByte() != MICRO_READY);

		UART_sendByte(MICRO_READY);

		/* Receiving the option from the HMI-micro */
		option = UART_recieveByte();

		/* Switching on the option chosen by the user */
		switch (option)
		{
		case 1 :
			CONTROL_checkPassword();
			break;
		case 2 :
			CONTROL_changePassword();
			break;
		case 3 :
			CONTROL_changePassword();
			break;
		case 4 :
			CONTROL_rotateMotor();
			break;
		case 5 :
			CONTROL_passNotMatched();
			break;
		}

	}
}
