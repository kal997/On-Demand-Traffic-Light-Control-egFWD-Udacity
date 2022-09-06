/*
 * DIO.c
 *
 * Created: 9/6/2022 2:36:04 PM
 *  Author: KHALED
 */ 
#include "DIO_Interface.h"

void DIO_init(ST_DIO_config_t* dio_config_ptr)
{
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
		}
		break;
		
		
	}

}//DIO_init
void DIO_write(EN_DIO_port_t port, EN_DIO_pin_t pin, EN_DIO_state_t state)
{
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
		}
		break;
	}
	
	
}//DIO_write
void DIO_read(EN_DIO_port_t port, EN_DIO_pin_t pin, EN_DIO_state_t* pinStatePtr)
{
	
	switch(port)
	{
		case PORT_A:
		*pinStatePtr = GET_BIT(PORTA, pin);
		break;
		
		case PORT_B:
		*pinStatePtr = GET_BIT(PORTB, pin);
		break;
		
		case PORT_C:
		*pinStatePtr = GET_BIT(PORTC, pin);
		break;
		
		case PORT_D:
		*pinStatePtr = GET_BIT(PORTD, pin);
		break;
	}
	

}//DIO_read
void DIO_toggle(EN_DIO_port_t port, EN_DIO_pin_t pin)
{
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
		}
}//DIO_toggle

