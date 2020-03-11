
#include "lcd.h"
#include "Dio.h"
#include "util/delay.h"



#define	SELECT_COLOM_ONE			0x40
#define SELECT_COLOM_TWO			0x10	
#define LAST_COLOM					0x50
#define CURSOR_BEGINNING			0x80
#define FIRST_HALF_MASK				0xF0
#define MASK_FIRST_BITS				0x0F
#define CURSOR_AT_BEGINNING			0x80
#define MOVE_CURSOR					0xC0
#define CLEAR_SCREEN				0x01
#define INIT_PORT					0xFF
#define INIT_CONTROL				0x33
#define FOUR_BIT_MDOE				0x28
#define CURSOR_OFF					0x0c
#define ENTRY_MODE					0x06
#define INIT_CONTROL_TWO			0x32

extern volatile uint8 init_Not_Done;


volatile uint8 init_Done	    = ZERO ;
volatile uint8 command_Done		= ZERO ;
volatile uint8 SEND_COMPLELETE  = ZERO ;
volatile uint8 SEND_COMPLELETE1 = ZERO ;
volatile  uint8 cursor_Flag		= ZERO ;

volatile uint8 string_COUNTer   = ZERO ;
volatile uint8 LCD_CLEARED      = ZERO ;


/**************************************************************************************/



typedef enum
{
	FIRST_HALF,
	RS_PIN_STATE,
	EN_PIN_STATE,
	SECOND_HALF,
	CHANGE_PIN
	
}Command_States;



/*
	 * Function: LCD_goToRowColumn.
	 *
	 * @definition: Go to A Specific Row and Colomn in the LCD.
	 *
	 * @param	Name		: row  
	 *			Type        : uint8
	 *			DESC		: Select the Specific Row.
	 *
	 * @param	Name		: col
	 *			Type        : uint8
	 *			DESC		: Select the Specific Colomn.
	 *
	 *
	 @return: void.
	 *					
	 */
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address = ZERO;
	
	switch(row)
	{
		case ZERO:
				Address=col;
				break;
		case ONE:
				Address=col+SELECT_COLOM_ONE;
				break;
		case TWO:
				Address=col+SELECT_COLOM_TWO;
				break;
		case THREE:
				Address=col+LAST_COLOM;
				break;
	}					
	
	
		LCD_sendCommand(Address | CURSOR_BEGINNING); 
		
	
}


/*
	 * Function: LCD_sendCommand.
	 *
	 * @definition:Send a rewuired comman to the LCD.
	 *
	 * @param	Name		: Command  
	 *			Type        : uint8
	 *			DESC		: Sending the command to the LCD.
	 *
	 *
	 @return: void.
	 *					
	 */

void LCD_sendCommand(uint8 command)
{
	static Command_States task_Count = FIRST_HALF;
	
	switch(task_Count)
	{
		
		case FIRST_HALF:	
				LCD_Port = (LCD_Port & MASK_FIRST_BITS) | (command & FIRST_HALF_MASK);
				task_Count++;
				break;
		
		case RS_PIN_STATE:
			LCD_Port &= ~ (ONE<<RS);
			task_Count++;
			break;
			
		
		case EN_PIN_STATE:
			LCD_Port |= (ONE<<EN);
			task_Count++;
			break;
		
		case SECOND_HALF:
			LCD_Port = (LCD_Port & MASK_FIRST_BITS) | (command << FOUR);
			task_Count++;
			break;
		
		case CHANGE_PIN:
			LCD_Port |= (ONE<<EN); 
			LCD_Port &= ~(ONE<<EN);
			task_Count++	    ;
			command_Done = ONE ;
			cursor_Flag = ONE  ; 
			break;
		
		
		default:
		task_Count = ZERO;
		break;
		
	}

}



/*
	 * Function: LCD_displayCharacter.
	 *
	 * @definition: Displays a Character on the LCD.
	 *
	 * @param	Name		: data  
	 *			Type        : uint8
	 *			DESC		: Sending the Character..
	 *
	 *
	 @return: void.
	 *					
	 */


