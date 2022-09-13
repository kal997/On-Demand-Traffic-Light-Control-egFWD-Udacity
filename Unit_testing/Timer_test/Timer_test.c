/*
 * Timer_test.c
 *
 * Created: 9/12/2022 11:34:05 PM
 *  Author: KHALED
 */ 


#include "../../ECUL/LED/LED.h"
#include "../../ECUL/Button/Button.h"
#include "../../MCAL/Timer/Timer.h"
#include "Timer_test.h"


void timerTest(void)
{
	ST_LED_t led1={PORT_A, PIN0}, led2 = {PORT_A, PIN1};
	EN_LED_error_t led1err =  LED_init(&led1), led2err = LED_init(&led2);

	s8 cnt = 5;
	while (cnt--)
	{
		LED_ON(&led2);
		timerDelay_1s();
		LED_OFF(&led2);
		timerDelay_1s();
	}
	
	

	
			
}


void timerDelay_1s(void)
{
	//1. defining overFlowCounter to hold the state of the overflows
	u8 overFlowCounter = 0;
	//2. making sure that timer is stopped
	TIMER0_stop();
	//3. according to the calculations, we need 30 overflow and 132 ticks to delay 1sec, so the initial ticks are 124
	TIMER0_setTicks(256-132);
	//4. configuring the timer
	ST_TIMER0_config_t timerConfigPtr = {TIMER0_NORMAL_MODE, TIMER0_SCALER_1024};
	TIMER0_Init(&timerConfigPtr);
	
	while (overFlowCounter<31)
	{
		//5. if the overflow flag is high, thats mean that 256 ticks are elapsed or an interrupt happened due to pedestrian button
		while(TIMER0_OV_checkFlag() == TIMER0_FLAG_LOW);
		overFlowCounter++;
		TIMER0_OV_clearFlag();
		TIMER0_setTicks(0);
	}
	//6. stop the timer
	TIMER0_stop();
	//7. free the timer for usage again
	TIMER0_deInit();
}