#ifndef TYPES_H_
#define TYPES_H_

/***********************************************************************/
/*
 * The basic data types
 */
typedef unsigned char		uint8_t;  /*  8 bits */
typedef unsigned short	    uint16_t; /* 16 bits */
typedef unsigned long	    uint32_t; /* 32 bits */

typedef signed char		    int8_t;   /*  8 bits */
typedef signed short        int16_t;  /* 16 bits */
typedef signed long		    int32_t;  /* 32 bits */


typedef volatile int8_t		vint8_t;  /*  8 bits */
typedef volatile int16_t	vint16_t; /* 16 bits */
typedef volatile int32_t	vint32_t; /* 32 bits */

typedef volatile uint8_t	vuint8_t;  /*  8 bits */
typedef volatile uint16_t	vuint16_t; /* 16 bits */
typedef volatile unsigned long	vuint32_t; /* 32 bits */

typedef uint8_t bool;

#define TRUE 	(1)
#define FALSE	(0)


/***********************************************************************/

#endif /* TYPES_H_ */
