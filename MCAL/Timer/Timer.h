/*
 * Timer.h
 *
 * Created: 9/8/2022 1:44:40 PM
 *  Author: KHALED
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/bit_manipulation.h"
#include "../../Utilities/standard_types.h"
#include "../../Utilities/registers.h"



typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}EN_TIMER0_preScaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASE_CORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE

}EN_TIMER0_mode_t;


typedef struct {
	EN_TIMER0_mode_t timer0Mode;
	EN_TIMER0_preScaler_t timer0PreScaler;
	}ST_TIMER0_config_t;


typedef enum
{
	TIMER0_FLAG_LOW=0,
	TIMER0_FLAG_HIGH

}EN_TIMER0_flagState_t;


typedef enum {
	TIMER0_OK,
	TIMER0_INVALID_MODE,
	TIMER0_INVALID_PRESCALER,
	TIMER0_IN_USE,
	TIMER0_OUT_OF_RANGE_TICKS,
	
	}EN_TIMER0_error_t;
 
void TIMER0_stop(void);
EN_TIMER0_error_t TIMER0_setTicks(u8 ticks);
EN_TIMER0_error_t TIMER0_Init(ST_TIMER0_config_t* timerConfigPtr);
EN_TIMER0_error_t TIMER0_deInit(void);
EN_TIMER0_error_t TIMER0_isFree(void);
void TIMER0_OV_clearFlag(void);
EN_TIMER0_flagState_t TIMER0_OV_checkFlag(void);




void TIMER0_OV_InterruptEnable(void);
void TIMER0_OV_InterruptDisable(void);
void TIMER0_OV_SetCallBack(void(*)(void));





#endif /* TIMER_H_ */