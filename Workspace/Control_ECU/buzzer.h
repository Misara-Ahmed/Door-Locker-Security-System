/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID                  PORTC_ID
#define BUZZER_PIN_ID                   PIN4_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Buzzer initializations
 */
void Buzzer_init();

/*
 * Description :
 * Enable the buzzer
 */
void Buzzer_on(void);

/*
 * Description :
 * Disable the buzzer
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
