/*
 * LED.h
 *
 * Created: 9/6/2022 4:54:57 PM
 *  Author: KHALED
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/DIO_interface.h"

typedef struct ST_LED_t{
	EN_DIO_port_t ledPort;
	EN_DIO_pin_t ledPin;
	}ST_LED_t;
	
typedef enum {
	LED_OK,
	LED_NOT_INIT,
	LED_INVALID_PORT,
	LED_INVALID_PIN
}EN_LED_error_t;
	
	
EN_LED_error_t LED_init(ST_LED_t*);
EN_LED_error_t LED_ON(ST_LED_t*);
EN_LED_error_t LED_OFF(ST_LED_t*);
EN_LED_error_t LED_toggle(ST_LED_t*);





#endif /* LED_H_ */