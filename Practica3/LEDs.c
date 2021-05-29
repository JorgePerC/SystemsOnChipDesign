#include "LEDs.h"

/* turn on or off the LEDs wrt to bit 2-0 of the value */
void LED_set(int value){
	/* use bit 0 of value to control red LED */

	if (value & 1)
		PTB->PCOR = 0x40000; /* turn on red LED */
	else 
		PTB->PSOR = 0x40000; /* turn off red LED */
	/* use bit 1 of value to control green LED */
	if (value & 2)
		PTB->PCOR = 0x80000; /* turn on green LED */
	else 
		PTB->PSOR = 0x80000; /* turn off green LED */
	/* use bit 2 of value to control blue LED */
	if (value & 4) 
		PTD->PCOR = 0x02; /* turn on blue LED */
	else 
		PTD->PSOR = 0x02; /* turn off blue LED */
}

void init_RED_LED (void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* enable clock to Port B */
	PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO | RED*/
	PTB->PDDR |= R_LED; /* make PTB18 as output pin */
}

void init_GREEN_LED (void){
	SIM->SCGC5 |= 0x400; /* enable clock to Port B */
	PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO | GREEN*/
	PTB->PDDR |= G_LED; /* make PTB19 as output pin */
}

void init_BLUE_LED (void){
	SIM->SCGC5 |= 0x1000; 	// enable clock to Port D 
	PORTD->PCR[1] = 0x100;// make PTD1 pin as GPIO | Blue
	PTD->PDDR |= 0x02; 		// make PTD1 as output pin
}

void toggle_LED (uint32_t desired){
	/* Turn off Green or Red LED */
	FPTB->PTOR = desired; // make the pin output low		
}

void toggle_Blue_LED (void){
	PTD->PTOR = B_LED; /* toggle blue LED */
}