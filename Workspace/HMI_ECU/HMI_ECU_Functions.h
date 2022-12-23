/******************************************************************************
 *
 * File Name: HMI_ECU_Functions.h
 *
 * Description: Header file for the HMI Functions
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/
#ifndef HMI_ECU_FUNCTIONS_H_
#define HMI_ECU_FUNCTIONS_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "lcd.h"
#include "std_types.h"
#include "common_macros.h"
#include "keypad.h"
#include "uart.h"
#include "timer1.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_SIZE     5
#define ENTER            '='
#define BAUD_RATE        9600
#define MICRO_READY      0x10
#define EQUAL            0x01
#define NOTEQUAL         0x00

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for making the user create the system password.
 */
void HMI_createSystemPassword(void);

/*
 * Description :
 * Function responsible for displaying the main system options that the user can do.
 */
void HMI_mainOptions(void);

/*
 * Description :
 * Function responsible for checking the password and if it is true it open the door.
 */
void HMI_openDoor(void);

/*
 * Description :
 * Function responsible for changing the system password.
 */
void HMI_changePassword(void);

/*
 * Description :
 * Function responsible for displaying error message on LCD for 1 minute then returning to the main options menu
 * when the password didn't match for 3 consecutive times.
 */
void HMI_passNotMatched(void);

/*
 * Description :
 * Function responsible for displaying the password entering messages.
 */
void HMI_enterPassDisplay(void);

/*
 * Description :
 * Function responsible for making sure that the micro-controller is ready to send or receive.
 */
void mcReady(void);

/*
 * Description :
 * Function responsible for taking the input password from the user and displaying * on the screen.
 */
void HMI_getAndDisplayPassword(uint8* password);

/*
 * Description :
 * Function responsible for checking the input password with the one saved in the other micro-controller.
 */
uint8 checkPassWithControl(void);


/*
 * Description :
 * Function responsible for doing what u need when the call-back function is called which is increasing the g_tick.
 */
void HMI_callBack(void);

/*
 * Description :
 * Function responsible for counting the number of trials u entered a wrong password.
 */
void changePasswordTrials(void);

/*
 * Description :
 * Function responsible for counting the number of trials u entered a wrong password while opening the door.
 */
void openDoorTrials(void);

#endif /* HMI_ECU_FUNCTIONS_H_ */
