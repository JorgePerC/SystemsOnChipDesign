

/*Reporte Practica 6*/
/*Los separatistas*/

#include <MKL25Z4.h>
#include <stdbool.h>
#include "LEDs.h"
#include "Keypad.h"
#include "LCD_Display.h"

#include "tpm.h"

#define TPM_MODULE  3750
#define DUTY_MIN	220
#define DUTY_MAX	350

#define ModuleMotor 999

void set_pos(int angle);
void showControls(void);
void setMotorSpeed(unsigned k);

void part1(void);
void part2 (void);
void part3(void);

void delayMs(int n);

int main (void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* enable clock to Port B */
	PORTB_PCR0 = PORT_PCR_MUX(3);
	TPM_init_PWM(TPM1_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
	TPM_CH_init(TPM1_BASE_PTR, 0, TPM_PWM_H);
	set_TPM_CnV(TPM1_BASE_PTR, 0, DUTY_MIN);
	
	while (true){
		 for (int i = 0; i < 10; i ++){
			 set_pos(i);
			 
		 }
		 for (int i = 10; i > 0; i --){
			 set_pos(i);
		 }
	}
	
}

void set_pos(int angle){
	int duty = 0;
	duty = angle*((DUTY_MAX-DUTY_MIN)/10) + DUTY_MIN;
	set_TPM_CnV(TPM1_BASE_PTR, 0, duty);
}

void part1(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	PORTD->PCR[0] = 0x100; /* make PTD0 pin as GPIO */
	PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
	PORTD->PCR[2] = 0x100; /* make PTD2 pin as GPIO */
	PORTD->PCR[3] = 0x100; /* make PTD3 pin as GPIO */
	PORTD->PCR[7] = 0x103; 
	/* make PTD7 pin as GPIO and PE */

	PTD->PDDR |= 0x0F; /* make PTD0-3 as output pin */
	PTD->PDDR &= ~0x80; /* make PTD7 as input pin */
		
	if((PTD->PDIR & 0x80) == 0){ /* PTD7 == 0 */
		PTD->PDOR &= ~0x0F; /* open all switches */
		delayMs(100); /* wait 0.1 second */
		PTD->PDOR |= 0x09; /* close SW1 & SW4 */
		while((PTD->PDIR & 0x80) == 0) ; /*PTD7 == 0 */ 
	}

	else{ /* PTD7 == 1 */

	PTD->PDOR &= ~0x0F; /* open all switches */
	delayMs(100); /* wait 0.1 second */
	PTD->PDOR |= 0x06; /* close SW2 & SW3 */
	while((PTD->PDIR & 0x80) != 0) ; /*PTD7 == 0 */ 
	} 
}

void part2 (void){
	// Implement the code for the second example seen in class, in which the PWM 
	// signal is changed by increments of 1% in the CnV register. Observe how the 
	// intensity of the LED decreases as we increment the duty cycle (because the LED is active low).
	int dutyVal;
	int module = 999;
	
	
	init_BLUE_LED();
	
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTB_PCR0 = PORT_PCR_MUX(3);
	TPM_init_PWM(TPM1_BASE_PTR, TPM_PLLFLL, module, TPM_CLK, PS_1, EDGE_PWM);
	TPM_CH_init(TPM1_BASE_PTR, 4, TPM_PWM_H);
	
	for (dutyVal = 250; dutyVal < module; dutyVal = dutyVal + 7){
		set_TPM_CnV(TPM1_BASE_PTR, 4, dutyVal);
		if (TPM1_STATUS & TPM_STATUS_CH4F_MASK){
			toggle_Blue_LED();
		}
	}
	
}

void part3(void){
	
	// Part 3. Simple industrial control with PWM. Imagine that we want to create 
	// an industrial grinder. Usually, just like a with house blender, these systems 
	// have several power configurations depending on how “hard” are the components 
	// (i.e. gravel, stones) we wish to grind and thus the motor changes speed (and thus torque) 
	// to do the work. In this sense, we will create a simple application that can change
	// the speed depending on a setting defined by the user

	// When you start your application, the next message should be displayed.
  //                  Set input mode
  //            Mode 1: Man     Mode 2: Auto
	
	// Initialize timer
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTB_PCR0 = PORT_PCR_MUX(3);
	TPM_init_PWM(TPM1_BASE_PTR, TPM_PLLFLL, ModuleMotor, TPM_CLK, PS_1, EDGE_PWM);
	
	
	keypad_init();
	LCD_init(DCommd_4bits);
	
	char line_1 [] = "Set input mode";
	char line_2 [] = "1: Manual 2: Auto";
	
	LCD_command(DCommd_ClearDisplay);
	LCD_command(DCommd_CursorFirstLine);
	LCD_sendWord(line_1);
	LCD_command(DCommd_CursorSecondLine);
	LCD_sendWord(line_2);
	do{
	if (keypad_getkey() == 1){
		showControls();
	} else if (keypad_getkey() == 2){
		//autoControl();
	}
	}while(keypad_getkey() != 12); // # is 12
	
	
	
	// You can use each mode by pressing whichever button in the keyboard you choose 
	// and pressing # toe execute the rest of your application

	
}

void showControls(void){
	// In manual mode, the idea is that you integrate the first part of this lab, but modifying 
	// the code for generating inverted PWM signals. Thus, the LCD should display
	// 			Select Speed

	// 1: L    2:M     3:MH   4:H (standing for Low, Medium, Medium High and High)

	char line_1 [] = "Select speed";
	char line_2 [] = "1: L  2:M  3:MH  4:H";
	unsigned int k;
	
	
	LCD_command(DCommd_ClearDisplay);
	LCD_command(DCommd_CursorFirstLine);
	LCD_sendWord(line_1);
	LCD_command(DCommd_CursorSecondLine);
	LCD_sendWord(line_2);
	while (1){
		k = keypad_getkey();
		setMotorSpeed(k);
		if (k == 13){ // "*" = 13 
			// Enable interrupt
			//NVIC_EnableIRQ(PTA);
		}
	}
	


	// After this, if we want to modify the speed of the motor, we can use a push button to 
	// send an interrupt to the MCU and display the above menu again. A second button can be 
	// used to stop the system the motor at any given time (emergency signal)
}


void setMotorSpeed(unsigned k){
	// After pressing the one of the keys the corresponding CnV register values should be sent 
	// to a function the initializes the PWM (duty cycles of 25%, 50%, 75% and 100%). 
	
	unsigned int dutyVal;
	
	// Multiply baseline * desired speed
	dutyVal = 250*k;

	TPM_CH_init(TPM1_BASE_PTR, 3, TPM_PWM_H);
	
	set_TPM_CnV(TPM1_BASE_PTR, 4, dutyVal);
	
	if (TPM1_STATUS & TPM_STATUS_CH4F_MASK){
		toggle_Blue_LED();
	}

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
