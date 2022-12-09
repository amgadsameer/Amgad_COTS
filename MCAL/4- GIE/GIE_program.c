#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void)
{
	//SET_BIT(SREG,SREG_I);

	 __asm __volatile("SEI");	/*Inline assembly instruction to set I bit*/
}

void GIE_voidDisableGlobal(void)
{
	//CLR_BIT(SREG,SREG_I);

	__asm __volatile("CLI"); /*Inline assembly instruction to clear I bit*/
}
