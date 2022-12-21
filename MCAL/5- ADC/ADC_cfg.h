#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/**
 * @details configure the reference voltage, options are: 1- AREF_REF
 * 														  2- AVCC_REF
 * 														  3- INTERNAL_2560mV_REF
 */
#define ADC_u8REF_VOLT				AVCC_REF

/**
 * @details configure the required ADC resolution, options are: 1- EIGHT_BITS
 * 																2- TEN_BITS
 */
#define ADC_u8RESOLUTION			EIGHT_BITS

/**
 * @details configure the interrupt enable configuration, options are: 1- ENABLED
 * 																	   2- DISABLED
 */
#define ADC_u8INT_ENABLE			DISABLED


#define ADC_u8PRESCALER_VAL			DIVISION_BY_128

#define ADC_u32TIMEOUT				50000u

#endif
