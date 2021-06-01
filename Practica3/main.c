/*
Pr�ctica 3 LCD, Keyboard, Timers

Los separatistas
*/

#include <MKL25Z4.h>
#include "LCD_Display.h"
#include "Keypad.h"
#include "I2C.h"
#include "LEDs.h"

void delay1ms(void);
void delayMs(int n);

void act1(void);
void act2(void);

void displayMenu(void);
void displayFeedback(unsigned int);
void LCD_sendWord(char *word);

void show_countdown(unsigned int * d);
void fill_numbers (unsigned int * d);
unsigned int convert_array_2_num(unsigned int * d);

int mainLCD(void);
int mainKeypad(void);



// MAIN----------

int main (void){
	act1();
	//act2();
}

void act1(void){
	unsigned int key;
/*
Part 1. Menu and output management. Write a very simple program that displays the following message in the LCD screen
* Menu in function

Then write a function that recovers the data from the get_key() function (plus a decoder) and switch on a led 
depending on which key was pressed (1: Red, 2: Blue, 3: Green) and display
* Feedback in function
The led should remain on for a few seconds, then go off and display the initial menu again.
*/
	init_RED_LED ();
	init_GREEN_LED ();
	init_BLUE_LED ();
 
	LCD_init(DCommd_8bits);
	while (TRUE){
		LCD_command(DCommd_CursorBlink);
		displayMenu();
		delayMs(500);
		key = keypad_getkey();
		
		if (key != 0){
			displayFeedback(key);
			delayMs(3000);
		}
		
		turn_off_all_LEDs();
		LCD_command(DCommd_ClearDisplay);
	}
	

}


void displayMenu(void){
/*
------------------------------
        PRESS BUTTON
R: 1       B: 2        G: 3
------------------------------
*/
	LCD_command(0x80); 	// set cursor at first line
	
	// write the word
	char message[] = "PRESS BUTTON";
	LCD_sendWord(message);
	
	LCD_command(0xC0); 	// set cursor at second line
	char msg[] = "R:1 | G:2 | B: 3";
	LCD_sendWord(msg);
	delayMs(500);

}

void displayFeedback(unsigned int key_pressed ){
// Show menu and turn on corresponding LEDs
/*
-------------------
  RED/BLUE/GREEN
    LED IS ON!
-------------------
*/

	// Read Port Data Input Register 
		// To know which LED is on


	LCD_command(0x80); 	// set cursor at the first line
	char *w;
	
	switch (key_pressed){
	// TODO VERIFY CASES
	case 0: 
		w = "RED"; 
		toggle_LED (R_LED);
		break;
	case  1:
		w = "BLUE";
		toggle_Blue_LED();
		break;
	case 2:
		w = "GREEN";
		toggle_LED (G_LED);
		break;
	default:
		w = "ERROR";
		break;
	}
	LCD_sendWord(w);
	
	LCD_command(0xC0); 	// set cursor at the second line
	char word[] = "LED is ON";
	LCD_sendWord(word);
	
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
	unsigned int select_Numbers []= {0,0};
	
	LCD_init(DCommd_8bits);
	
	LCD_command(DCommd_ClearDisplay);
	LCD_command(DCommd_CursorFirstLine);
	char word [] = "Hello there";
	while (TRUE){
		// Display Hello there
		LCD_sendWord(word);
		delayMs(5000);
		
		fill_numbers(select_Numbers);
		
		show_countdown(select_Numbers);
		
		LCD_command(DCommd_ClearDisplay);
	}
	
}

void fill_numbers (unsigned int * d){
	//Method to receive as input the time to count down from.
	// This method does not take into account if the first key pressed is #
	// It also won't show the selection
	unsigned int keyP;
	int i;
	for (i = 0; i < 2; i++) {
		 keyP = keypad_getkey();
		if (keyP == 20){ // TODO: Place value for #
			break;
		}else{
			d[i] = keyP;
		}
	}	
}

void show_countdown(unsigned int * d){
	// Method to countdown and shown how muc time remaining there is.
	
	unsigned int i;
	char word[10]; // make sure you allocate enough space to append the other string
	char w[] = "Counting";
	// In ASCII, Numbers begin at 48 = 0
	// We add 48 to the selected numbers to get their char
	
	// count decimal places in seconds
	unsigned int total_countdown = convert_array_2_num(d);
	
	for(i = total_countdown - 1 ; i < 0 ; i ++){
		LCD_command(DCommd_ClearDisplay);
		LCD_command(DCommd_CursorFirstLine);
		LCD_sendWord (w);
		
		LCD_command(DCommd_CursorSecondLine);
		sprintf(word, "%d", i);
		LCD_sendWord (word);
		delayMs(10000);
	}
}

unsigned int convert_array_2_num(unsigned int * d){
	//Converts the input from the keyboard into a number from 0-99
	unsigned int i;
	unsigned int res = 0;
	for (i = 0; i < sizeof(d)/sizeof(int); i++){
		res = res + d[ (sizeof(d)/sizeof(int)) - i]* 10*i; // This is not scalable.
	}
	
	return res;
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

