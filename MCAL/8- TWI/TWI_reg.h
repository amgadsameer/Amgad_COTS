/*******************************************************************/
/*******************************************************************/
/******** Author:    Amgad Samir ***********************************/
/******** Component: TWI         ***********************************/
/******** Layer:     MCAL        ***********************************/
/******** Version:   1.0         ***********************************/
/*******************************************************************/
/*******************************************************************/

#ifndef TWI_REG_H_
#define TWI_REG_H_

#define TWCR		*((volatile uint8*)0x56)		/*TWI Control Register*/
#define TWCR_TWINT	7u								/*Interrupt Flag*/
#define TWCR_TWEA	6u                           	/*Enable Acknowledge*/
#define TWCR_TWSTA	5u                           	/*Start Condition*/
#define TWCR_TWSTO	4u                           	/*Stop Condition*/
#define TWCR_TWWC	3u                           	/*Write Collision*/
#define TWCR_TWEN	2u                           	/*Enable*/
#define TWCR_TWIE	0u                           	/*Interrupt Enable*/

#define TWDR 		*((volatile uint8*)0x23)       	/*TWI Data Register*/

#define	TWAR		*((volatile uint8*)0x22)       	/*TWI Address Register*/
#define TWAR_TWGCE	0u								/*General Call recognition Enable*/

#define TWSR		*((volatile uint8*)0x21)       	/*TWI Status Register*/
#define TWSR_TWPS0	0u								/*Prescaler Bit0*/
#define TWSR_TWPS1	1u								/*Prescaler Bit1*/

#define TWBR		*((volatile uint8*)0x20)       	/*TWI Bit Rate Register*/


#endif /* TWI_REG_H_ */
