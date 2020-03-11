/*
 * Push_Button.h
 *
 * Created: 11/26/2019 10:57:13 AM
 *  Author: Mohamed
 */ 


#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

/*****************************************************************************************
 * 										INCLUDEs										 *
 *****************************************************************************************/

#include "std_types.h"

/*****************************************************************************************
 * 											MACROS										 *
 *****************************************************************************************/


#define BUTTON_0	4
#define BUTTON_1	2


/*****************************************************************************************
 * 									Function Prototypes									 *
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
void Ave_button_init(uint8 button);

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
STATUS Ave_button_read(uint8 button);



#endif /* PUSH_BUTTON_H_ */