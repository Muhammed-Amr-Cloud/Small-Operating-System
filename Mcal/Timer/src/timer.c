/*
 * timer.c
 *
 *  Created on: Nov 4, 2019
 *      Author: Mohamed
 */

/*****************************************************************************************
 * 									INCLUDES											 *
 *****************************************************************************************/

#include "registers.h"
#include "std_types.h"
#include "timer.h"
#include "interrupt.h"

/*****************************************************************************************
 * 									USED MACROS											 *
 *****************************************************************************************/

#define POLLING          1
#define INTERRUPT        2

#define FOURTY_SIX       64
#define TIMER_0_OV       255
#define ONE_MILLI_DELAY  32

/*****************************************************************************************
 * 								GLOBAL VARIABLES 										 *
 *****************************************************************************************/
volatile uint8 g_Prescaler;
volatile uint8 g_Int_Flag = 0 ;
volatile uint8 g_Int_Polling = 0 ;
volatile uint16 g_count = 0 ;
volatile uint16 g_delay_ms = 0 ;
volatile uint8 g_tick = 0 ;
static volatile void (*g_ptr_Timer0_CallBack)(void);
volatile uint16 my_delay = 0 ;

volatile uint8 g_my_Count = 0 ;


/*****************************************************************************************
 * 								FUNCTION DEFINITION										 *
 *****************************************************************************************/

STATUS timer_Init(timer_Confguration_s* ptr_Timer_Cfg)
{

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
	if(ptr_Timer_Cfg == NULL)
	{
		return NOT_OK;
	}
	else
	{
		
	}

	if(ptr_Timer_Cfg->timer_Ch == TIMER_ZERO)
	{

		g_count = (ptr_Timer_Cfg->timer_count);

		TCCR0  = ( (TCCR0 & (0x7F)) | PIN_SEVEN);

		TCNT0 = 0 ;

		if(ptr_Timer_Cfg->timer_Interrupt == INTERRUPT_DISABLE)
		{

			g_Int_Polling = POLLING;

			if(ptr_Timer_Cfg->timer_Mode == COUNTER)
			{

				g_Prescaler = COUNT_PRESCALE;
			}

		else if (ptr_Timer_Cfg->timer_Mode == TIMER)
		{

			g_Prescaler = TIMER_PRESCALE ;
		}

		}


		else if (ptr_Timer_Cfg->timer_Interrupt == INTERRUPT_ENABLE)
		{

			SREG|= PIN_SEVEN;
			g_Int_Polling = INTERRUPT;
			TIMSK |= PIN_ZERO;

			if(ptr_Timer_Cfg->timer_Mode == COUNTER)
			{

				g_Prescaler = COUNT_PRESCALE;
			}

			else if (ptr_Timer_Cfg->timer_Mode == TIMER)
			{
				g_Prescaler =  TIMER_PRESCALE ;

			}
			else
			{
				
			}

		}

	}

	return OK;
}




void timer_Start(unsigned char ch_No)
{


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

//	if(ch_No == TIMER_ZERO)
	{

	TCCR0 =( TCCR0 & (0xF8) ) |  (1<<0) | (1<<1);
	}
}



void timer_Stop(unsigned char ch_No)
{

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
	if(ch_No == TIMER_ZERO)
	{

	TCCR0 = (TCCR0 & (0xF8) )  | g_Prescaler;
	}

}



unsigned char timer_Set_Count(unsigned char ch_No, unsigned char count)
{

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
	if(ch_No == TIMER_ZERO)
	{

		if(count < TIMER_0_OV )
		{
			g_my_Count = count ;
			TCNT0 = TIMER_0_OV - count;
		}
		else
		{
			return NOT_OK;
		}
	}

	return OK;
}



STATUS timer_Get_Status(unsigned char ch_No )
{
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


	if(ch_No == TIMER_ZERO)
	{
		if(g_Int_Polling == INTERRUPT)
		{

			if(g_Int_Flag == 1)
			{
				g_Int_Flag = CLEARED;
				return OK ;
			}
		}
		else if (g_Int_Polling == POLLING)
		{

			while(!(TIFR & PIN_ZERO));
			return OK;

		}
		else
		{
			
		}
	}

return NOT_OK;
}


#if 0
void timer_0_delay_ms(uint16 delay_ms)
{
	
	g_delay_ms = delay_ms;
	
	
}



void timer_OneInit(void)
{
	
	
	
}


#endif







void timer0_SetCallBAck(void (*ptrTo_Func) (void))
{
	
	g_ptr_Timer0_CallBack = ptrTo_Func ;
	
}


ISR(TIMER0_OVF_vect){
	
	TCNT0 = TIMER_0_OV -  g_my_Count;
	g_ptr_Timer0_CallBack();
	//TCNT0 = 249;
	
	//gpioPinDirection(PORTA,0xff,OUTPUT);
	//gpioPinToggle(PORTA,0xff);
	//
	
}