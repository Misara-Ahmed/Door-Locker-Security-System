/******************************************************************************
 *
 * File Name: CONTROL_ECU_Functions.h
 *
 * Description: Header file for the CONTROL Functions
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#ifndef CONTROL_ECU_FUNCTIONS_H_
#define CONTROL_ECU_FUNCTIONS_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "common_macros.h"
#include "std_types.h"
#include "external_eeprom.h"
#include "timer1.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_SIZE     5
#define BAUD_RATE         9600
#define MICRO_READY       0x10
#define PASS_NOT_EQUAL     0
#define PASS_EQUAL         1

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for checking the two passwords which the user enters on startup.
 */
void CONTROL_checkPassword(void);

/*
 * Description :
 * Function responsible for saving the password in the eeprom.
 */
void CONTROL_savePassword(uint8 * pass);

/*
 * Description :
 * Function responsible for checking the entered password with the one saved in the eeprom.
 */
uint8 CONTROL_eepromCheckPassword(void);

/*
 * Description :
 * Function responsible for changing the saved password in the eeprom.
 */
void CONTROL_changePassword(void);

/*
 * Description :
 * Function responsible for making sure that the micro-controller is ready to send or receive.
 */
void mcReady(void);

/*
 * Description :
 * Function responsible for :
 * 1- Rotating the motor for 15-seconds CW and display a message on the screen “Door is Unlocking”.
 * 2- Holding the motor for 3-seconds.
 * 3- Rotating motor for 15-seconds A-CW and display a message on the screen “Door is Locking”.
 */
void CONTROL_rotateMotor(void);

/*
 * Description :
 * The call back function of the Timer, responsible for increasing the number of g_tick.
 */
void CONTROL_callBack(void);

/*
 * Description :
 * When the passwords don't match for 3 successive times it will take action.
 * Function responsible for :
 * 1- Activating Buzzer for 1-minute.
 * 2- System should be locked no inputs from Keypad will be accepted during this time period.
 */
void CONTROL_passNotMatched(void);

#endif /* CONTROL_ECU_FUNCTIONS_H_ */
