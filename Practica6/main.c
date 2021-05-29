

/*Reporte Practica 6*/
/*Los separatistas*/

#include <MKL25Z4.h>
#include <stdbool.h>

#include "tpm.h"

#define TPM_MODULE  3750
#define DUTY_MIN	220
#define DUTY_MAX	350

void set_pos(int angle);

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

void set_pos(int angle)
{
	int duty = 0;
	duty = angle*((DUTY_MAX-DUTY_MIN)/10) + DUTY_MIN;
	set_TPM_CnV(TPM1_BASE_PTR, 0, duty);
}
