/*
 * LED_test.c
 *
 * Created: 9/12/2022 10:44:23 PM
 *  Author: KHALED
 */ 

#include "LED_test.h"
#include "../../ECUL/LED/LED.h"
#define F_CPU 8000000UL
#include <util/delay.h>
void ledToggleTest(void)
{
	ST_LED_t led1={PORT_A, PIN0}, led2 = {PORT_A, PIN1};
	EN_LED_error_t led2err = LED_init(&led2) , led1err =  LED_init(&led1);
	
	if (led1err == LED_OK)	LED_ON(&led1);
	if (led1err == LED_OK)	LED_ON(&led2);
	
	s8 cnt = 5;
	while (cnt--)
	{
		_delay_ms(500);
		LED_toggle(&led1);
		LED_toggle(&led2);
	}
	LED_ON(&led1);
	LED_ON(&led2);

}

void ledInitTest(void)
{
	ST_LED_t led1={PORT_A, PIN0}, led2 = {PORT_A, PIN1}, errLed = {PORT_A, PIN2};
	EN_LED_error_t led1err =  LED_init(&led1), led2err = LED_init(&led2);
	
	if (led1err == LED_OK)LED_ON(&led1);
	if (led2err == LED_OK)LED_ON(&led2);
	
}

