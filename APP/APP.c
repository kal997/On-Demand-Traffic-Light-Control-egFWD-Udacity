/*
 * APP.c
 *
 * Created: 9/8/2022 7:31:13 PM
 *  Author: KHALED
 */ 

#include "APP.h"
/***********************************************************************************************************************/
/*********************************             GLOBAL VARIABLES         ************************************************/
/***********************************************************************************************************************/

// Cars Traffic lights
ST_LED_t carsRedLedConfig = {CAR_RED_PORT, CAR_RED_LED}, carsYellowLedConfig = {CAR_YELLOW_PORT, CAR_YELLOW_LED}, carsGreenLedConfig = {CAR_GREEN_PORT, CAR_GREEN_LED};
// Pedestrian Traffic lights configuration
ST_LED_t pedRedLedConfig = {PED_RED_PORT, PED_RED_LED}, pedYellowLedConfig = {PED_YELLOW_PORT, PED_YELLOW_LED}, pedGreenLedConfig = {PED_GREEN_PORT, PED_GREEN_LED};

u8 isPedestrainButtonPressed =  PB_NOT_PRESSED;
																				 


/***********************************************************************************************************************/
/***************************************         STATIC FUNCTIONS       ************************************************/
/***********************************************************************************************************************/

static void timerDelay_1s(void)
{
	u8 overFlowCounter = 0;
	TIMER0_stop();
	TIMER0_setTicks(256-132);
	ST_TIMER0_config_t timerConfigPtr = {TIMER0_NORMAL_MODE, TIMER0_SCALER_1024};
	TIMER0_Init(&timerConfigPtr);
	while (overFlowCounter<31)
	{
		while(TIMER0_OV_checkFlag() == TIMER0_LOW);
		
		if (isPedestrainButtonPressed == PB_PRESSED)
		{
			break;
		}
		overFlowCounter++;
		TIMER0_OV_clearFlag();
		TIMER0_setTicks(0);
	}
	TIMER0_stop();
}
static void timerDelay_5s(void)
{
	u8 overFlowCounter = 0;
	TIMER0_stop();
	TIMER0_setTicks(256-150);
	ST_TIMER0_config_t timerConfigPtr = {TIMER0_NORMAL_MODE, TIMER0_SCALER_1024};
	TIMER0_Init(&timerConfigPtr);
	while (overFlowCounter<153)
	{
		while(TIMER0_OV_checkFlag() == TIMER0_LOW);
		if (isPedestrainButtonPressed == PB_PRESSED)
		{
			break;
		}
		overFlowCounter++;
		TIMER0_OV_clearFlag();
		TIMER0_setTicks(0);
	}
	TIMER0_stop();
}

static void deactivatePedestrianButton(void)
{
	EXT_InterruptDisable(PEDESTRIAN_BUTTON);
}
static void activatePedestrianButton(void)
{
	EXT_InterruptEnable(PEDESTRIAN_BUTTON);
}

