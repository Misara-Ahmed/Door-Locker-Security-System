/******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the ATmega32 DC MOTOR driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "dc_motor.h"

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins and Stop the DC-Motor at the beginning.
 */
void DcMotor_init(void)
{
	/*
	 * configuring the dc motor pins to be output pins.
	 */
	GPIO_setupPinDirection(DC_FIRSTPIN_PORT,DC_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_SECONDPIN_PORT,DC_SECOND_PIN,PIN_OUTPUT);

	/*
	 * stopping the dc motor at the beginning.
	 */
	GPIO_writePin(DC_ENABLE_PORT, DC_ENABLE_PIN, LOGIC_LOW);

}

/*
 * Description :
 * Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Function responsible for sending the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_rotate(DcMotor_State state,uint8 speed)
{
	/*
	 * Configuring the states of the motor.
	 */
	switch (state)
	{
	case STOP :
		/*
		 * Stopping the motor by clearing both pins of it.
		 */
		GPIO_writePin(DC_FIRSTPIN_PORT, DC_FIRST_PIN, LOGIC_LOW);
		GPIO_writePin(DC_SECONDPIN_PORT, DC_SECOND_PIN, LOGIC_LOW);
		break;

	case CW :
		/*
		 * Configuring the motor to rotate clockwise by clearing the first pin and setting the second pin.
		 */
		GPIO_writePin(DC_FIRSTPIN_PORT, DC_FIRST_PIN, LOGIC_LOW);
		GPIO_writePin(DC_SECONDPIN_PORT, DC_SECOND_PIN, LOGIC_HIGH);
		break;

	case ACW :
		/*
		 * Configuring the motor to rotate anti-clockwise by setting the first pin and clearing the second pin.
		 */
		GPIO_writePin(DC_FIRSTPIN_PORT, DC_FIRST_PIN, LOGIC_HIGH);
		GPIO_writePin(DC_SECONDPIN_PORT, DC_SECOND_PIN, LOGIC_LOW);
		break;
	}

	/*
	 * starting the motor with the required speed.
	 */
	PWM_Timer0_Start(speed);
}

void Rotate_CW(void)
{
	DcMotor_rotate( CW , 100);
}

void Rotate_ACW(void)
{
	DcMotor_rotate( ACW , 100);
}

void DcMotor_Stop(void)
{
	DcMotor_rotate( ACW , 0);

}
