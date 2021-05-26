
#include "I2C.h"

void init_I2C(void){
	// 1. Init clock to SIM_SCGC4 
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;  /* enable clock to Port C */
	
	// 2. Disable the I2C module while configuring
	
	// 3. Set the I2C clock speed 

	
	// 4. Enable I2C module

}

void send_data_I2C (void){
	
// 1. Poll the BUSY bit of I2Cx_S register until the bus is not busy.
// 2. Set TX (bit 4) of I2Cx_C1 register for transmitting.
// 3. Set MST (bit 5) of I2Cx_C1 register to put the I2C module in master mode and generate a START on the bus.
// 4. Write the Slave address + W to I2Cx_D register to send the slave address.
// 5. Poll IICIF (bit 1) of I2Cx_S until the transmission is terminated.
// 6. Clear IICIF bit by writing a 1 to it.
// 7. Check ARBL (bit 4) of I2Cx_S to see whether the arbitration was lost. If yes, clear ARBL bit by writing a 1 to it and abort the transmission.
// 8. Check RXAK (bit 0) of I2Cx_S to see whether the slave sent an ACK. If not, abort the transmission.
// 9. Write the data byte to I2Cx_D register to send the data.
// 10. Poll IICIF (bit 1) of I2Cx_S until the transmission is complete.
// 11. Clear IICIF bit by writing a 1 to it.
// 12. Check RXAK (bit 0) of I2Cx_S to see whether the slave sent an ACK.
// 13. Clear MST (bit 5) and TX (bit 4) of I2Cx_C1 register to generate a STOP on the bus. See figure below.

}