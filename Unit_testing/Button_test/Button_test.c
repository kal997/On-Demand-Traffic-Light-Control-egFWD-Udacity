/*
 * Button_test.c
 *
 * Created: 9/12/2022 11:00:44 PM
 *  Author: KHALED
 */ 
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../ECUL/LED/LED.h"
#include "../../ECUL/Button/Button.h"
#include "Button_test.h"

#define F_CPU 8000000UL
#include <util/delay.h>
void buttonTest(void)
{
	ST_LED_t led1={PORT_D, PIN5}, led2 = {PORT_D, PIN6};
	EN_LED_error_t led1err =  LED_init(&led1), led2err = LED_init(&led2);


	EN_BUTTON_error_t getStateErr, exitButtonGetState;
	ST_Button_config_t button1, button2;
	button1.buttonPin = PIN2;
	button1.buttonPort = PORT_D;
	button1.buttonPinInputConfig = INPULL;
	
	button2.buttonPin = PIN3;
	button2.buttonPort = PORT_D;
	button2.buttonPinInputConfig = INPULL;

	
	EN_BUTTON_error_t buttonErr = Button_init(&button1);
	EN_BUTTON_error_t exitButtonErr = Button_init(&button2);
	
	while (1)	
	{	
		getStateErr  =  Button_getState(&button1);
		exitButtonGetState = Button_getState(&button2);
		if (getStateErr == BUTTON_OK)
		{
			if (button1.buttonState == HIGH)
			{
				LED_ON(&led1);
			}
			else
			{
				LED_OFF(&led1);
			}
		}
		if (exitButtonGetState == BUTTON_OK)
		{
			if (button2.buttonState == HIGH)
			{
				LED_ON(&led2);
				break;
			}
			
		}
		
	}
	
}
