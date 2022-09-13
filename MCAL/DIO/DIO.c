/*
 * DIO.c
 *
 * Created: 9/6/2022 2:36:04 PM
 *  Author: KHALED
 */ 
#include "DIO_Interface.h"




typedef enum {
	DIO_INIT,
	DIO_NOT_INIT
	}DIO_init_flag_t;

static DIO_init_flag_t dioInitArr[NO_OF_PORTS][NO_OF_PINS] = {
	{DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT}, 
	{DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT},
	{DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT}, 
	{DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT, DIO_NOT_INIT}
	};
	
EN_DIO_error_t DIO_init(ST_DIO_config_t* dio_config_ptr)
{
	EN_DIO_error_t dioInitErr = DIO_OK;

	if (dio_config_ptr->pin < 0 || dio_config_ptr->pin > PIN7) return DIO_INVALID_PIN;
	
		
	switch(dio_config_ptr->pin_config)
	{
		case OUTPUT:
		
			switch(dio_config_ptr->port)
			{
				case PORT_A:
					SET_BIT(DDRA, dio_config_ptr->pin); 
					break;
				
				case PORT_B:
					SET_BIT(DDRB, dio_config_ptr->pin);
					break;
				
				case PORT_C:
					SET_BIT(DDRC, dio_config_ptr->pin);
					break;
				
				case PORT_D:
					SET_BIT(DDRD, dio_config_ptr->pin);
					break;
				default:
					dioInitErr = DIO_INVALID_PORT;
					break;
			}
			break;
		
		case INFREE:
			switch(dio_config_ptr->port)
			{
				case PORT_A:
					CLR_BIT(DDRA, dio_config_ptr->pin);
					CLR_BIT(PORTA, dio_config_ptr->pin);
					break;
				
				case PORT_B:
					CLR_BIT(DDRB, dio_config_ptr->pin);
					CLR_BIT(PORTB, dio_config_ptr->pin);
					break;
				
				case PORT_C:
					CLR_BIT(DDRC, dio_config_ptr->pin);
					CLR_BIT(PORTC, dio_config_ptr->pin);
				
					break;
				
				case PORT_D:
					CLR_BIT(DDRD, dio_config_ptr->pin);
					CLR_BIT(PORTD, dio_config_ptr->pin);
					break;
				
				default:
					dioInitErr = DIO_INVALID_PORT;
					break;
			}
			break;
		
		case INPULL:
			switch(dio_config_ptr->port)
			{
				case PORT_A:
					CLR_BIT(DDRA, dio_config_ptr->pin);
					SET_BIT(PORTA, dio_config_ptr->pin);
					break;
				
				case PORT_B:
					CLR_BIT(DDRB, dio_config_ptr->pin);
					SET_BIT(PORTB, dio_config_ptr->pin);
					break;
				
				case PORT_C:
					CLR_BIT(DDRC, dio_config_ptr->pin);
					SET_BIT(PORTC, dio_config_ptr->pin);
				
					break;
				
				case PORT_D:
					CLR_BIT(DDRD, dio_config_ptr->pin);
					SET_BIT(PORTD, dio_config_ptr->pin);
					break;
				
				default:
					dioInitErr = DIO_INVALID_PORT;
					break;
			}
			break;
			
		default:
			dioInitErr = DIO_INVALID_PIN_CONFIG;
			break;

		
	}
	if (dioInitErr == DIO_OK)
	{
		dioInitArr[dio_config_ptr->port][dio_config_ptr->pin] = DIO_INIT; // save that pin is initialized 
	}
	return dioInitErr;

}//DIO_init
EN_DIO_error_t DIO_write(EN_DIO_port_t port, EN_DIO_pin_t pin, EN_DIO_state_t state)
{
	// check the pin argument, to avoid memory damage
	if (pin <	PIN0 || pin > PIN7) return DIO_INVALID_PIN;
	
	
	// check if pin is initialized or not
	if (dioInitArr[port][pin] == DIO_NOT_INIT) return DIO_NOT_INITIALIZED;
	
	
	
	EN_DIO_error_t dioWriteErr = DIO_OK;

	switch(state)
	{
		case HIGH:
			switch(port)
			{
				case PORT_A:
					SET_BIT(PORTA, pin);
					break;
				
				case PORT_B:
					SET_BIT(PORTB, pin);
					break;
				
				case PORT_C:
					SET_BIT(PORTC, pin);
					break;
				
				case PORT_D:
					SET_BIT(PORTD, pin);
					break;
				
				default:
					dioWriteErr = DIO_INVALID_PORT;
					break;
			}
			break;
		
		case LOW:
			switch(port)
			{
				case PORT_A:
					CLR_BIT(PORTA, pin);
					break;
				
				case PORT_B:
					CLR_BIT(PORTB, pin);
					break;
					
				case PORT_C:
					CLR_BIT(PORTC, pin);
					break;
				
				case PORT_D:
					CLR_BIT(PORTD, pin);
					break;
				
				default:
					dioWriteErr = DIO_INVALID_PORT;
					break;
			}
			break;
		default:
			dioWriteErr = DIO_INVALID_STATE;
	}
	return dioWriteErr;
	
	
}//DIO_write
EN_DIO_error_t DIO_read(EN_DIO_port_t port, EN_DIO_pin_t pin, EN_DIO_state_t* pinStatePtr)
{
	// check the pin argument, to avoid memory damage
	if (pin <	PIN0 || pin > PIN7) return DIO_INVALID_PIN;
	
	// check if pin is initialized or not
	if (dioInitArr[port][pin] == DIO_NOT_INIT) return DIO_NOT_INITIALIZED;
	
	
	EN_DIO_error_t dioReadErr = DIO_OK;

	switch(port)
	{
		case PORT_A:
			*pinStatePtr = GET_BIT(PINA, pin);
			break;
			
		case PORT_B:
			*pinStatePtr = GET_BIT(PINB, pin);
			break;
			
		case PORT_C:
			*pinStatePtr = GET_BIT(PINC, pin);
			break;
			
		case PORT_D:
			*pinStatePtr = GET_BIT(PIND, pin);
			break;
		default:
			dioReadErr = DIO_INVALID_PORT;
	}
	return dioReadErr;
}//DIO_read
EN_DIO_error_t DIO_toggle(EN_DIO_port_t port, EN_DIO_pin_t pin)
{
	// check the pin argument, to avoid memory damage
	if (pin <	PIN0 || pin > PIN7) return DIO_INVALID_PIN;
	
	
	// check if pin is initialized or not
	if (dioInitArr[port][pin] == DIO_NOT_INIT) return DIO_NOT_INITIALIZED;
	
	
	EN_DIO_error_t dioToggleErr = DIO_OK;

	switch(port)
	{
		case PORT_A:
			TOG_BIT(PORTA, pin);
			break;
			
		case PORT_B:
			TOG_BIT(PORTB, pin);
			break;
			
		case PORT_C:
			TOG_BIT(PORTC, pin);
			break;
			
		case PORT_D:
			TOG_BIT(PORTD, pin);
			break;
		default:
			dioToggleErr = DIO_INVALID_PORT;
	}
	return dioToggleErr;
}//DIO_toggle

