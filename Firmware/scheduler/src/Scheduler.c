/*
 * Scheduler.c
 *
 * Created: 11/24/2019 5:42:26 PM
 *  Author: Mohamed
 */ 

/*****************************************************************************************
 * 										INCLUDES										 *
 *****************************************************************************************/
#include "Scheduler.h"
#include "timer.h"
#include "lcd.h"
#include "Push_Button.h"


/*****************************************************************************************
 * 								Local Functions Prototypes								 *
 *****************************************************************************************/

static void next_Task_Ready(void);




/*****************************************************************************************
 * 								Global Variables										 *
 *****************************************************************************************/

static volatile uint8 g_Tick_Flag              ;
static volatile uint8 g_Generated_Task_Number  ;
static volatile uint8 g_Generated_Task_ID	   ;




volatile uint8 Start_Exectute	 = ZERO;
volatile uint8 button_PUSH		= START_CHAR ;
volatile uint8  pinflag			= ZERO ;
volatile uint8 init_Not_Done	= ZERO ;
volatile uint8 init_Is_Done		= ZERO;


extern volatile uint8 init_Done;
extern volatile uint8 SEND_COMPLELETE ;
extern volatile  uint8 cursor_Flag ;
extern volatile uint8 LCD_CLEARED  ;
extern volatile uint8 string_COUNTer ;




/*****************************************************************************************
 * 							Local Structure	 and Enums									 *
 *****************************************************************************************/

typedef enum
{
	READY,
	WAITING,
	IDLE
	
}Sos_Task_State_t;


typedef struct
{	uint16			 Count			 ;
	uint8			 ID			     ;
	uint16			 Periodicity	 ;
	Sos_Task_State_t State			 ;
	uint8			 Periority		 ;
	void(*ptrToFunction_Task)(void)  ;
}task_t;


static task_t Task[MAX_NUM_OF_TASKS] ;



/*****************************************************************************************
 * 							Local Function Implementation								 *
 *****************************************************************************************/



static void next_Task_Ready(void)
{
	g_Generated_Task_Number++ ;
	g_Generated_Task_ID++	  ;
}





/*****************************************************************************************
 * 								Function Implementation									 *
 *****************************************************************************************/


/*
	 * Function: Timer_Ticks_Detect.
	 *
	 * @definition: The function the the timer will call that detects the ticks.
	 *
	 * @param : void
	 *
	 * @return: void.
	 *
	 */
void Timer_Ticks_Detect (void)
{
	
	g_Tick_Flag = ONE;
}





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


STATUS Sos_Create_Task(uint8 task_Periority, uint16 task_Periodicity ,pointer_ToFunciton_t ptrTo_Task)
{
	uint8 status = OK;
	
	if(ptrTo_Task == NULL || task_Periodicity <= ZERO)
	{
		status = NOT_OK ;
	}
	else
	{	
		Task[g_Generated_Task_Number].Count              =     ZERO             ;
		Task[g_Generated_Task_Number].Periodicity		 = task_Periodicity		;
		Task[g_Generated_Task_Number].Periority			 = task_Periority		;
		Task[g_Generated_Task_Number].ptrToFunction_Task = ptrTo_Task			;
		Task[g_Generated_Task_Number].ID				 = g_Generated_Task_ID  ;
		Task[g_Generated_Task_Number].State				 = READY				;
		next_Task_Ready();
	}
	 
	return status ;
}


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

STATUS Sos_Init(void)
{
	g_Tick_Flag				= ZERO ;
	g_Generated_Task_Number = ZERO ;
	g_Generated_Task_ID		= ZERO ;
	
	timer_Init(&timer_Zero_Cfg);
	timer_Set_Count(TIMER_ZERO, RESOLUTION);
	timer0_SetCallBAck(Timer_Ticks_Detect);
	
	return OK;
}



#if 0

static void check_Highest_Periority (void)
{
	uint8 count_Task ;
	
	
	for(count_Task = ZERO ; count_Task < g_Generated_Task_Number ; count_Task++)
	{
		//if( highest_Periority < Task[count_Task].Periority)
		//{
			//highest_Periority = Task[count_Task].Periority ;
		//}
		//
		
	}
	
	
}

#endif

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

