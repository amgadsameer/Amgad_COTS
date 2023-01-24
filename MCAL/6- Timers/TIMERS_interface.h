#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

void TIMER0_voidInit(void);

uint8 TIMERS_u8SetCallBack(uint8 Copy_u8TmrIntSource, void(*Copy_pvCallBackFunc)(void));


#endif