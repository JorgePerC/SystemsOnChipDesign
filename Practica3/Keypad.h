
#include <MKL25Z4.h>

/*
 *******************************************************************************
 *                              Los separatistas                               *
 *																																						 *
 * File to configure 16x2 LCD Display on the Freedom Development board 				 *
 * FRCM-KL25Z.																													 			 *
 * --------------------------------------------------------------------------- *
 * Pin 1 -> PTC0																															 *
 * Pin 2 -> PTC1																															 *
 * ...																																				 *
 * Pin 7 -> PTC6																															 *
 * Pin 8 -> PTC7																															 *
 * --------------------------------------------------------------------------- *
 * Created: 14/05/2021																												 *
 *******************************************************************************
*/

/*
 *******************************************************************************
 *                              Register Symbols                               *
 *******************************************************************************
*/

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

void keypad_init(void);
unsigned int keypad_getkey(void);