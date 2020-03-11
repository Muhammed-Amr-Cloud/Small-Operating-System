/*
 * Small_OS.c
 *
 * Created: 11/24/2019 5:14:37 PM
 * Author : Mohamed
 */ 



#include "timer.h"
#include "lcd.h"
#include "Push_Button.h"
#include "util/delay.h"
#include "Scheduler.h"






void task_Execute (void)
{
	
	
	Sos_Task_NIGNTY_ms();

}


void task_Init(void)
{
	SoS_Init_Tasks();
	
}







#if 0 

void toggle_LED_TWO(void)
{
	
	
}

#endif


int main(void)
{	
	Sos_Init();
	Sos_Create_Task(1,1,task_Execute);
	Sos_Create_Task(3,5,task_Init);
	
	
	Sos_Run();
}

