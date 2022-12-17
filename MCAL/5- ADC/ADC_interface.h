#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define ADC_SINGLE_ENDED_CH0		0u
#define ADC_SINGLE_ENDED_CH1        1u
#define ADC_SINGLE_ENDED_CH2        2u
#define ADC_SINGLE_ENDED_CH3        3u
#define ADC_SINGLE_ENDED_CH4        4u
#define ADC_SINGLE_ENDED_CH5        5u
#define ADC_SINGLE_ENDED_CH6        6u
#define ADC_SINGLE_ENDED_CH7        7u

void ADC_voidInit(void);


uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result);

uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result, void(*Copy_pvNotificationFunc)(void));


#endif
