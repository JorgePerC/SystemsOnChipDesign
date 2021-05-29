
#include "LCD_Display.h"

void LCD_init(unsigned char bitSelection)	{
	int limit;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; /* enable clock to Port D */
	
	/* Set pins as GPIO */
	if (bitSelection == DCommd_8bits){
		limit = 7;
	}else{
		limit = 4;
	}
	
	for (int i = 0; i < limit; i++){
	
		PORTD->PCR[7-i] = 0x100; /* make PTD# pin as GPIO */
		// Deshabilitar interrupciones
		
	}
	
	/* Set pins as output pins */
	if (bitSelection == DCommd_8bits){
		PTD->PDDR = 0xFF; /* make PTD7-0 as output pins */
	}else{
		PTD->PDDR = 0xF0; /* make PTD7-4 as output pins */
											// TODO: Check
	}

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /* enable clock to Port A */
	
	PORTA->PCR[2] = 0x100; /* make PTA2 pin as GPIO */
	PORTA->PCR[4] = 0x100; /* make PTA4 pin as GPIO */
	PORTA->PCR[5] = 0x100; /* make PTA5 pin as GPIO */
	
	PTA->PDDR |= 0x34; /* make PTA5, 4, 2 as out pins*/

	waitUntilFinished();
	
	/* set 8-bit data, 2-line, 5x7 font */
	LCD_command(bitSelection);
	
	/* move cursor right */
	LCD_command(DCommd_IncrementCursor); 
	/* clear screen, move cursor to home */
	LCD_command(DCommd_CursorHome);
	/* turn on display, cursor blinking */
	LCD_command(DCommd_CursorBlink);

}


void LCD_command(unsigned char command) {
	PTA->PCOR = RS | RW; /* RS = 0, R/W = 0 */
	PTD->PDOR = command;
	PTA->PSOR = EN; /* pulse E */

	PTA->PCOR = EN; 

	waitUntilFinished();
}


void LCD_data(unsigned char data){

	PTA->PSOR = RS; /* RS = 1 */

	PTA->PCOR = RW; /* R/W = 0*/

	PTD->PDOR = data;

	PTA->PSOR = EN; /* pulse E */

	waitUntilFinished();
	
	PTA->PCOR = EN;
	
	waitUntilFinished();
}

void LCD_sendWord(char *word){
	// Send all individual letters
	for (unsigned int i = 0; i < sizeof (word); i++){
		LCD_data(word[i]);
	}

}

void waitUntilFinished(void){

	// TODO: CHECK
	/* Wait until LCD is not busy */
	do {
		/* BF can be read, when RS = LOW & R/W = HIGH on DB7 port */
		PTA->PCOR |= RS;
		PTA->PSOR |= RW;
	} while(PORTD->PCR[7]);
}
