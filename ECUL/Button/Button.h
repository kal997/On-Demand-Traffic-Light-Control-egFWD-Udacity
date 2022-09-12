/*
 * Button.h
 *
 * Created: 9/6/2022 5:34:45 PM
 *  Author: KHALED
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../MCAL/DIO/DIO_interface.h"
typedef struct ST_Button_config_t{
	EN_DIO_port_t buttonPort;
	EN_DIO_pin_t buttonPin;
	EN_DIO_pin_config_t buttonPinInputConfig;
	EN_DIO_state_t buttonState;
	}ST_Button_config_t;


typedef enum {
	BUTTON_OK,
	BUTTON_NOT_INIT,
	BUTTON_INVALID_PORT,
	BUTTON_INVALID_PIN,
	BUTTON_INVALID_PIN_CONFIG,

}EN_BUTTON_error_t;

EN_BUTTON_error_t Button_init(ST_Button_config_t*);
EN_BUTTON_error_t Button_getState(ST_Button_config_t*);





#endif /* BUTTON_H_ */