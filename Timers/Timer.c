/*
Timers and Counters

Los separatistas
-----------------------
All ARM Chips come with an integrated System Tick Timer
		No tiene optuput compare ni otras funcionalidades, pq se utiliza como metr�nomo
			Periodicidad
			Sincronizaci�n de componentes dentro de la tarjeta 
		3 Timers en la tarjeta 
		Timer es principalmente para un delay, tener diferentes frecuencias de reloj
			Output compare, y otras funcionalidades 
		
Difference betwen System tick and one channel timer?


STCURENT  -> Sets counter
STRELOAD -> Value to count down from
*/

#include <MKL25Z4.h>

#define R_LED 0x40000
#define G_LED 0x80000
#define B_LED 0x02

void turn_on_LED (uint32_t desired);
void turn_off_LED (uint32_t desired);
void toggle_Blue_LED (void);

void delay1ms(void);
void delayMs(int n);
void act1 (void);
void act2 (void);
void act3 (void);
void act4 (void);

void init_RED_LED (void);
void init_BLUE_LED (void);
void init_GREEN_LED (void);

int main (void) {
	
	act4();
	
}

void init_RED_LED (void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* enable clock to Port B */
	PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO | RED*/
	PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
}

void init_GREEN_LED (void){
	SIM->SCGC5 |= 0x400; /* enable clock to Port B */
	PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO | GREEN*/
	PTB->PDDR |= 0x80000; /* make PTB19 as output pin */
}

void init_BLUE_LED (void){
	SIM->SCGC5 |= 0x1000; 	// enable clock to Port D 
	PORTD->PCR[1] = 0x100;// make PTD1 pin as GPIO | Blue
	PTD->PDDR |= 0x02; 		// make PTD1 as output pin 
	// Ojo con las D de PTD Y PORTD
}

void turn_off_LED (uint32_t desired){
	/* Turn off Green or Red LED */
	FPTB->PSOR = desired; // make the pin output low
		
}
void turn_on_LED (uint32_t desired){
	/* Turn on Green or Red LED */
	FPTB->PCOR = desired; // make the pin output high
}

void toggle_Blue_LED (void){
	PTD->PTOR = B_LED; /* toggle blue LED */
}
void act1 (void){
	/* Part 1. Make use of the SysTick timer to toggle the led in the KL25z board. 
	A counter should be used and its value must be shifted 4 places to the right so 
	that the changes can be slow enough to be visible in the LED of the board 
	(connect the output to the red LED, PTB18) */
	uint32_t c;
	
	init_RED_LED();
	
	/* Configure SysTick */
	SysTick->LOAD = 0xFFFFFF; 										// reload reg. with max val
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 			// Enable clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 	// Use system clock
	 
	while (1) {
		c = SysTick-> VAL; 													// read current val of down counter 
		PTB->PDOR = c >> 4; 												// line up counter MSB with LED 
	}
}

/* PART II*/
void act2(void) {
	/*Part 2. Toggling green LED using SysTick delay. This program should make use of 
	the SysTick to generate one second delay to toggle the green LED. System clock is 
	running at 41.94 MHz.  SysTick is configure to count down from 41939 to give a 
	1 ms delay. For every 1000 delays (1 ms * 1000 = 1 sec), toggle the green LED once. 
	The green LED is connected to PTB19. */
	
	int i;
	init_GREEN_LED ();

	while (1){
		
		turn_off_LED(G_LED);
		
		/*Wait 1000 ms*/
		delayMs(1000);
			/* If we use delay1ms(), and a 1000 cycles for
				it takes more time to react, I believe that's beacuse we
				stopped the timer after the ms has passed, and it takes a
				while to enable it again. */
		
		turn_on_LED(G_LED);
		/*Wait 10 ms, just so LED can shine */
		for (i = 0; i < 10; i++){
			delay1ms();
		}
	}
	
}

/* PART III*/

