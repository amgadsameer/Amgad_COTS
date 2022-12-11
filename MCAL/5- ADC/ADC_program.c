#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "ADC_privtate.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"
#include "ADC_reg.h"

void ADC_voidInit(void)
{
#if ADC_u8REF_VOLT	== AREF_REF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif  ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif  ADC_u8REF_VOLT == INTERNAL_2560mV_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
	#error Wrong ADC_u8REF_VOLT configuration option

#endif

#if ADC_u8RESOLUTION	== EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_u8RESOLUTION	== TEN_BITS
	CLR_BIT(ADMUX_ADMUX_ADLAR);

#else
	#error wrong ADC_u8RESOLUTION configuration option
#endif

#if ADC_u8INT_ENABLE	== DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_u8INT_ENABLE	== ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#else
	#error wrong ADC_u8INT_ENABLE configuration option
#endif

	/* configure prescaler bits */
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_u8PRESCALER_VAL;

	/*ADC Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}


uint16 ADC_u16GetChannelReading(uint8 Copy_u8Channel)
{
	/*configure the analog channel*/
	ADMUX &= CHANNEL_MASK;
	ADMUX |= Copy_u8Channel;

	/*Start the conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*wait until the conversion is complete*/
	while(GET_BIT(ADCSRA,ADCSRA_ADIF) ==0);

	/*Clear the conversion complete flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_u8RESOLUTION == EIGHT_BITS
	return ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
	return ADC;
#endif

}