void Sos_Run(void)
{
	/*my Dispatcher.
	*/	
	uint8 task_Count  ;
	uint8 highest_Periority			   = Task[g_Generated_Task_Number].Periority ;
	uint8 Task_Highest_Periority_Index = ZERO;
	timer_Start(TIMER_ZERO);
	while(1)
	{
		
		if(g_Tick_Flag == ONE) // Each Tick.
		{
			g_Tick_Flag = ZERO ;	
			
			for(task_Count = 0 ; task_Count < g_Generated_Task_Number ; task_Count++)
			{
								if(Task[task_Count].State == WAITING)
								{	
									
									Task[task_Count].Count++ ;
									
									if(((Task[task_Count].Count) % (Task[task_Count].Periodicity)) == ZERO )
									{	
										/*DEBUG!
										gpioPinToggle(PORTC,0x08);
										*/
										Task[task_Count].Count = ZERO ; 
										Task[task_Count].State = READY ;
									}
									else
									{
										
									}
									
								}
								
								
								else if (Task[task_Count].State == READY)
								{
									for(int Selected_Arr_Count = ZERO ; Selected_Arr_Count <g_Generated_Task_Number ; Selected_Arr_Count++)
									{
										if(Task[Selected_Arr_Count].State == READY)
										{
											if(highest_Periority <= Task[Selected_Arr_Count].Periority)
											{
												highest_Periority = Task[Selected_Arr_Count].Periority ;
												Task_Highest_Periority_Index = Selected_Arr_Count;
											}
											
											
										}
										
									}
									
									Task[Task_Highest_Periority_Index].ptrToFunction_Task();
									Task[Task_Highest_Periority_Index].State = WAITING     ;	
																	
								}
								else if (Task[task_Count].State == IDLE)
								{
									Task[task_Count].State == IDLE;
								}
				
			}
		
			highest_Periority = Task[g_Generated_Task_Number].Periority ;
		}
		
		
	}
	
		
}

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
STATUS Sos_Delete_Task(uint8 Task_Number)
{
	uint8 status = OK ;
	task_t temp_Storage ;
	
	if(g_Generated_Task_Number < ONE)
	{
		status = NOT_OK ;
	}
	else
	{
		Task[Task_Number].State = IDLE;
		temp_Storage = Task[Task_Number]				  ;
		Task[Task_Number] = Task[g_Generated_Task_Number] ;
		Task[g_Generated_Task_Number] = temp_Storage	  ;
		g_Generated_Task_Number--;
		g_Generated_Task_ID--;
		
	}
	
	
	return status ;
}


#if 0

//Task[Task_Number].Count     ^= Task[g_Generated_Task_Number].Count	  ;
//Task[g_Generated_Task_Number].Count ^= Task[Task_Number].Count		  ;
//Task[Task_Number].Count        ^= Task[g_Generated_Task_Number].Count ;
//
//Task[Task_Number].Count     ^= Task[g_Generated_Task_Number].Count	  ;
//Task[g_Generated_Task_Number].Count ^= Task[Task_Number].Count		  ;
//Task[Task_Number].Count        ^= Task[g_Generated_Task_Number].Count ;
//
//Task[Task_Number].Count     ^= Task[g_Generated_Task_Number].Count	  ;
//Task[g_Generated_Task_Number].Count ^= Task[Task_Number].Count		  ;
//Task[Task_Number].Count        ^= Task[g_Generated_Task_Number].Count ;
//
//Task[Task_Number].Count     ^= Task[g_Generated_Task_Number].Count	  ;
//Task[g_Generated_Task_Number].Count ^= Task[Task_Number].Count		  ;
//Task[Task_Number].Count        ^= Task[g_Generated_Task_Number].Count ;
//
//Task[Task_Number].Count     ^= Task[g_Generated_Task_Number].Count	  ;
//Task[g_Generated_Task_Number].Count ^= Task[Task_Number].Count		  ;
//Task[Task_Number].Count        ^= Task[g_Generated_Task_Number].Count ;


if(g_Tick_Flag == 1)
{																		//each tick do something
	for(task_Count = 0 ; task_Count < g_Generated_Task_Number ; task_Count++)
	{
		
		check_Highest_Periority();
		// check if the task is in running state or not
		if(Task[task_Count].Periority <= highest_Periority)
		{
			Periodicity = Task[task_Count].Periodicity;
			Task[task_Count].Periodicity--     ;
			
			if(Task[task_Count].Periodicity == ZERO)
			{
				Task[task_Count].ptrToFunction_Task() ;
				Task[task_Count].Periodicity = Periodicity; // need to return the Periodicity to its initial value.
			}
			
		}
		
		
		
		
		
	}
	
	
	
	g_Tick_Flag = ZERO ;
	
}




#endif


/*****************************************************************************************
 * 									OS Tasks											 *
 *****************************************************************************************/


STATUS Sos_Task_NIGNTY_ms(void)
{
		
		static uint8 task_Counter = ZERO ;
		
		if (Ave_button_read(BUTTON_0))
		{
			button_PUSH++;
		}
		if (Ave_button_read(BUTTON_1))
		{
			button_PUSH--;
		}
		
		switch(task_Counter)
		{
			case ZERO :
			LCD_displayCharacter(button_PUSH);
			
			if(SEND_COMPLELETE == ONE)
			{
				task_Counter++;
				SEND_COMPLELETE = ZERO ;
			}
			
			break;
			
			case ONE:
			LCD_clearScreen();
			
			if(LCD_CLEARED == ONE)
			{
				task_Counter++;
				LCD_CLEARED = ZERO ;
			}
			
			break;
			case 2 :
			task_Counter = ZERO ;
			break;
			
			default :
			break;
		}
		
	return OK;
}



void SoS_Init_Tasks(void)
{
	
	
	static uint8 Init_Task_State = ZERO;
	switch(Init_Task_State)
	{
		case ZERO :
			Ave_button_init(BUTTON_0);
			Init_Task_State++;
		
		break;
		
		case ONE :
		LCD_init();
		
		if(init_Not_Done == ONE)
		{
			Init_Task_State++;
			
		}
		break;
		
		default:
		init_Is_Done = ONE ;
		
		break;
	}
	
	if(init_Is_Done == ONE)
	{
		Sos_Delete_Task(ZERO);
		
		
	}
	
	
}