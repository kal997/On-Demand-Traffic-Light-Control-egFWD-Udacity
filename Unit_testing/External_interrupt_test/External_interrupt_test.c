/*
 * External_interrupt_test.c
 *
 * Created: 9/12/2022 11:16:06 PM
 *  Author: KHALED
 */ 

#include "../../ECUL/LED/LED.h"
#include "../../ECUL/Button/Button.h"
#include "../../MCAL/External_interrupt/External_interrupt.h"
#include "External_interrupt_test.h"
u8 flag = 0;
void externalInterruptISR(void)
{
	flag ^= 1;

}
void externalInterruptInitTest(void)
{

	ST_LED_t led1={PORT_D, PIN5}, led2 = {PORT_D, PIN6}, errLed = {PORT_D, PIN7};
	EN_LED_error_t led1err =  LED_init(&led1), led2err = LED_init(&led2);
	
	

	EN_EXT_error_t err = EXT_InterruptSenseControl(EXT_INT0, RISING_EDGE);
	switch (err)
	{
		case EXT_INT_INVALID_SOURCE:
			LED_ON(&led1);
			break;
		case EXT_INT_INVALID_SENSE_CONTROL:
			LED_ON(&led2);
			break;
		case EXT_INT_OK:
			LED_ON(&led1);
			LED_ON(&led2);
			break;
		default:
		break;
	}	

}


void externalInterruptTest(void)
{

	ST_LED_t led1={PORT_D, PIN5}, led2 = {PORT_D, PIN6};
	EN_LED_error_t led1err =  LED_init(&led1), led2err = LED_init(&led2);
	
	
	
	
	
	EN_BUTTON_error_t exitButtonGetState;
	ST_Button_config_t extButton;
	
	extButton.buttonPin = PIN3;
	extButton.buttonPort = PORT_D;
	extButton.buttonPinInputConfig = INPULL;

	
	EN_BUTTON_error_t exitButtonErr = Button_init(&extButton);
	EN_EXT_error_t err = EXT_InterruptSenseControl(EXT_INT0, RISING_EDGE);
	EXT_InterruptSetCallback(EXT_INT0, externalInterruptISR);
	EXT_InterruptEnable(EXT_INT0);
	sei();
	while (1)	
	{	
		exitButtonGetState = Button_getState(&extButton);
		if (flag == 1)
		{
			LED_toggle(&led1);
			flag = 0;
		}
		if (exitButtonGetState == BUTTON_OK)
		{
			if (extButton.buttonState == HIGH)
			{
				LED_ON(&led2);
				EXT_InterruptDisable(EXT_INT0);
				break;
			}
			
		}
		
	}
	

}

