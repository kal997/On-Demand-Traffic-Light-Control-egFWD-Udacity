/*
 * Timer.c
 *
 * Created: 9/8/2022 1:44:27 PM
 *  Author: KHALED
 */ 

#include "Timer.h"

// static global pointer to function, to be set using setCallBack
static void (*Timer0_OVF_Fptr) (void) = NULLPTR;


// static global flag that indicates the timer0 state (in-use, available)
static EN_TIMER0_error_t timer0State = TIMER0_OK;








EN_TIMER0_error_t TIMER0_isFree(void)
{
	return timer0State;
}
EN_TIMER0_error_t TIMER0_setTicks(u8 ticks)
{	
	EN_TIMER0_error_t setTicksErr;
	if(ticks>255) setTicksErr = TIMER0_OUT_OF_RANGE_TICKS;
	else
	{
		 TCNT0 = ticks;
		 setTicksErr = TIMER0_OK;
	}
	return setTicksErr;
}
EN_TIMER0_error_t TIMER0_Init(ST_TIMER0_config_t* timerConfigPtr)
{
	//**** checking if the timer already in-use *********
	if (timer0State == TIMER0_IN_USE)
	{
		return TIMER0_IN_USE;
	}
	
	
	
	
	EN_TIMER0_error_t timer0initErr = TIMER0_OK;
	
	//************* 1. selecting timer 0 mode ***********
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
		default:
			timer0initErr = TIMER0_INVALID_MODE;
			break;
	}
	// return error state if mode is not selected properly.
	if(timer0initErr != TIMER0_OK) return timer0initErr;
	
	
	
	//********** 2. clock select *************
	if (timerConfigPtr->timer0PreScaler >8)
	{ 
		timer0initErr = TIMER0_INVALID_PRESCALER;
	}
	else
	{
		TCCR0 &= 0XF8; //0b11111000
		TCCR0 |= timerConfigPtr->timer0PreScaler;
	}
	
	// change timer state to in-use instead of free
	timer0State = TIMER0_IN_USE;
	
	// return error state if pre-scaler is not selected properly.
	return timer0initErr != TIMER0_OK? timer0initErr : TIMER0_OK;
		
}
EN_TIMER0_error_t TIMER0_deInit(void)
{
	// freeing timer 0 for usage
	timer0State = TIMER0_OK;
	return TIMER0_OK;
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
