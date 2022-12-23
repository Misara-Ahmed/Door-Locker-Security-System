/******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the ATmega32 DC MOTOR driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_FIRSTPIN_PORT    PORTA_ID
#define DC_SECONDPIN_PORT   PORTA_ID
#define DC_ENABLE_PORT      PORTA_ID

#define DC_FIRST_PIN        PIN0_ID
#define DC_SECOND_PIN       PIN1_ID
#define DC_ENABLE_PIN       PIN2_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/*
 * Description :
 * Enum for the dc motor different states.
 */
typedef enum
{
	STOP,CW,ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins and Stop the DC-Motor at the beginning.
 */
void DcMotor_init(void);

/*
 * Description :
 * Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Function responsible for sending the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_rotate(DcMotor_State state,uint8 speed);

void Rotate_CW(void);

void Rotate_ACW(void);

void DcMotor_Stop(void);

#endif /* DC_MOTOR_H_ */
