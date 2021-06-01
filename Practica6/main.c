

/*Reporte Practica 6*/
/*Los separatistas*/

#include <MKL25Z4.h>
#include <stdbool.h>

#include "tpm.h"

#define TPM_MODULE  3750
#define DUTY_MIN	220
#define DUTY_MAX	350

void set_pos(int angle);
void part1(void);
void delayMs(int n)

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
