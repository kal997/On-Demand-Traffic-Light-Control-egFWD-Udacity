/*
 * External_interrupt.h
 *
 * Created: 9/7/2022 12:27:05 PM
 *  Author: KHALED
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_
#include "../../Utilities/bit_manipulation.h"
#include "../../Utilities/standard_types.h"
#include "../../Utilities/registers.h"

typedef enum{
	EXT_INT0,
	EXT_INT1,
	EXT_INT2
}EXT_EN_InterruptSource_t;


typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	ANY_LOGIC_CHANGE,
	LOW_LEVEL
}EXT_EN_SenseControl_t;



typedef enum{
	FLAG_LOW,
	FLAG_HIGH
	}EXT_EN_flag_t;



void EXT_InterruptEnable(EXT_EN_InterruptSource_t);
void EXT_InterruptDisable(EXT_EN_InterruptSource_t);
void EXT_InterruptSenseControl(EXT_EN_InterruptSource_t, EXT_EN_SenseControl_t);
void EXT_InterruptSetCallback(EXT_EN_InterruptSource_t, void(*)(void));

void EXT_Interrupt_ReadFlag(EXT_EN_InterruptSource_t, EXT_EN_flag_t*); // read flag API
void EXT_Interrupt_WriteFlag(EXT_EN_InterruptSource_t); // write flag API










#endif /* EXTERNAL_INTERRUPT_H_ */