/**************************************************************/
/**************************************************************/
/*********		Author: Amgad Samir			*******************/
/*********		File: PORT_prog.c			*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/
#include "STD_TYPES.h"

#include "PORT_reg.h"
#include "PORT_interface.h"
#include "PORT_cfg.h"
#include "PORT_private.h"

void PORT_voidInit(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	PORTA= PORTA_INITIAL_VAL;
	PORTB= PORTB_INITIAL_VAL;
	PORTC= PORTC_INITIAL_VAL;
	PORTD= PORTD_INITIAL_VAL;

}
