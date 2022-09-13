#include "APP.h"
#include "../MCAL/Timer/Timer.h"

/***********************************************************************************************************************/
/*********************************             GLOBAL VARIABLES         ************************************************/
/***********************************************************************************************************************/

// Cars Traffic lights configurations
ST_LED_t carsRedLedConfig = {CAR_RED_PORT, CAR_RED_LED}, carsYellowLedConfig = {CAR_YELLOW_PORT, CAR_YELLOW_LED}, carsGreenLedConfig = {CAR_GREEN_PORT, CAR_GREEN_LED};
// Pedestrian Traffic lights configurations
ST_LED_t pedRedLedConfig = {PED_RED_PORT, PED_RED_LED}, pedYellowLedConfig = {PED_YELLOW_PORT, PED_YELLOW_LED}, pedGreenLedConfig = {PED_GREEN_PORT, PED_GREEN_LED};

u8 isPedestrainButtonPressed =  PB_NOT_PRESSED;
																				 

/***********************************************************************************************************************/
/***************************************         STATIC FUNCTIONS       ************************************************/
/***********************************************************************************************************************/

static void timerDelay_1s(void)
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
		//6. we check if the button if pressed
		if (isPedestrainButtonPressed == PB_PRESSED)
		{
			// break out of the overFlowCounter while loop
			break;
		}
		//7. if not pressed, continue
		overFlowCounter++;
		TIMER0_OV_clearFlag();
		TIMER0_setTicks(0);
	}
	//8. stop the timer
	TIMER0_stop();
	//9. free the timer for usage again
	TIMER0_deInit();
}
static void timerDelay_5s(void)
{
	//1. defining overFlowCounter to hold the state of the overflows
	u8 overFlowCounter = 0;
	//2. making sure that timer is stopped
	TIMER0_stop();
	//3. according to the calculations, we need 152 overflow and 150 tick to delay 5sec, so the initial ticks will equal 106
	TIMER0_setTicks(106);
	//4. configuring the timer
	ST_TIMER0_config_t timerConfigPtr = {TIMER0_NORMAL_MODE, TIMER0_SCALER_1024};
	TIMER0_Init(&timerConfigPtr);
	
	while (overFlowCounter<153)
	{
		//5. if the overflow flag is high, thats mean that 256 ticks are elapsed or an interrupt happened due to pedestrian button
		while(TIMER0_OV_checkFlag() == TIMER0_FLAG_LOW);
		//6. we check if the button if pressed
		if (isPedestrainButtonPressed == PB_PRESSED)
		{
			// break out of the overFlowCounter while loop
			break;
		}
		//7. if not pressed, continue
		overFlowCounter++;
		TIMER0_OV_clearFlag();
		TIMER0_setTicks(0);
	}
	//8. stop the timer
	TIMER0_stop();
	//9. free the timer for usage again
	TIMER0_deInit();
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
	// this variable holds the state of the cars traffic light.
	EN_trafficLightStatus_t carsTrafficLightState;
	while (1)
	{
		// checking if button is pressed or not, if not pressed, we will continue with the normal mode
		if (isPedestrainButtonPressed == PB_NOT_PRESSED)
		{
			LED_ON(&carsGreenLedConfig);
			carsTrafficLightState = GREEN_LIGHTS_ON;
			timerDelay_5s();
			LED_OFF(&carsGreenLedConfig);
		}
		else break; // if pressed, return the carsTrafficLightState
		
		// checking if button is pressed or not, if not pressed, we will continue with the normal mode
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
		else break; // if pressed, return the carsTrafficLightState
		
		// checking if button is pressed or not, if not pressed, we will continue with the normal mode
		if(isPedestrainButtonPressed == PB_NOT_PRESSED)
		{
			LED_ON(&carsRedLedConfig);
			carsTrafficLightState = RED_LIGHTS_ON;
			timerDelay_5s();
			LED_OFF(&carsRedLedConfig);
		}
		else break; // if pressed, return the carsTrafficLightState
	
		// checking if button is pressed or not, if not pressed, we will continue with the normal mode
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
		else break; // if pressed, return the carsTrafficLightState
		
		
	}
	
	
	isPedestrainButtonPressed = PB_NOT_PRESSED; // in order to execute delay functions properly, we have clear the flag
	return carsTrafficLightState; // if this function returns, thats mean that the Pedestrian button is pressed.
	
}
static EN_trafficLightMode_t getPedestrianMode(EN_trafficLightStatus_t interruptedNormalMode)
{
	// this variable will hold the pedestrian mode corresponding to the last state of cars traffic lights.
	EN_trafficLightMode_t currentPedestrianMode = PEDESTRIAN_MODE_1;
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
		default:
			break;
	}
	// returns the pedestrian mode to execute
	return currentPedestrianMode;
}
static void trafficLightsPedestrianMode(EN_trafficLightMode_t currentPedestrianMode)
{
	/*
	this function executes the given pedestrian mode PEDESTRIAN_MODE_1 or PEDESTRIAN_MODE_2.
	*/
	
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
	// this function will be called if the button is pressed.
	
	// set the isPedestrainButtonPressed flag to inform the delay function to break from the delay loop.
	isPedestrainButtonPressed = PB_PRESSED;
	// set the overflow flag to interrupt the ongoing delay.
	TIMER0_OV_clearFlag();
	
}


/***********************************************************************************************************************/
/***************************************        APPLICATION FUNCTIONS       ********************************************/
/***********************************************************************************************************************/



void APP_init(ST_APP_init_error_t* AppinitErrPtr)
{
	//1. enabling the global interrupt
	sei();
	
	//2. Pedestrian button initialization and getting initialization states
	AppinitErrPtr->pedButtonSenseControlErr = EXT_InterruptSenseControl(PEDESTRIAN_BUTTON, RISING_EDGE);
	AppinitErrPtr->pedButtonCallBackFunctionErr = EXT_InterruptSetCallback(PEDESTRIAN_BUTTON, pedstrianButtonPressed);
	AppinitErrPtr->pedButtonInterruptEnableErr = EXT_InterruptEnable(PEDESTRIAN_BUTTON);
	
	//3. Cars traffic lights initialization and getting initialization states
	AppinitErrPtr->carRedLedErr = LED_init(&carsRedLedConfig);
	AppinitErrPtr->carYellowLedErr = LED_init(&carsYellowLedConfig);
	AppinitErrPtr->carGreenLedErr = LED_init(&carsGreenLedConfig);


	//4. Pedestrian traffic lights initialization and getting initialization states
	AppinitErrPtr->pedRedLedErr = LED_init(&pedRedLedConfig);
	AppinitErrPtr->pedYellowLedErr = LED_init(&pedYellowLedConfig);
	AppinitErrPtr->pedGreenLedErr = LED_init(&pedGreenLedConfig);
}


void APP_start()
{
	EN_trafficLightStatus_t interruptedNormalModeState;
	EN_trafficLightMode_t pedMode;
	
	while(1)
	{
		//1. if trafficLightsNormalMode returns this means that the pedestrian button is pressed
		//2. we will assign the cars traffic lights last state to interruptedNormalModeState
		interruptedNormalModeState = trafficLightsNormalMode();
		//3. deactivating the pedestrian button, to execute the corresponding pedestrian mode.
		deactivatePedestrianButton();
		//4. getting the corresponding pedestrian mode to execute
		pedMode =  getPedestrianMode(interruptedNormalModeState);
		//5. executes the pedestrian mode
		trafficLightsPedestrianMode(pedMode);	
		//6. activates the pedestrian button again.
		activatePedestrianButton();
	}
	
}








