/*
Pr�ctica 3 LCD, Keyboard, Timers

Los separatistas
*/

#include <MKL25Z4.h>
#include "LCD_Display.h"
#include "LCD_Display.c"


#define R_LED 0x40000
#define G_LED 0x80000
#define B_LED 0x02


void toggle_LED (uint32_t desired);
void toggle_Blue_LED (void);

void delay1ms(void);
void delayMs(int n);

void init_RED_LED (void);
void init_BLUE_LED (void);
void init_GREEN_LED (void);



void keypad_init(void);
char keypad_getkey(void);
void LED_set(int value);

void act1(void);
void act2(void);

void displayMenu(void);
void displayFeedback(void);
void sendWord(char *word);

int mainLCD(void);
int mainKeypad(void);



int main (void){
	act1();
}


int mainLCD(void){
	LCD_init(DCommd_8bits);
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


int mainKeypad(void){
	unsigned char key;

	keypad_init();
	//LED_init();

	while(1){
		key = keypad_getkey();
		LED_set(key); /* set LEDs according to the key code */
	}
}

void act1(void){
/*
Part 1. Menu and output management. Write a very simple program that displays the following message in the LCD screen
* Menu in function

Then write a function that recovers the data from the get_key() function (plus a decoder) and switch on a led 
depending on which key was pressed (1: Red, 2: Blue, 3: Green) and display
* Feedback in function
The led should remain on for a few seconds, then go off and display the initial menu again.
*/

	LCD_init(DCommd_8bits);
	LCD_command(0xF);
	displayMenu();

}


void displayMenu(void){
/*
------------------------------
        PRESS BUTTON
R: 1       B: 2        G: 3
------------------------------
*/
	
	for(;;){
		LCD_command(1); 	// clear display
		delayMs(500);
		LCD_command(0x80); 	// set cursor at first line
		
		LCD_data('P'); 		// write the word
		LCD_data('B');
		// write the word
		char message[] = "PRESS BUTTON";
		sendWord(message);
		/*
		LCD_command(0xC0); 	// set cursor at second line
		LCD_data('R'); 		// write the word
		LCD_data(':');
		LCD_data('1');
		LCD_data(' ');
		
		LCD_data('G'); 		// write the word
		LCD_data(':');
		LCD_data('2');
		LCD_data(' ');
		
		LCD_data('B'); 		// write the word
		LCD_data(':');
		LCD_data('3');
		*/

		delayMs(500);
	} 

}
void displayFeedback(){
/*
-------------------
  RED/BLUE/GREEN
    LED IS ON!
-------------------
*/

	// Read Port Data Input Register 
		// To know which LED is on


	LCD_command(0x80); 	// set cursor at the first line
	/*
	switch (expression){

	case constant-expression :
		 code 
		break;
	case  constant-expression :
		 code 
		break;
	case constant-expression :
		code 
		break;
	default:
		
		LCD_data('E'); 		// write the word
		LCD_data('R');
		LCD_data('R');
		LCD_data('O');
		LCD_data('R');
		break;
	}
	LCD_command(0xC0); 	// set cursor at the second line
	//char w[] = 'L','E','D',' ','I','S',' ','O','N'];
	//sendWord();
	*/
}



void act2(void){
/*
Part 2. Ascending Timer: The goal of the program is to implement a simple timer, as the ones used in sports or music. The code should proceed as follows:

It should print a hello and stay there for 5 seconds (you can use simple delay for this), then a second message should appear 
in the first line asking for the user to introduce the number of seconds.
To make this interesting, the code should be able to accept at least two digits, so you need to introduce the get_key(function) 
into a while loop that only stops when you press another not numerical key (for instance the * or # key.)
The introduced value should set the TMP_MODULO register in one timer and start it, either immediately after the termination key 
was selected or by pressing the same key again.
Then the LCD should show a message Counting and showing the current count value.
Once the timer has elapsed, you can use a buzzer (if you have it) or a led to mark that the timer went to zero.
*/


}





/* Initializes PortC that is connected to the keypad.
 Pins as GPIO input pin with pullup enabled.*/
void keypad_init(void){
	SIM->SCGC5 |= 0x0800;  /* enable clock to Port C */
	PORTC->PCR[0] = 0x103; /* PTC0, GPIO, enable pullup*/
	PORTC->PCR[1] = 0x103; /* PTC1, GPIO, enable pullup*/
	PORTC->PCR[2] = 0x103; /* PTC2, GPIO, enable pullup*/
	PORTC->PCR[3] = 0x103; /* PTC3, GPIO, enable pullup*/
	PORTC->PCR[4] = 0x103; /* PTC4, GPIO, enable pullup*/
	PORTC->PCR[5] = 0x103; /* PTC5, GPIO, enable pullup*/
	PORTC->PCR[6] = 0x103; /* PTC6, GPIO, enable pullup*/
	PORTC->PCR[7] = 0x103; /* PTC7, GPIO, enable pullup*/
	PTD->PDDR = 0x0F; /* make PTC7-0 as input pins */
}

/* keypad_getkey()
* If a key is pressed, it returns a key code. Otherwise, a zero is returned.
The upper nibble of Port C is used as input. Pull-ups are enabled when the keys are not pressed
* The lower nibble of Port C is used as output that drives the keypad rows.
* First all rows are driven low and the input pins are read. If no key is pressed, it will read as all ones. Otherwise, some key is pressed. 
* If any key is pressed, the program drives one row low at a time and leave the rest of the rows inactive (float) then read the input pins.
* Knowing which row is active and which column is active, the program can decide which key is pressed. */

char keypad_getkey(void) {

	int row, col;
	const char row_select[] = {0x01, 0x02, 0x04, 0x08}; 
	/* one row is active */
	/* check to see any key pressed */

	PTC->PDDR |= 0x0F; /* enable all rows */
	PTC->PCOR = 0x0F;
	//delayUs(2); /* wait for signal return */
	col = PTC-> PDIR & 0xF0; /* read all columns */
	PTC->PDDR = 0; /* disable all rows */
	if (col == 0xF0)
		return 0; /* no key pressed */


	/* If a key is pressed, we need find out which key.*/ 
	for (row = 0; row < 4; row++){ 
		PTC->PDDR = 0; /* disable all rows */

		PTC->PDDR |= row_select[row]; /* enable one row */
		PTC->PCOR = row_select[row]; /* drive active row low*/

		//delayUs(2); /* wait for signal to settle */
		col = PTC->PDIR & 0xF0; /* read all columns */

		if (col != 0xF0) break; 
	/* if one of the input is low, some key is pressed. */
	}
	
	PTC->PDDR = 0; /* disable all rows */

	if (row == 4)
		return 0; /* if we get here, no key is pressed */

	/* gets here when one of the rows has key pressed*/ 
	/*check which column it is*/

	if (col == 0xE0) 
		return row * 4 + 1; /* key in column 0 */
	if (col == 0xD0) 
		return row * 4 + 2; /* key in column 1 */
	if (col == 0xB0) 
		return row * 4 + 3; /* key in column 2 */
	if (col == 0x70) 
		return row * 4 + 4; /* key in column 3 */
	
	return 0; /* just to be safe */
}

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

void delayMs(int n) {
	int i;
	SysTick->LOAD = 41940 - 1;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 		// Enable clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 	// Use system clock

	for(i = 0; i < n; i++) {
		while((SysTick->CTRL & 0x10000) == 0)
	 /* wait until the COUTN flag is set */
		{ }
	}
	SysTick->CTRL = 0; 
	/* Stop the timer (Enable = 0) */
}

void delay1ms(void) {
	/* Configure SysTick */
	SysTick->LOAD = 41939;							// Since clock is running at 41.939 MHz
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 		// Enable clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 	// Use system clock
	
	while((SysTick->CTRL & 0x10000) == 0){} 		// wait until the COUNT flag is set 
	
	SysTick->CTRL = 0; 														// Stop the timer (Enable = 0) 
}

