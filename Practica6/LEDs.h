
#include <MKL25Z4.h>

/*
 *******************************************************************************
 *                              Los separatistas                               *
 *																																						 *
 * File to configure and control LEDs on the Freedom Development board 				 *
 * FRDM-KL25Z.																													 			 *
 * --------------------------------------------------------------------------- *
 * Created: 14/05/2021																												 *
 *******************************************************************************
*/

/*
 *******************************************************************************
 *                              Register Symbols                               *
 *******************************************************************************
*/

#define R_LED 0x40000
#define G_LED 0x80000
#define B_LED 0x02

/*
 *******************************************************************************
 *                        General Function Declarations                        *
 *******************************************************************************
*/

void LED_set(int value);
void init_RED_LED (void);
void init_GREEN_LED (void);
void init_BLUE_LED (void);
void toggle_LED (uint32_t desired);
void toggle_Blue_LED (void);
void turn_off_all_LEDs(void);