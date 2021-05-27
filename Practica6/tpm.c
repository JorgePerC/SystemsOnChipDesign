/*
 * tpm.c
 *
 *  Created on: Jul 16, 2013
 *      Author: B34443
 */


#include "tpm.h"


void TPM_init_PWM(TPM_MemMapPtr TPMx, int  clock_source, int module, int clock_mode, int ps, int counting_mode)
{
	if(TPMx == TPM0_BASE_PTR)
		SIM_SCGC6	|= SIM_SCGC6_TPM0_MASK;
	else if(TPMx == TPM1_BASE_PTR)
		SIM_SCGC6	|= SIM_SCGC6_TPM1_MASK;
	else
		SIM_SCGC6	|= SIM_SCGC6_TPM2_MASK;
	
	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(clock_source);
	
	TPM_MOD_REG(TPMx)  	=  module;
	
	TPM_SC_REG(TPMx)	|= TPM_SC_CMOD(clock_mode) | TPM_SC_PS(ps);
	
	if(counting_mode)
		TPM_SC_REG(TPMx) |= TPM_SC_CPWMS_MASK;
}

void TPM_CH_init(TPM_MemMapPtr TPMx, int channel, int mode)
{
	TPM_CnSC_REG(TPMx, channel) |= mode;
}

void set_TPM_CnV(TPM_MemMapPtr TPMx, int channel, int value)
{
	TPM_CnV_REG(TPMx, channel) = value;
}