void act3 (void) {
	/*Part 3. Toggling blue LED using TPM0 delay (prescaler). 
	This program has to make use of the TPM0 to generate maximal delay to toggle the blue LED. 
	MCGFLLCLK (41.94 MHz) is used as timer counter clock. Prescaler must be set to divide by 128 and the Module register to 65,535. 
	The timer counter overflows at 41.94 MHz / 128 / 65,536 = 5.0 Hz. The blue LED is connected to PTD1.*/

	init_BLUE_LED ();
	
	SIM->SCGC6 = SIM_SCGC6_TPM0_MASK;	// Enable System Clock gate to Clock's register
	SIM->SOPT2 |= 0x01000000; // SIM_SOPT2_PLLFLLSEL_MASK << SIM_SOPT2_RTCCLKOUTSEL_SHIFT; // MCGFLLCLK	?				
	//TPM0->SC = 0;
	TPM0->SC = SIM_SOPT2_TPMSRC_MASK; // Disable clock
	TPM0->SC = TPM_SC_PS(0x07);			 	// prescaler 128 
	TPM0->MOD = 0xFFFF;					 			// max modulo value 
	TPM0->SC |= TPM_STATUS_TOF_MASK; 	// clear TOF 
	
	TPM0->SC |= 0x08; // enable timer free-running mode // CMOD LPTPM?
	/*
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; // Use MCGFLLCLK as CNT clock - Wont work |||| SIM->SOPT2 |= 0x01000000;	
	TPM0->SC |= 0x08; 											// enable timer free-running mode
	*/
	while (1) {
		while((TPM0->SC & 0x80) == 0) {}
		/* wait until the TOF is set 
			This is done trough polling, which is not the best since we have to
			go to the register and read it each time. Later on we'll see how to
			do it with interruptions*/
		TPM0->SC |= TPM_STATUS_TOF_MASK; /* clear TOF */
		toggle_Blue_LED();
	}
}




/* PART IV*/
void act4 (void) {
	/* Part 4. Longer time interval. Toggling blue LED using TPM0 delay. 
	The program must use TPM0 to generate long delay to toggle the blue LED. 
	MCGIRCLK (32.768 kHz) is used as timer counter clock. Prescaler is set to divided by 4 and the Modulo register is set to 40,959. 
	The timer counter overflows at 32,768 Hz / 40,960 / 4 = 0.2 Hz.  The blue LED is connected to PTD1.
	*/	
	
	init_BLUE_LED ();
	
	SIM->SCGC6 = SIM_SCGC6_TPM0_MASK;	// Enable System Clock gate to Clock's register
	SIM->SOPT2 |= 0x03000000 ; // SIM_SOPT2_PLLFLLSEL_MASK << SIM_SOPT2_RTCCLKOUTSEL_SHIFT; // MCGFLLCLK	?				
	//TPM0->SC = 0;
	TPM0->SC = SIM_SOPT2_TPMSRC_MASK; // Disable clock
	TPM0->SC = TPM_SC_PS(0x2);			 	// prescaler 4 
	TPM0->MOD = 40960 -1;					 		// Set modulo value 40,959.
	TPM0->SC |= TPM_STATUS_TOF_MASK; 	// clear TOF 
	
	TPM0->SC |= 0x08; // enable timer free-running mode // CMOD LPTPM?
	
	while (1) {
		while((TPM0->SC & 0x80) == 0) {}
		/* wait until the TOF is set */
		TPM0->SC |= TPM_STATUS_TOF_MASK; /* clear TOF */
		toggle_Blue_LED();
	}

}


void delayMs(int n) {
	int i;
	SysTick->LOAD = 41940 - 1;
	SysTick->CTRL = 0x5; /* Enable the timer and choose sysclk as the clock source */

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
	SysTick->LOAD = 41939;												// Since clock is running at 41.939 MHz
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 			// Enable clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 	// Use system clock
	
	while((SysTick->CTRL & 0x10000) == 0){} 			// wait until the COUNT flag is set 
	
	SysTick->CTRL = 0; 														// Stop the timer (Enable = 0) 
}

