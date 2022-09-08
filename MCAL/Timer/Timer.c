/*
 * Timer.c
 *
 * Created: 9/8/2022 1:44:27 PM
 *  Author: KHALED
 */ 

#include "Timer.h"

// static global pointer to function, to be set using setCallBack
static void (*Timer0_OVF_Fptr) (void) = NULLPTR;








void TIMER0_setInitialTicks(u8 ticks)
{
	TCNT0 = ticks;
}

void TIMER0_Init(ST_TIMER0_config_t* timerConfigPtr)
{
	// 1. selecting timer 0 mode
	switch (timerConfigPtr->timer0Mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASE_CORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FAST_PWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	
	// 2. clock select
	TCCR0&=0XF8; //0b11111000
	TCCR0 |= timerConfigPtr->timer0PreScaler;	
}

void TIMER0_OV_clearFlag(void)
{
	SET_BIT(TIFR, TOV0);
}
EN_TIMER0_flagState_t TIMER0_OV_checkFlag(void)
{
	return GET_BIT(TIFR, TOV0);
}


void TIMER0_stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}


void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OVF_Fptr = local_fptr;
}

ISR(TIMER0_OVF_vect)
{
	if(Timer0_OVF_Fptr != NULLPTR)
	{
		Timer0_OVF_Fptr();
	}
}
