/*
 * DIO_interface.h
 *
 * Created: 9/6/2022 2:35:46 PM
 *  Author: KHALED
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../../Utilities/bit_manipulation.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/standard_types.h"


typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
}EN_DIO_pin_t;
typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
}EN_DIO_port_t;
typedef enum{
	INPULL,
	INFREE,
	OUTPUT
}EN_DIO_pin_config_t;

typedef enum{
	LOW,
	HIGH
}EN_DIO_state_t;


typedef struct {
	EN_DIO_port_t port;
	EN_DIO_pin_t pin;
	EN_DIO_pin_config_t pin_config;
}ST_DIO_config_t;


void DIO_init(ST_DIO_config_t*);
void DIO_write(EN_DIO_port_t, EN_DIO_pin_t, EN_DIO_state_t);
void DIO_read(EN_DIO_port_t, EN_DIO_pin_t, EN_DIO_state_t*);
void DIO_toggle(EN_DIO_port_t, EN_DIO_pin_t);





#endif /* DIO_INTERFACE_H_ */