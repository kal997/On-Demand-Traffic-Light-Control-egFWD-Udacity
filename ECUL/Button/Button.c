/*
 * Button.c
 *
 * Created: 9/6/2022 5:34:58 PM
 *  Author: KHALED
 */ 
#include "Button.h"

void Button_init(ST_Button_t* buttonPtr)
{
	ST_DIO_config_t buttonConfig = {buttonPtr->buttonPort, buttonPtr->buttonPin, buttonPtr->buttonPinInputConfig};
	DIO_init(&buttonConfig);
	
}
void Button_getState(ST_Button_t* buttonPtr)
{
	EN_DIO_state_t state;
	DIO_read(buttonPtr->buttonPort, buttonPtr->buttonPin, &state);
	buttonPtr->buttonState = state;
}