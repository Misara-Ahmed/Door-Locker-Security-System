/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the ATmega32 TIMER1 driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

#endif /* TIMER_H_ */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	NORMAL_MODE , CTC_MODE = 4
}Timer1_Mode;

typedef enum{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Timer1_Prescaler;


typedef struct {
uint16 initial_value;
uint16 compare_value;
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function to setup the initialization for Timer1.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to stop Timer1.
 */
void Timer1_deInit(void);

/*
 * Description :
 * Function to set the call back function of the Timer.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

