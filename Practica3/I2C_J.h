/*
 *******************************************************************************
 *                              Los separatistas                               *
 *																																						 *
 * File to configure I2C communication protocol on the Freedom Development 		 *
 * board FRCM-KL25Z.																													 *
 * Created: 14/05/2021																												 *
 *******************************************************************************
*/

#include <MKL25Z4.h>

/*
 *******************************************************************************
 *                              Register Symbols                               *
 *******************************************************************************
*/


#define I2Cmask 0x20

/*
 *******************************************************************************
 *                              Type Definitions                               *
 *******************************************************************************
*/

/* Create an "object" 
	Take the following into account when declaring variables: 
	https://www.allaboutcircuits.com/technical-articles/understanding-memory-structures-in-embedded-c-language/
*/
typedef struct {
	unsigned char l;
	
} I2C_interface;



/*
 *******************************************************************************
 *                        General Function Declarations                        *
 *******************************************************************************
*/


void init_I2C(void);

void send_data_I2C (void);

void recieve_data_I2C (void);

