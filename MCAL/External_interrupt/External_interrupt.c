/*
 *  External_interrupt.c
 *
 *  Created: 9/7/2022 12:29:11 PM
 *  Author: KHALED
 */ 
#include "External_interrupt.h"

// static, to act as a guard for these globals, accessed only via the EXT_InterruptSetCallback API
static void(*EXT_INT0_Ptr)(void) = NULLPTR;
static void(*EXT_INT1_Ptr)(void) = NULLPTR;
static void(*EXT_INT2_Ptr)(void) = NULLPTR;



void EXT_InterruptEnable(EXT_EN_InterruptSource_t interrupt_pin)
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		SET_BIT(GICR, INT0);
		break;
		
		case EXT_INT1:
		SET_BIT(GICR, INT1);
		break;
		
		case EXT_INT2:
		SET_BIT(GICR, INT2);
		break;
	}
}
void EXT_InterruptSenseControl(EXT_EN_InterruptSource_t interrupt_pin, EXT_EN_SenseControl_t sense)
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
			
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
			break;
			
			case LOW_LEVEL:
			CLR_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
		}
		break;
		
		case EXT_INT1:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
			
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
			break;
			
			case LOW_LEVEL:
			CLR_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
			break;
			
		}
		break;
		
		case EXT_INT2:
		switch(sense)
		{
			case RISING_EDGE:
			SET_BIT(MCUCSR, ISC2);
			break;
			
			case FALLING_EDGE:
			CLR_BIT(MCUCSR, ISC2);
			break;
			
			default:
			CLR_BIT(MCUCSR, ISC2);
		}
		break;
	}
}
void EXT_InterruptDisable(EXT_EN_InterruptSource_t interrupt_pin)
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		CLR_BIT(GICR, INT0);
		break;
		
		case EXT_INT1:
		CLR_BIT(GICR, INT1);
		break;
		
		case EXT_INT2:
		CLR_BIT(GICR, INT2);
		break;
	}
}
void EXT_Interrupt_ReadFlag(EXT_EN_InterruptSource_t interrupt_pin, EXT_EN_flag_t* flagPtr)
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		*flagPtr = GET_BIT(GIFR, INTF0);
		break;
		
		case EXT_INT1:
		*flagPtr = GET_BIT(GIFR, INTF1);
		break;
		
		case EXT_INT2:
		*flagPtr = GET_BIT(GIFR, INTF2);
		break;
	}
}
void EXT_Interrupt_WriteFlag(EXT_EN_InterruptSource_t interrupt_pin)
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		SET_BIT(GIFR, INTF0);
		break;
		
		case EXT_INT1:
		SET_BIT(GIFR, INTF1);
		break;
		
		case EXT_INT2:
		SET_BIT(GIFR, INTF2);
		break;
	}
}

void EXT_InterruptSetCallback(EXT_EN_InterruptSource_t interrupt_pin, void(*pLocal)(void))
{
	switch(interrupt_pin)
	{
		case EXT_INT0:
		EXT_INT0_Ptr = pLocal;
		break;
		
		case EXT_INT1:
		EXT_INT1_Ptr = pLocal;
		break;
		
		case EXT_INT2:
		EXT_INT2_Ptr = pLocal;
		break;
	}
}

ISR(INT0_vect)
{
	// da 3shan ma3mlsh runtime error lma ygarb y-call el code ely fe address 0
	// Because this will cause a runtime error, if the ISR is executed before the callback function pointer is set.
	if(EXT_INT0_Ptr!= NULLPTR) EXT_INT0_Ptr();
}
ISR(INT1_vect)
{
	if(EXT_INT1_Ptr!= NULLPTR) EXT_INT1_Ptr();
}
ISR(INT2_vect)
{
	if(EXT_INT2_Ptr!= NULLPTR) EXT_INT2_Ptr();
}


