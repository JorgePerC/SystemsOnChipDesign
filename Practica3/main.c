/*
Pr�ctica 3 LCD, Keyboard, Timers

Los separatistas
*/

#include <MKL25Z4.h>
#include "LCD_Display.h"
#include "Keypad.h"
#include "I2C.h"

void delay1ms(void);
void delayMs(int n);

void act1(void);
void act2(void);

void displayMenu(void);
void displayFeedback(void);
void sendWord(char *word);


int mainLCD(void);
int mainKeypad(void);



// MAIN----------

int main (void){
	LCD_init(DCommd_8bits);
	LCD_command(0xF);
	
	LCD_command(1); 	// clear display
		delayMs(500);
		LCD_command(0x80); 	// set cursor at first line
		
		LCD_data('P'); 		// write the word
		LCD_data('B');
		// write the word
		char message[] = "PRESS BUTTON";
		sendWord(message);

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
	unsigned int key;

	keypad_init();
	//LED_init();

	while(1){
		key = keypad_getkey();
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

/*
int main (void){
	hal_i2c0_init(I2C0_B);
	
	//char l = 'z';
	//hal_dev_lcd_write_reg( 0x7, 0xF);
	
	hal_dev_lcd_write_reg( RS, 0x0);
	hal_dev_lcd_write_reg( RW, 0x0);
	hal_dev_lcd_write_reg( EN, 0x1);
	
	hal_dev_lcd_write_reg( 0x40, DCommd_4bits);
	hal_dev_lcd_write_reg( 0x40, DCommd_IncrementCursor);
	hal_dev_lcd_write_reg( 0x40, DCommd_CursorHome);
	hal_dev_lcd_write_reg( 0x40, DCommd_CursorBlink);
	hal_dev_lcd_write_reg( EN, 0x0);
	
	while (TRUE) {
		hal_dev_lcd_write_reg( RS, 0x1);
		hal_dev_lcd_write_reg( RW, 0x0);
		hal_dev_lcd_write_reg( 0x40, 'a');
		hal_dev_lcd_write_reg( EN, 0x1);
	}
	
}
static void pause(void)
{
    int n;
    for(n=0; n<40; n++){}
}

void hal_dev_lcd_write_reg(uint8_t addr, uint8_t data){
    i2c_start(I2C0_B);

    i2c_write_byte(I2C0_B, LCD_DISPLAY_I2C_ADDRESS | I2C_WRITE);
	
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_write_byte(I2C0_B, addr);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_write_byte(I2C0_B, data);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_stop(I2C0_B);
    pause();
}
*/
