/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the ATmega32 PWM driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to setup Timer0 to generate PWM signal for the motor.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
