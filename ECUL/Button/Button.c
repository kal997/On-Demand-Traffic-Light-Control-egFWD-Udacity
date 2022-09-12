/*
 * Button.c
 *
 * Created: 9/6/2022 5:34:58 PM
 *  Author: KHALED
 */ 
#include "Button.h"

EN_BUTTON_error_t Button_init(ST_Button_config_t* buttonPtr)
{
	EN_BUTTON_error_t buttonInitErr = BUTTON_OK;
	ST_DIO_config_t buttonConfig = {buttonPtr->buttonPort, buttonPtr->buttonPin, buttonPtr->buttonPinInputConfig};
	EN_DIO_error_t dioErr =  DIO_init(&buttonConfig);
	switch (dioErr)
	{
		case DIO_INVALID_PIN:
			buttonInitErr = BUTTON_INVALID_PIN;
			break;
		case DIO_INVALID_PORT:
			buttonInitErr = BUTTON_INVALID_PORT;
			break;
		case DIO_INVALID_PIN_CONFIG:
			buttonInitErr = BUTTON_INVALID_PIN_CONFIG;
			break;
		case DIO_NOT_INITIALIZED:
			buttonInitErr = BUTTON_NOT_INIT;
			break;
		default:
			break;
	}
	return buttonInitErr;
	
}
EN_BUTTON_error_t Button_getState(ST_Button_config_t* buttonPtr)
{
	EN_BUTTON_error_t buttonGetStateErr = BUTTON_OK;
	EN_DIO_state_t state;
	EN_DIO_error_t dioReadErr = DIO_read(buttonPtr->buttonPort, buttonPtr->buttonPin, &state);
	switch (dioReadErr)
	{
		case DIO_INVALID_PIN:
			buttonGetStateErr = BUTTON_INVALID_PIN;
			break;
		case DIO_INVALID_PORT:
			buttonGetStateErr = BUTTON_INVALID_PORT;
			break;
		case DIO_INVALID_PIN_CONFIG:
			buttonGetStateErr = BUTTON_INVALID_PIN_CONFIG;
			break;
		case DIO_NOT_INITIALIZED:
			buttonGetStateErr = BUTTON_NOT_INIT;
			break;
		case DIO_OK:
			buttonPtr->buttonState = state;
			break;
		default:
			break;
	}
	return buttonGetStateErr;
}