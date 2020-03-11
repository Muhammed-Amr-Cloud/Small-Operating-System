/*
 * Push_Button.c
 *
 * Created: 11/26/2019 10:57:55 AM
 *  Author: Mohamed
 */ 


/*****************************************************************************************
 * 										INCLIDES										 *
 *****************************************************************************************/


#include "Push_Button.h"
#include "Dio.h"

/*****************************************************************************************
 * 										USED MACROS										 *
 *****************************************************************************************/

#define BUTTON_DEBOUNCE				15


/*****************************************************************************************
 * 									Function Definition									 *
 *****************************************************************************************/


/*
	 * Function: Ave_button_init.
	 *
	 * @definition: Init the button
	 *
	 * @param	Name		: button  
	 *			Type        : uint8
	 *			DESC		: Initialize a required Button.
	 *
	 @return: void.
	 *					
	 */
void Ave_button_init(uint8 button){
	
	
	switch (button)
	{
		case BUTTON_0 :
		gpioPinDirection(PORTC,(ONE<<BUTTON_0),INPUT);
		break;
		
		case BUTTON_1 :
		gpioPinDirection(PORTB,(ONE<<BUTTON_1),INPUT);
		break;
		
		default:
		break;
		
	}
	
}

/*
	 * Function: Ave_button_read.
	 *
	 * @definition: Status of the Button.
	 *
	 * @param	:Name: button.
	 *			Type: uint8.
	*			DESC: REturns the status of the button.
	 *
	 * @return: STATUS
	 *					OK : Successfully Initialized the timer.
	 * 				NOT OK : Timer didn't initialized successfully.
	 *
	 */




uint8 Ave_button_read(uint8 button){
	
	static uint8 button_Counts	 = ZERO ; 
	static uint8 button_Counts2  = ZERO ; 
	static uint8 button_Flag	 = ZERO ;
	switch (button)
	{
	
		case BUTTON_0 :
		if(gpioPinRead(PORTC,BUTTON_0))
		{		
			button_Counts++;
			
			if(gpioPinRead(PORTC,BUTTON_0) && button_Counts ==BUTTON_DEBOUNCE)
			{
				button_Counts = ZERO;		
				if(button_Flag == ZERO )
				{
					return ONE ; 
					button_Flag = ONE ;
				}
			}
			else
			{
				button_Flag = ZERO ;
			}
		}
		return ZERO ;
		break;
		
		case BUTTON_1 :
		if(gpioPinRead(PORTB,BUTTON_1))
		{
			button_Counts2++;
			
			if(gpioPinRead(PORTB,BUTTON_1) && button_Counts2 ==BUTTON_DEBOUNCE)
			{
				button_Counts2 = ZERO ;
				return ONE ;
			}
		}
		return ZERO;
		break;
		
		default:
		return ZERO;
		
		
	}
}

