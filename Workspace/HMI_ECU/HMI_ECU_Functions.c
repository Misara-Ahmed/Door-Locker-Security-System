/******************************************************************************
 *
 * File Name: HMI_ECU_Functions.c
 *
 * Description: Source file for the HMI Functions
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/


#include "HMI_ECU_Functions.h"
#include <util/delay.h>

/*******************************************************************************
 *                              Variables                                      *
 *******************************************************************************/

uint8 g_Password[PASSWORD_SIZE + 1];
uint8 passChecked;
uint8 g_HMIcount = 0;
uint8 g_tick = 0;
Timer1_ConfigType timerConfig = { 0 , 7800 , F_CPU_1024 , CTC_MODE};

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for making the user create the system password.
 */
void HMI_createSystemPassword(void)
{
	uint8 first_pass[PASSWORD_SIZE + 1];
	uint8 second_pass[PASSWORD_SIZE + 1];

	mcReady();

	UART_sendByte(1);

	HMI_enterPassDisplay();

	HMI_getAndDisplayPassword(first_pass);

	while( KEYPAD_getPressedKey() != ENTER );

	_delay_ms(500);

	LCD_clearScreen();

	LCD_displayString("plz re-enter the");

	LCD_moveCursor(1 , 0);

	LCD_displayString("same pass: ");

	HMI_getAndDisplayPassword(second_pass);


	while( KEYPAD_getPressedKey() != ENTER );

	_delay_ms(500);

	first_pass[5] = '#';
	second_pass[5] = '#' ;

	mcReady();

	UART_sendString(first_pass);

	while(UART_recieveByte() != MICRO_READY);

	UART_sendString(second_pass);

	while(UART_recieveByte() != MICRO_READY);

	passChecked = UART_recieveByte();

	if (passChecked)
	{
		HMI_mainOptions();
	}
	else
	{
		LCD_clearScreen();
		HMI_createSystemPassword();
	}
}

/*
 * Description :
 * Function responsible for displaying the main system options that the user can do.
 */
void HMI_mainOptions(void)
{
	uint8 keyPressed;

	g_HMIcount = 0;

	LCD_clearScreen();

	LCD_displayString("+ : Open Door");

	LCD_moveCursor(1, 0);

	LCD_displayString("- : Change Pass");

	keyPressed = KEYPAD_getPressedKey();

	switch(keyPressed)
	{
	case '+':
		HMI_openDoor();
		break;
	case '-':
		HMI_changePassword();
		break;
	}
}

/*
 * Description :
 * Function responsible for checking the password and if it is true it open the door.
 */
void HMI_openDoor(void)
{
	uint8 HMI_flag;

	_delay_ms(500);

	HMI_flag = checkPassWithControl();

	if (HMI_flag)
	{
		openDoorTrials();
	}
	else
	{
		mcReady();

		UART_sendByte(4);

		Timer1_setCallBack(HMI_callBack);

		Timer1_init(&timerConfig);

		LCD_clearScreen();
		LCD_displayString("Door is Unlocking");
		while(g_tick < 15);

		while(g_tick < 18);

		LCD_clearScreen();
		LCD_displayString("Door is locking");

		while(g_tick < 33);
		g_tick = 0 ;
		HMI_mainOptions();
	}
}

/*
 * Description :
 * Function responsible for changing the system password.
 */
void HMI_changePassword(void)
{
	uint8 HMI_flag;

	_delay_ms(500);

	HMI_flag = checkPassWithControl();

	_delay_ms(500);

	if(HMI_flag)
	{
		changePasswordTrials();

	}
	else
	{
		HMI_createSystemPassword();
	}
}

/*
 * Description :
 * Function responsible for displaying the password entering messages.
 */
void HMI_enterPassDisplay(void)
{
	LCD_clearScreen();

	LCD_displayString("plz enter pass:");

	LCD_moveCursor(1,0);
}

/*
 * Description :
 * Function responsible for making sure that the micro-controller is ready to send or receive.
 */
void mcReady(void)
{
	UART_sendByte(MICRO_READY);

	while(UART_recieveByte() != MICRO_READY);

}

/*
 * Description :
 * Function responsible for displaying error message on LCD for 1 minute then returning to the main options menu
 * when the password didn't match for 3 consecutive times.
 */
void HMI_passNotMatched(void)
{
	mcReady();

	UART_sendByte(5);

	Timer1_setCallBack(HMI_callBack);

	Timer1_init(&timerConfig);

	LCD_clearScreen();

	LCD_displayString(" ERROR ");
	while(g_tick < 60);

	g_tick = 0 ;

	HMI_mainOptions();
}

/*
 * Description :
 * Function responsible for taking the input password from the user and displaying * on the screen.
 */
void HMI_getAndDisplayPassword(uint8* password)
{
	for (int i = 0 ; i < PASSWORD_SIZE ; i++)
	{
		password[i] = KEYPAD_getPressedKey();
		_delay_ms(500);
		LCD_displayCharacter('*');
	}
}

/*
 * Description :
 * Function responsible for checking the input password with the one saved in the other micro-controller.
 */
uint8 checkPassWithControl(void)
{
	uint8 flag;
	uint8 pass[PASSWORD_SIZE +1 ];

	mcReady();

	UART_sendByte(3);

	HMI_enterPassDisplay();

	HMI_getAndDisplayPassword(pass);

	while( KEYPAD_getPressedKey() != ENTER );

	_delay_ms(500);

	pass[5] = '#';

	mcReady();

	UART_sendString(pass);

	while(UART_recieveByte() != MICRO_READY);

	UART_sendByte(MICRO_READY);

	flag = UART_recieveByte();

	return flag;
}

/*
 * Description :
 * Function responsible for doing what u need when the call-back function is called which is increasing the g_tick.
 */
void HMI_callBack(void)
{
	g_tick++;

}

/*
 * Description :
 * Function responsible for counting the number of trials u entered a wrong password.
 */
void changePasswordTrials(void)
{
	g_HMIcount ++;
	if ( g_HMIcount == 3)
	{
		HMI_passNotMatched();
	}
	else
	{
		HMI_changePassword();
	}
}

/*
 * Description :
 * Function responsible for counting the number of trials u entered a wrong password while opening the door.
 */
void openDoorTrials(void)
{
	g_HMIcount ++;
	if ( g_HMIcount == 3)
	{
		HMI_passNotMatched();
	}
	else
	{
		HMI_openDoor();
	}
}
