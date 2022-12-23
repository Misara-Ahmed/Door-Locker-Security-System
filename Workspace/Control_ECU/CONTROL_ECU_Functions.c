/******************************************************************************
 *
 * File Name: CONTROL_ECU_Functions.c
 *
 * Description: Source file for the CONTROL Functions
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "external_eeprom.h"
#include <util/delay.h>
#include "CONTROL_ECU_Functions.h"

/*******************************************************************************
 *                              Variables                                      *
 *******************************************************************************/
uint8 g_PASSWORD[PASSWORD_SIZE + 1];
uint8 g_tick = 0;
Timer1_ConfigType timerConfig = { 0 , 7800 , F_CPU_1024 , CTC_MODE};

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for checking the two passwords which the user enters on startup.
 */
void CONTROL_checkPassword(void)
{
	uint8 check_pass = 1;
	uint8 FIRST_PASS[PASSWORD_SIZE + 1];
	uint8 SECOND_PASS[PASSWORD_SIZE + 1];

	mcReady();

	UART_receiveString(FIRST_PASS);

	UART_sendByte(MICRO_READY);

	UART_receiveString(SECOND_PASS);

	for (int i = 0 ; i < PASSWORD_SIZE ; i++)
	{
		if(FIRST_PASS[i] != SECOND_PASS[i])
		{
			check_pass = 0;
			break;
		}
	}

	if ( check_pass )
	{
		CONTROL_savePassword(FIRST_PASS);
	}

	UART_sendByte(MICRO_READY);

	UART_sendByte(check_pass);


}

/*
 * Description :
 * Function responsible for saving the password in the eeprom.
 */
void CONTROL_savePassword(uint8 * pass)
{
	for (int i = 0; i < PASSWORD_SIZE; i++ )
	{
		EEPROM_writeByte(0X031+i, pass[i]);
		_delay_ms(200);
	}
}

/*
 * Description :
 * Function responsible for checking the entered password with the one saved in the eeprom.
 */
uint8 CONTROL_eepromCheckPassword(void)
{
	uint8 data;

	uint8 flag = 0;

	/* Read from the external EEPROM */
	for (int i = 0 ; i < PASSWORD_SIZE ; i++ )
	{
		EEPROM_readByte(0X031+i, &data);
		if (g_PASSWORD[i] != data)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

/*
 * Description :
 * Function responsible for changing the saved password in the eeprom.
 */
void CONTROL_changePassword(void)
{
	uint8 CONTROL_flag = 0;

	mcReady();

	UART_receiveString(g_PASSWORD);

	CONTROL_flag = CONTROL_eepromCheckPassword();

	UART_sendByte(MICRO_READY);

	while(UART_recieveByte() != MICRO_READY);

	UART_sendByte(CONTROL_flag);

}

/*
 * Description :
 * Function responsible for making sure that the micro-controller is ready to send or receive.
 */
void mcReady(void)
{
	while(UART_recieveByte() != MICRO_READY);

	UART_sendByte(MICRO_READY);

}

/*
 * Description :
 * Function responsible for :
 * 1- Rotating the motor for 15-seconds CW and display a message on the screen “Door is Unlocking”.
 * 2- Holding the motor for 3-seconds.
 * 3- Rotating motor for 15-seconds A-CW and display a message on the screen “Door is Locking”.
 */
void CONTROL_rotateMotor(void)
{

	Timer1_setCallBack(CONTROL_callBack);

	DcMotor_init();

	Rotate_CW();

	Timer1_init(&timerConfig);

	while(g_tick < 15);

	DcMotor_Stop();

	while(g_tick < 18);

	Rotate_ACW();

	while(g_tick < 33);

	DcMotor_init();

	g_tick = 0;

	Timer1_deInit();
}

/*
 * Description :
 * When the passwords don't match for 3 successive times it will take action.
 * Function responsible for :
 * 1- Activating Buzzer for 1-minute.
 * 2- System should be locked no inputs from Keypad will be accepted during this time period.
 */
void CONTROL_passNotMatched(void)
{
	Timer1_setCallBack(CONTROL_callBack);

	Timer1_init(&timerConfig);

	Buzzer_init();

	Buzzer_on();

	while(g_tick < 60);

	Buzzer_off();
}

/*
 * Description :
 * The call back function of the Timer, responsible for increasing the number of g_tick.
 */
void CONTROL_callBack(void)
{
	g_tick++;
}
