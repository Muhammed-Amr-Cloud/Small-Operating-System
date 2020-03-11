/*
 * Scheduler.h
 *
 * Created: 11/24/2019 5:42:13 PM
 *  Author: Mohamed
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/*****************************************************************************************
 * 										INCLUDES										 *
 *****************************************************************************************/
#include "timer.h"
#include "Scheduler_Lcfg.h"


/*****************************************************************************************
 * 									Function Prototypes									 *
 *****************************************************************************************/


/*
	 * Function: Sos_Init.
	 *
	 * @definition: Inits the Small Os.
	 *
	 * @param	:void.
	 *
	 * @return: STATUS
	 *					OK : Successfully Initialized the timer.
	 * 				NOT OK : Timer didn't initialized successfully.
	 *
	 */
STATUS Sos_Init(void);


/*
* Function: Sos_Run.
*
* @definition: Starts the Small Os.
*
* @param	:void.
*
* @return: STATUS
*					OK : Successfully Initialized the timer.
* 				NOT OK : Timer didn't initialized successfully.
*
*/
void Sos_Run(void);

/*
	 * Function: Sos_Create_Task.
	 *
	 * @definition: Function to Create A task.
	 *
	 * @param	Name		: task_Periority  
	 *			Type        : uint8
	 *			DESC		: Determines the Task Periority.
	 *
	 * @param	Name		: task_Periodicity
	 *			Type        : uint16
	 *			DESC		: the time of calling the task Each time.
	 *
	 * @param	Name		: ptrTo_Task
	 *			Type        : pointer_ToFunciton_t
	 *			DESC		: A pointer to the function that will be executed.
	 *
	 @return: STATUS
	 *					OK : Successfully Initialized the timer.
	 * 				NOT OK : Timer didn't initialized successfully.
	 *
	 */

STATUS Sos_Create_Task(uint8 task_Periority, uint16 task_Periodicity ,pointer_ToFunciton_t ptrTo_Task);


/*
* Function: Sos_Delete_Task.
*
* @definition: Deletes a required Task
*
* @param	:void.
*
* @return: STATUS
*					OK : Successfully Initialized the timer.
* 				NOT OK : Timer didn't initialized successfully.
*
*/
STATUS Sos_Delete_Task(uint8 Task_Number);

















#endif /* SCHEDULER_H_ */