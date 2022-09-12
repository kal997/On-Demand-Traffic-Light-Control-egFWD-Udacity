/*
 * LED.c
 *
 * Created: 9/6/2022 4:54:40 PM
 *  Author: KHALED
 */ 
#include "LED.h"
EN_LED_error_t LED_init(ST_LED_t* ledPtr)
{
	EN_LED_error_t ledInitErr = LED_OK;
	
	ST_DIO_config_t dioPinConfig = {ledPtr->ledPort, ledPtr->ledPin, OUTPUT};
	EN_DIO_error_t dioInitErr= DIO_init(&dioPinConfig);
	switch (dioInitErr)
	{
		case DIO_INVALID_PORT:
			ledInitErr = LED_INVALID_PORT;
			break;
		case DIO_INVALID_PIN:
			ledInitErr = LED_INVALID_PIN;
			break;
		default:
		break;
	}
	return ledInitErr;
}
EN_LED_error_t LED_ON(ST_LED_t* ledPtr)
{	
	EN_LED_error_t ledOnErr = LED_OK;

	EN_DIO_error_t dioWriteErr = DIO_write(ledPtr->ledPort, ledPtr->ledPin, HIGH);
	switch (dioWriteErr)
	{
		case DIO_INVALID_PORT:
			ledOnErr = LED_INVALID_PORT;
			break;
		case DIO_INVALID_PIN:
			ledOnErr = LED_INVALID_PIN;
			break;
		case DIO_NOT_INITIALIZED:
			ledOnErr = LED_NOT_INIT;
			break;
		
		default:
		break;
	}
	return ledOnErr;
}
EN_LED_error_t LED_OFF(ST_LED_t* ledPtr)
{
	
	EN_LED_error_t ledOffErr = LED_OK;

	EN_DIO_error_t dioWriteErr = DIO_write(ledPtr->ledPort, ledPtr->ledPin, LOW);
	switch (dioWriteErr)
	{
		case DIO_INVALID_PORT:
		ledOffErr = LED_INVALID_PORT;
		break;
		case DIO_INVALID_PIN:
		ledOffErr = LED_INVALID_PIN;
		break;
		case DIO_NOT_INITIALIZED:
		ledOffErr = LED_NOT_INIT;
		break;
		default:
		break;
	}
	return ledOffErr;
}
EN_LED_error_t LED_toggle(ST_LED_t* ledPtr)
{
	EN_LED_error_t ledToggleErr = LED_OK;

	EN_DIO_error_t dioToggleErr = DIO_toggle(ledPtr->ledPort, ledPtr->ledPin);
	switch (dioToggleErr)
	{
		case DIO_INVALID_PORT:
		ledToggleErr = LED_INVALID_PORT;
		break;
		case DIO_INVALID_PIN:
		ledToggleErr = LED_INVALID_PIN;
		break;
		case DIO_NOT_INITIALIZED:
		ledToggleErr = LED_NOT_INIT;
		break;
		default:
		break;
	}
	return ledToggleErr;
	
	
}
