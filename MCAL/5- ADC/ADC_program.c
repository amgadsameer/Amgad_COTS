#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "ADC_privtate.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"
#include "ADC_reg.h"

static uint16* ADC_pu16ConversionResult = NULL;
static void(*ADC_pvNotificationFunc)(void) = NULL;
static uint8 ADC_u8BusyFlag = IDLE;

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


uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pu16Result != NULL)
	{
		/*Check if ADC is not busy*/
		if(ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32TimeoutCounter = 0u;

			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*configure the analog channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*wait until the conversion is complete or the timeout is passed*/
			while((GET_BIT(ADCSRA,ADCSRA_ADIF) ==0)  && (Local_u32TimeoutCounter < ADC_u32TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}
			if(Local_u32TimeoutCounter>= ADC_u32TIMEOUT)
			{
				/*Loop is broken because flag isn't raised until timeout is passed*/
				Local_u8ErrorState =TIMEOUT_ERR;
			}

			else
			{
				/*Loop is broken because flag is raised before the timeout is passed*/
				/*Clear the conversion complete flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result= ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result= ADC;
#endif

				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;
			}
		}
		else
		{
			/*ADC was busy, assign the error state*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result, void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		/*Check if ADC is not busy*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Initialize the result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the notification function globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*configure the analog channel*/
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable the ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief ADC conversion complete ISR
 */
void __vector_16 (void)		__attribute__((signal));
void __vector_16 (void)
{
	if(ADC_pu16ConversionResult != NULL)
	{
#if ADC_u8RESOLUTION == EIGHT_BITS
		*ADC_pu16ConversionResult= ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
		*ADC_pu16ConversionResult= ADC;
#endif

		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the application notification function*/
		if(ADC_pvNotificationFunc != NULL)
		{
			ADC_pvNotificationFunc();
		}
		else
		{
			/*Notification function pointer is NULL*/
		}
	}
	else
	{
		/*Conversion result pointer is NULL*/
	}
}
