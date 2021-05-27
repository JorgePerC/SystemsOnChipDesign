
#include <MKL25Z4.h>

/*
 *******************************************************************************
 *                              Los separatistas                               *
 *																																						 *
 * File to configure 16x2 LCD Display on the Freedom Development board 				 *
 * FRCM-KL25Z.																													 			 *
 * --------------------------------------------------------------------------- *
 * Pin D0 -> PTD0																															 *
 * Pin D1 -> PTD1																															 *
 * Pin D2 -> PTD2																															 *
 * ...																																				 *
 * Pin RS  -> PTA2																															 *
 * Pin R/W -> PTA4																															 *
 * Pin E   -> PTA5																															 *
 * --------------------------------------------------------------------------- *
 * Created: 14/05/2021																												 *
 *******************************************************************************
*/

// Display Commands

#define DCommd_ClearDisplay			0x01
#define DCommd_CursorHome				0x02
#define DCommd_IncrementCursor	0x06
#define DCommd_CursorBlink			0x0F
#define DCommd_CursorFirstLine	0x80
#define DCommd_CursorSecondLine	0xC0
#define DCommd_8bits						0x38
#define DCommd_4bits						0x28


/*
 *******************************************************************************
 *                              Register Symbols                               *
 *******************************************************************************
*/

#define RS 0x04 /* PTA2 mask */
#define RW 0x10 /* PTA4 mask */
#define EN 0x20 /* PTA5 mask */

#define BF 0xff			/*LCD Busy mask TODO: check */

#define LCD_DISPLAY_I2C_ADDRESS 0x3F


/*
 *******************************************************************************
 *                              Type Definitions                               *
 *******************************************************************************
*/


/*
 *******************************************************************************
 *                        General Function Declarations                        *
 *******************************************************************************
*/

void LCD_init(unsigned char bitSelection);


void LCD_command(unsigned char command);

void LCD_data(unsigned char data);

void sendWord(char *word);

void waitUntilFinished(void);
