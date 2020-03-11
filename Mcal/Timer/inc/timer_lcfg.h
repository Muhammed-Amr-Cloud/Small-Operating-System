/*
 * timer_lcfg.h
 *
 *  Created on: Nov 4, 2019
 *      Author: Mohamed
 */

#ifndef TIMER_LCFG_H_
#define TIMER_LCFG_H_



/*****************************************************************************************
 * 									MACROS												 *
 *****************************************************************************************/



#define PIN_ZERO			(1<<0)
#define PIN_SEVEN			(1<<7)	
#define PIN_ONE				(1<<1)
#define OVF_TIMER			256
#define COUNT_PRESCALE			(1<<2) | (1<<1)
#define TIMER_PRESCALE			(1<<2) | (1<<0)
#define CLEARED						0


/*****************************************************************************************
 * 							ENUMS AND STRUCTURE DECLARATION								 *
 *****************************************************************************************/
typedef enum{

	TIMER_ZERO,
	TIMER_ONE,
	TIMER_TWO
}timer_Channel_Cfg_n;



/*
 * choosing the mode of the counter.
 *
 */
typedef enum{

	TIMER,
	COUNTER,
}timer_Mode_Cfg_n;


/*
 * Enabling or disabling the timer interrupt.
 *
 */

typedef enum{

	INTERRUPT_DISABLE,
	INTERRUPT_ENABLE
}timer_Interrupt_Cfg_n;



/*
 * Configuration Structure.
 *
 */

typedef struct{

timer_Channel_Cfg_n timer_Ch;

timer_Mode_Cfg_n timer_Mode;

unsigned short timer_count;

timer_Interrupt_Cfg_n timer_Interrupt;

unsigned long CPU_CLOCK;

}timer_Confguration_s;



/*
 * Externing Structure member values to use it in the including.
 *
 */

/*****************************************************************************************
 * 								STRUCTURE EXTERNING										 *
 *****************************************************************************************/

extern timer_Confguration_s timer_Zero_Cfg ;


#endif /* TIMER_LCFG_H_ */
