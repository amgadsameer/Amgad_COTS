
#ifndef TIMERS_REGISTER_H_
#define TIMERS_REGISTER_H_

#define OCR0			*((volatile uint8*)0x5C)			/*Output compare match register*/

#define TIMSK			*((volatile uint8*)0x59)			/*Timer mask register*/
#define TIMSK_TOIE0		0								/*Timer0 overflow interrupt enable*/
#define TIMSK_OCIE0		1								/*Timer0 compare match interrupt enable*/

#define TCCR0           *((volatile uint8*)0x53)			/*Timer counter control register 0*/
#define TCCR0_COM01		5								/*Compare match output mode bit 1*/
#define TCCR0_COM00		4								/*Compare match output mode bit 0*/
#define TCCR0_WGM00		6								/*Waveform generation mode bit 0*/
#define TCCR0_WGM01		3								/*Waveform generation mode bit 1*/


#define TCNT0           *((volatile uint8*)0x52)			/*Timer counter 0 register*/


#endif
