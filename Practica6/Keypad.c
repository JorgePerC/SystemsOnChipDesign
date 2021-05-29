#include "Keypad.h"

/* Initializes PortC that is connected to the keypad.
 Pins as GPIO input pin with pullup enabled.*/
void keypad_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;  /* enable clock to Port C */
	for (int i = 0; i< 8; i++ ){
		PORTC->PCR[i] = 0x103; /* PTC0, GPIO, enable pullup*/
	}
	
	PTD->PDDR = 0x0F; /* make PTC7-0 as input pins */
}

/* keypad_getkey()
* If a key is pressed, it returns a key code. Otherwise, a zero is returned.
The upper nibble of Port C is used as input. Pull-ups are enabled when the keys are not pressed
* The lower nibble of Port C is used as output that drives the keypad rows.
* First all rows are driven low and the input pins are read. If no key is pressed, it will read as all ones. Otherwise, some key is pressed. 
* If any key is pressed, the program drives one row low at a time and leave the rest of the rows inactive (float) then read the input pins.
* Knowing which row is active and which column is active, the program can decide which key is pressed. 
---------------------------------
Return meanings:
0 = no input
1 = no input | 2 = asdadssda  | 3 = asdadas  | 4 = asdasdasd
5 = no input | 6 = asdadssda  | 7 = asdadas  | 8 = asdasdasd
9 = no input | 10 = asdadssda | 11 = asdadas | 12 = asdasdasd
13 = no input | 14 = asdadssda | 15 = asdadas | 16 = asdasdasd

*/

unsigned int keypad_getkey(void) {

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