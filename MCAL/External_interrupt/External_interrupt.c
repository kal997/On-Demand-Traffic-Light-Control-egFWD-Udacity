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



EN_EXT_error_t EXT_InterruptEnable(EN_EXT_InterruptSource_t interrupt_pin)
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;
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
		
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
			break;
	}
	return extInterruptErr;
}
EN_EXT_error_t EXT_InterruptSenseControl(EN_EXT_InterruptSource_t interrupt_pin, EN_EXT_SenseControl_t sense)
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;
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
				default:
					extInterruptErr = EXT_INT_INVALID_SENSE_CONTROL;
					break;
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
					CLR_BIT(MCUCR, ISC01);
				default:
					extInterruptErr = EXT_INT_INVALID_SENSE_CONTROL;
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
				
					CLR_BIT(MCUCR, ISC01);
				default:
					extInterruptErr = EXT_INT_INVALID_SENSE_CONTROL;
					break;
			}
			break;
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
	}
	return extInterruptErr;
}
EN_EXT_error_t EXT_InterruptDisable(EN_EXT_InterruptSource_t interrupt_pin)
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;

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
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
			
	}
	return extInterruptErr;
}
EN_EXT_error_t EXT_Interrupt_ReadFlag(EN_EXT_InterruptSource_t interrupt_pin, EN_EXT_flag_t* flagPtr)
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;

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
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
	}
	return extInterruptErr;
}
EN_EXT_error_t EXT_Interrupt_WriteFlag(EN_EXT_InterruptSource_t interrupt_pin)
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;
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
		
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
			break;
	}
	return extInterruptErr;
}

EN_EXT_error_t EXT_InterruptSetCallback(EN_EXT_InterruptSource_t interrupt_pin, void(*pLocal)(void))
{
	EN_EXT_error_t extInterruptErr = EXT_INT_OK;

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
		
		default:
			extInterruptErr = EXT_INT_INVALID_SOURCE;
			
	}
	return extInterruptErr;
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