static EN_trafficLightStatus_t trafficLightsNormalMode(void)
{
	EN_trafficLightStatus_t carsTrafficLightState;
	while (1)
	{
		
		if (isPedestrainButtonPressed == PB_NOT_PRESSED)
		{
			LED_ON(&carsGreenLedConfig);
			carsTrafficLightState = GREEN_LIGHTS_ON;
			timerDelay_5s();
			LED_OFF(&carsGreenLedConfig);
		}
		else break;
		
		if (isPedestrainButtonPressed == PB_NOT_PRESSED)
		{
			LED_ON(&carsYellowLedConfig);
			carsTrafficLightState = YELLOW_LIGHTS_ON;
			for(int i = 0 ; i<5 && isPedestrainButtonPressed == PB_NOT_PRESSED; i++)
			{
				timerDelay_1s();
				LED_toggle(&carsYellowLedConfig);
			}
			LED_OFF(&carsYellowLedConfig);
		}
		else break;
		
		if(isPedestrainButtonPressed == PB_NOT_PRESSED)
		{
			LED_ON(&carsRedLedConfig);
			carsTrafficLightState = RED_LIGHTS_ON;
			timerDelay_5s();
			LED_OFF(&carsRedLedConfig);
		}
		else break;
		
	}
	
	
	isPedestrainButtonPressed = PB_NOT_PRESSED; // in order to execute delay functions properly
	return carsTrafficLightState; // Pedestrian button is pressed
	
}
static EN_trafficLightMode_t getPedestrianMode(EN_trafficLightStatus_t interruptedNormalMode)
{
	EN_trafficLightMode_t currentPedestrianMode;
	switch (interruptedNormalMode)
	{
		case RED_LIGHTS_ON:
			currentPedestrianMode = PEDESTRIAN_MODE_1;
			break;
		case YELLOW_LIGHTS_ON:
			currentPedestrianMode = PEDESTRIAN_MODE_2;
			break;
		case GREEN_LIGHTS_ON:
			currentPedestrianMode = PEDESTRIAN_MODE_2;
			break;
	}
	return currentPedestrianMode;
}
static void trafficLightsPedestrianMode(EN_trafficLightMode_t currentPedestrianMode)
{
	switch (currentPedestrianMode)
	{
		case PEDESTRIAN_MODE_1:
			LED_ON(&carsRedLedConfig);
			LED_ON(&pedGreenLedConfig);
			timerDelay_5s();
			break;
		case PEDESTRIAN_MODE_2:
			LED_ON(&pedRedLedConfig);
			LED_ON(&carsGreenLedConfig);
			LED_ON(&pedYellowLedConfig);
			LED_ON(&carsYellowLedConfig);
			for(int i = 0 ; i<5 ; i++)
			{
				timerDelay_1s();
				LED_toggle(&pedYellowLedConfig);
				LED_toggle(&carsYellowLedConfig);

				
			}
			LED_OFF(&pedRedLedConfig);
			LED_OFF(&carsGreenLedConfig);
			LED_OFF(&pedYellowLedConfig);
			LED_OFF(&carsYellowLedConfig);
			
			LED_ON(&pedGreenLedConfig);
			LED_ON(&carsRedLedConfig);
			timerDelay_5s();
			break;
		default:
		break;
	}
	LED_OFF(&carsRedLedConfig);
	
	LED_ON(&pedYellowLedConfig);
	LED_toggle(&carsYellowLedConfig);
	LED_ON(&carsRedLedConfig);
	for(int i = 0 ; i<5 ; i++)
	{
		timerDelay_1s();
		LED_toggle(&carsYellowLedConfig);
		LED_toggle(&pedYellowLedConfig);
	}
	
	LED_OFF(&pedGreenLedConfig);
	LED_OFF(&pedRedLedConfig);
	LED_OFF(&carsRedLedConfig);
	
}

static void pedstrianButtonPressed(void)
{
	
	isPedestrainButtonPressed = PB_PRESSED;
	TIMER0_OV_clearFlag();
	
}


/***********************************************************************************************************************/
/***************************************        APPLICATION FUNCTIONS       ********************************************/
/***********************************************************************************************************************/



void APP_init()
{
	// Pedestrian button initialization
	sei();
	EXT_InterruptSenseControl(PEDESTRIAN_BUTTON, RISING_EDGE);
	EXT_InterruptSetCallback(PEDESTRIAN_BUTTON, pedstrianButtonPressed);
	EXT_InterruptEnable(PEDESTRIAN_BUTTON);
	
	// Cars traffic lights initialization
	LED_init(&carsRedLedConfig);
	LED_init(&carsYellowLedConfig);
	LED_init(&carsGreenLedConfig);


	// Pedestrian traffic lights initialization
	LED_init(&pedRedLedConfig);
	LED_init(&pedYellowLedConfig);
	LED_init(&pedGreenLedConfig);

}


void APP_start()
{
	EN_trafficLightStatus_t interruptedNormalModeState;
	EN_trafficLightMode_t pedMode;
	
	while(1)
	{
		interruptedNormalModeState = trafficLightsNormalMode();
		deactivatePedestrianButton();
		pedMode =  getPedestrianMode(interruptedNormalModeState);
		trafficLightsPedestrianMode(pedMode);	
		activatePedestrianButton();
	}
	
}













