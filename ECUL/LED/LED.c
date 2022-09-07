/*
 * LED.c
 *
 * Created: 9/6/2022 4:54:40 PM
 *  Author: KHALED
 */ 
#include "LED.h"
void LED_init(ST_LED_t* ledPtr)
{
	ST_DIO_config_t dioPinConfig = {ledPtr->ledPort, ledPtr->ledPin, OUTPUT};
	DIO_init(&dioPinConfig);
}
void LED_ON(ST_LED_t* ledPtr)
{
	DIO_write(ledPtr->ledPort, ledPtr->ledPin, HIGH);
}
void LED_OFF(ST_LED_t* ledPtr)
{
	DIO_write(ledPtr->ledPort,  ledPtr->ledPin, LOW);
}
void LED_toggle(ST_LED_t* ledPtr)
{
	DIO_toggle(ledPtr->ledPort, ledPtr->ledPin);
}
