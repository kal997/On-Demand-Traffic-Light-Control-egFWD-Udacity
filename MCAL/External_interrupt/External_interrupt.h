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
}EN_EXT_InterruptSource_t;


typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	ANY_LOGIC_CHANGE,
	LOW_LEVEL
}EN_EXT_SenseControl_t;



typedef enum{
	EXT_INT_FLAG_LOW,
	EXT_INT_FLAG_HIGH
	}EN_EXT_flag_t;


typedef enum {
	EXT_INT_OK,
	EXT_INT_INVALID_SOURCE,
	EXT_INT_INVALID_SENSE_CONTROL,
}EN_EXT_error_t;



EN_EXT_error_t EXT_InterruptEnable(EN_EXT_InterruptSource_t);
EN_EXT_error_t EXT_InterruptDisable(EN_EXT_InterruptSource_t);
EN_EXT_error_t EXT_InterruptSenseControl(EN_EXT_InterruptSource_t, EN_EXT_SenseControl_t);
EN_EXT_error_t EXT_InterruptSetCallback(EN_EXT_InterruptSource_t, void(*)(void));

EN_EXT_error_t EXT_Interrupt_ReadFlag(EN_EXT_InterruptSource_t, EN_EXT_flag_t*); // read flag API
EN_EXT_error_t EXT_Interrupt_WriteFlag(EN_EXT_InterruptSource_t); // write flag API









#endif /* EXTERNAL_INTERRUPT_H_ */