void LCD_displayCharacter(uint8 data)
{
	static uint8 char_Count = ZERO ;
	switch(char_Count)
	{
		case ZERO :
		
			
			LCD_Port = (LCD_Port & MASK_FIRST_BITS) | (data & FIRST_HALF_MASK); 
			LCD_Port |= (ONE<<RS);				
			LCD_Port|= (ONE<<EN);
			char_Count++;
			break;
		case ONE:
			LCD_Port &= ~ (ONE<<EN);
			char_Count++;
			break;
		case TWO :
			LCD_Port = (LCD_Port & MASK_FIRST_BITS) | (data << FOUR);
			LCD_Port |= (ONE<<EN);
			char_Count++;
			break;
		case THREE :
			LCD_Port &= ~ (ONE<<EN);
			char_Count++;
			SEND_COMPLELETE  = ONE;
			SEND_COMPLELETE1 = ONE;
			cursor_Flag		 = ZERO;
			string_COUNTer++;
			break;
		
		default:
		char_Count = ZERO ;
		break;
		
		
	}
}

/*
	 * Function: LCD_displayString.
	 *
	 * @definition: Displays a String on the LCD.
	 *
	 * @param	Name		: Str  
	 *			Type        : uint8 *
	 *			DESC		: Sending an Array of Characters..
	 *
	 *
	 @return: void.
	 *					
	 */

void LCD_displayString(const uint8 *Str)			
{
	int i;
	for(i=ZERO ; Str[i]!='\0' ;i++)				
	{
		LCD_displayCharacter (Str[i]);
	}
}

/*
	 * Function: LCD_displayStringRowColumn.
	 *
	 * @definition: Function to Create A task.
	 *
	 * @param	Name		: row  
	 *			Type        : uint8
	 *			DESC		: Determines the required Row.
	 *
	 * @param	Name		: col
	 *			Type        : uint8
	 *			DESC		: Determines the required Col.
	 *
	 * @param	Name		: Str
	 *			Type        : uint8*
	 *			DESC		: Sending An Array of Characters.
	 *
	 @return: void
	 *
	 */


void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 *Str)
{		
	if (row == ZERO && col<16)
	{
		LCD_sendCommand((col & MASK_FIRST_BITS)|CURSOR_AT_BEGINNING);			
	}
	
	else if (row == ONE && col<16)
	{
		LCD_sendCommand((col & MASK_FIRST_BITS)|MOVE_CURSOR);
	}
	
	LCD_displayString(Str);			
		
}


/*
	 * Function: LCD_intgerToString.
	 *
	 * @definition: Displays a String on the LCD.
	 *
	 * @param	Name		: data  
	 *			Type        : uint16 
	 *			DESC		: displays an integer as a string.
	 *
	 *
	 @return: void.
	 *					
	 */

void LCD_intgerToString(uint16 data)
{
	char buff[FIVE]; 
	itoa(data,buff,TEN);
	LCD_displayString(buff);
}

/*
	 * Function: LCD_init.
	 *
	 * @definition:Initialize the LCD.
	 *
	 * @param:void
	 *
	 *
	 * @return: void.
	 *					
	 */
void LCD_init(void)
{
	static uint8 LCD_Init_State = ZERO;
								
	switch(LCD_Init_State)
	{
		
		case ZERO:
			LCD_Dir = INIT_PORT;
			LCD_Init_State++;	
		break;
		case ONE:
		LCD_sendCommand(INIT_CONTROL);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		
		break;
		case TWO:
		LCD_sendCommand(INIT_CONTROL_TWO);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		break;
		case THREE:
		LCD_sendCommand(FOUR_BIT_MDOE);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		break;
		case FOUR:
		LCD_sendCommand(CURSOR_OFF);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		break;
		case FIVE:
		LCD_sendCommand(ENTRY_MODE);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		break;
		case SIX:
		LCD_sendCommand(CLEAR_SCREEN);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		break;
		case SEVEN:
		LCD_sendCommand(CURSOR_AT_BEGINNING);
		if(command_Done == ONE)
		{
			LCD_Init_State++;
			command_Done = ZERO;
		}
		init_Done = ONE;
		init_Not_Done = ONE ;
		break;
		
		default:
		break;
		
	}					



}

/*
	 * Function: LCD_clearScreen.
	 *
	 * @definition: Clear the Screen.
	 *
	 * @param:void
	 *
	 *
	 * @return: void.
	 *					
	 */

void LCD_clearScreen(void)
{	
	static uint8 step = ZERO ;
	
	switch(step)
	{
		case ZERO:
			LCD_sendCommand (CLEAR_SCREEN);
			if(command_Done == ONE)
			{
			step++;
			command_Done = ZERO ;
			}
			break;
		case ONE :
		
			LCD_sendCommand (CURSOR_AT_BEGINNING);
			if(command_Done == ONE)
			{
				step++;
				command_Done = ZERO;
			}
			break;
		
		default:
			LCD_CLEARED = ONE ;
			step = ZERO ;
			break;	
	}
	
}