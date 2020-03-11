
/*
 * lcd.h
 *
 * Created: 11/26/2019 5:42:13 PM
 *  Author: Mohamed
 */ 
#ifndef LCD_H_
#define LCD_H_

#include "registers.h"
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define LCD_Dir			PORTA_DIR					
#define LCD_Port		PORTA_DATA				
#define RS 1							
#define EN 3

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/


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

void LCD_goToRowColumn(uint8 row,uint8 col);
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
void LCD_sendCommand(uint8 command);
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

void LCD_displayCharacter(uint8 data);
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
void LCD_displayString(const uint8 *Str);
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
void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8* Str);
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
void LCD_intgerToString(uint16 data);

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

void LCD_init(void);
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
void LCD_clearScreen(void);

#endif /* LCD_H_ */
