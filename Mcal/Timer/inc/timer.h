/*
 * timer.h
 *
 *  Created on: Nov 4, 2019
 *      Author: Mohamed
 */

#ifndef TIMER_H_
#define TIMER_H_


/*****************************************************************************************
 * 										INCLUDES										 *
 *****************************************************************************************/

#include "timer_lcfg.h"
#include "std_types.h"
#include "Dio.h"


/*****************************************************************************************
 * 									Function Prototypes.								 *
 *****************************************************************************************/

/*
 * Function: timer_Init.
 *
 *@definition:	The function is meant to Initialize the timer - Timer0 or Timer1 or Timer2, while choosing its mode
 *	as a timer or a counter. Ability to choose the interrupts or Polling
 *
 * @param IN: ptr_Timer_Cfg: Is a Pointer to Structure of the Timer Configuration.
 *
 @return: STATUS
 *					OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */

STATUS timer_Init(timer_Confguration_s* ptr_Timer_Cfg);



/*
 * Function: timer_Start.
 *
 * @definition: The function Starts a specific timer.
 *
 * @param ch_No: Choosing between timer0 or timer1 or timer2, 0-> timer0   1-> timer1  2->timer2
 *
 * @return: void.
 *
 */


void timer_Start(unsigned char ch_No);


/*
 * Function: timer_Stop.
 *
 * @definition: Function to Stop a Specific timer.
 *
 * @param: ch_No :  Choosing between timer0 or timer1 or timer2, 0-> timer0   1-> timer1  2->timer2
 *
 * @return: void.
 *
 */

void timer_Stop(unsigned char ch_No);


/*
 * Function: timer_Set_Counter.
 *
 * @definition: Chossing the timer that will give a required delay
 *
 * @param ch_No:  Choosing between timer0 or timer1 or timer2, 0-> timer0   1-> timer1  2->timer2.
 *
 * @param count: required delay in MilliSeconds
 *
 * @return: void.
 *
 */


void timer_Set_Counter(unsigned char ch_No, unsigned short count);


/*
 * Function: timer_Get_Status.
 *
 * @definition: the function return the status of the time
 *
 *@param ch_No :  Choosing between timer0 or timer1 or timer2, 0-> timer0   1-> timer1  2->timer2
 *
 *@param @return: STATUS
 *
 * 				OK : Successfully Initialized the timer.
 * 				NOT OK : Timer didn't initialized successfully.
 */


STATUS timer_Get_Status(unsigned char ch_No );


void timer_0_delay_ms(uint16 delay_ms);


void timer0_SetCallBAck(void (*ptr_Func)(void));



unsigned char timer_Set_Count(unsigned char ch_No, unsigned char count);

void timer_OneInit(void);

void timer_OneStart(void);










#endif /* TIMER_H_ */
