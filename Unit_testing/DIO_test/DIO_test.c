/*
 * DIO_test.c
 *
 * Created: 9/12/2022 8:31:37 PM
 *  Author: KHALED
 */ 

/*
 * On-Demand-Traffic-Light-Control.c
 *
 * Created: 9/6/2022 1:43:45 PM
 * Author : KHALED
 */



#define F_CPU 8000000UL
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_interface.h"



void dioInitTest1(void)
{
	ST_DIO_config_t led1  = {PORT_D,PIN5, OUTPUT};
	ST_DIO_config_t led2  = {PORT_D,PIN6, OUTPUT};
	ST_DIO_config_t indicationLed  = {PORT_D,PIN7, OUTPUT};
	
	DIO_init(&indicationLed);
	
	
	
	
	
	DIO_init(&led1);
	DIO_init(&led2);
	
	EN_DIO_error_t err1 = DIO_write(led1.port, led1.pin, HIGH);
	EN_DIO_error_t err2 =  DIO_write(led2.port, led2.pin, HIGH);
	if (err2 == DIO_NOT_INITIALIZED)
	{
		DIO_write(indicationLed.port, indicationLed.pin, HIGH);
	}
	
}
void dioInitTest2(void)
{
	ST_DIO_config_t led1  = {PORT_D,PIN5, OUTPUT};
	ST_DIO_config_t led2  = {PORT_D,PIN6, OUTPUT};
	ST_DIO_config_t indicationLed  = {PORT_D,PIN7, OUTPUT};
	DIO_init(&indicationLed);
	
	
	
	DIO_init(&led1);
	//DIO_init(&led2);
	
	EN_DIO_error_t err1 = DIO_write(led1.port, led1.pin, HIGH);
	EN_DIO_error_t err2 =  DIO_write(led2.port, led2.pin, HIGH);
	if (err2 == DIO_NOT_INITIALIZED)
	{
		DIO_write(indicationLed.port, indicationLed.pin, HIGH);
	}
	
}
void dioReadTest(void)
{
	ST_DIO_config_t dioButton = {PORT_D, PIN2, INPULL};
	ST_DIO_config_t dioButtonExit = {PORT_D, PIN3, INPULL};

	ST_DIO_config_t dioLed  = {PORT_D,PIN5, OUTPUT};
	EN_DIO_state_t button1State, button2State;
	DIO_init(&dioButton);
	DIO_init(&dioLed);
	DIO_init(&dioButtonExit);
	
	while (1)
	{
		DIO_read(dioButton.port, dioButton.pin, &button1State);
		DIO_read(dioButtonExit.port, dioButtonExit.pin, &button2State);
		
		if (button1State == HIGH)
		{
			DIO_write(dioLed.port, dioLed.pin, HIGH);
		}
		else
		{
			DIO_write(dioLed.port, dioLed.pin, LOW);
		}
		

		if (button2State == HIGH)
		{
			
			break;
		}
		
	}


	
}
void dioWriteTest(void)
{
	ST_DIO_config_t leds[32];
	ST_DIO_config_t	led;
	u8 port, pin;
	for (port = 0 ; port<4 ; port++)
	{
		for (pin = 0; pin < 8; pin++)
		{
			led.pin = pin;
			led.port = port;
			led.pin_config = OUTPUT	;
			
			leds[(port*8)+pin] = led;
			DIO_init(&led);
		}
	}
	for (pin = 0 ; pin<32 ; pin++)
	{
		DIO_write(leds[pin].port, leds[pin].pin, HIGH);
		
	}

}



