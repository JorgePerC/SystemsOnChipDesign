/*
	LCD Display
*/

/*  Initialize and display ?Hello? on the LCD using 8-bit data mode.

* Data pins use Port D, control pins use Port A.
* This program does not poll the status of the LCD.
* It uses delay to wait out the time LCD controller is busy.

* Timing is more relax than the HD44780 datasheet to accommodate the variations among the LCD modules.

* You may want to adjust the amount of delay for your LCD controller. */

#include <MKL25Z4.h>

#define RS 0x04 /* PTA2 mask */
#define RW 0x10 /* PTA4 mask */
#define EN 0x20 /* PTA5 mask */

/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at */ /*41.94 MHz in SystemInit(). */


void LCD_command(unsigned char command);
void LCD_command_noWait(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_ready(void);
void delayMs(int n);


int main(void){
	LCD_init();
	LCD_command(0xF);
	
	for(;;){
		LCD_command(1); /* clear display */
		delayMs(500);
		LCD_command(0x80); /* set cursor at first line */
		LCD_data('H'); /* write the word */
		LCD_data('e');
		LCD_data('l');
		LCD_data('l');
		LCD_data('o');
		LCD_command(0xC0); /* set cursor at second line */
		LCD_data('W'); /* write the word */
		LCD_data('o');
		LCD_data('r');
		LCD_data('l');
		LCD_data('d');
		delayMs(500);
	} 
}


void delayMs(int n) {

	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++) { }

}


void LCD_init(void)	{
	SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
	
	PORTD->PCR[4] = 0x100; /* make PTD4 pin as GPIO */
	PORTD->PCR[5] = 0x100; /* make PTD5 pin as GPIO */
	PORTD->PCR[6] = 0x100; /* make PTD6 pin as GPIO */
	PORTD->PCR[7] = 0x100; /* make PTD7 pin as GPIO */

	PTD->PDDR = 0xF0; /* make PTD7-4 as output pins */
	
	SIM->SCGC5 |= 0x0200; /* enable clock to Port A */
	
	PORTA->PCR[2] = 0x100; /* make PTA2 pin as GPIO */
	PORTA->PCR[4] = 0x100; /* make PTA4 pin as GPIO */
	PORTA->PCR[5] = 0x100; /* make PTA5 pin as GPIO */
	
	PTA->PDDR |= 0x34; /* make PTA5, 4, 2 as out pins*/

	delayMs(30); /* initialization sequence */

	//LCD_command(0x30); // LCD_command_noWait
	delayMs(10);
	
	//LCD_command(0x30);	// LCD_command_noWait
	delayMs(1);
	
	//LCD_command(0x30);	// LCD_command_noWait
	
	/* set 4-bit data, 2-line, 5x7 font */
	LCD_command(0x28);
	
	/* move cursor right */
	LCD_command(0x06); 
	/* clear screen, move cursor to home */
	LCD_command(0x01);
	/* turn on display, cursor blinking */
	LCD_command(0x0F);

}

void LCD_command(unsigned char command) {
	PTA->PCOR = RS | RW; /* RS = 0, R/W = 0 */
	PTD->PDOR = command;
	PTA->PSOR = EN; /* pulse E */

	delayMs(0);
	PTA->PCOR = EN; 

	if (command < 4)
	delayMs(4); /* command 1 and 2 needs up to 1.64ms */
	else
	delayMs(1); /* all others 40 us */
}

void LCD_command_noWait(unsigned char command){
	PTA->PCOR = RS | RW; /* RS = 0, R/W = 0 */
	PTD->PDOR = command;
	PTA->PSOR = EN; /* pulse E */
	delayMs(0);
	PTA->PCOR = EN; 
}

void LCD_data(unsigned char data){

	PTA->PSOR = RS; /* RS = 1, R/W = 0 */

	PTA->PCOR = RW;

	PTD->PDOR = data;

	PTA->PSOR = EN; /* pulse E */

	delayMs(0);
	PTA->PCOR = EN;
	delayMs(1);
}

/* This function waits until LCD controller is ready to accept a new command/data before returns. */
void LCD_ready(void){
	char status;
	PTD->PDDR = 0; /* PortD input */
	PTA->PCOR = RS; /* RS = 0 for status */
	PTA->PSOR = RW; /* R/W = 1, LCD output */
	
	do { /* stay in the loop until it is not busy */
		PTA->PSOR = EN; /* raise E */
		delayMs(0);
		status = PTD->PDIR; /* read status register */
		PTA->PCOR = EN;
		delayMs(0); /* clear E */
	} while (status & 0x80); /* check busy bit */
	
	PTA->PCOR = RW; /* R/W = 0, LCD input */
	PTD->PDDR = 0xFF; /* PortD output */
}


