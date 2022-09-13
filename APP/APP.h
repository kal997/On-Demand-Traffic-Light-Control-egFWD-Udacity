/*
 * APP.h
 *
 * Created: 9/8/2022 7:30:58 PM
 *  Author: KHALED
 */ 


#ifndef APP_H_
#define APP_H_


#include "../ECUL/LED/LED.h"
#include "../MCAL/External_interrupt/External_interrupt.h"


/***********************************************************************************************************************/
/*********************************************        CONFIGURATIONS      **********************************************/
/***********************************************************************************************************************/

#define PEDESTRIAN_BUTTON EXT_INT0
#define CAR_RED_LED       PIN2
#define CAR_GREEN_LED     PIN0
#define CAR_YELLOW_LED    PIN1

#define CAR_RED_PORT      PORT_A
#define CAR_GREEN_PORT    PORT_A
#define CAR_YELLOW_PORT   PORT_A

#define PED_RED_LED       PIN2
#define PED_GREEN_LED     PIN0
#define PED_YELLOW_LED    PIN1
		
#define PED_RED_PORT      PORT_B
#define PED_GREEN_PORT    PORT_B
#define PED_YELLOW_PORT   PORT_B



/***********************************************************************************************************************/
/***************************************        MACROS AND TYPEDEF       ***********************************************/
/***********************************************************************************************************************/

#define PB_PRESSED 1
#define PB_NOT_PRESSED 0
typedef enum {
	PEDESTRIAN_MODE_1,
	PEDESTRIAN_MODE_2,
	NORMAL_MODE
}EN_trafficLightMode_t;
typedef enum {
	RED_LIGHTS_ON,
	YELLOW_LIGHTS_ON,
	GREEN_LIGHTS_ON,
}EN_trafficLightStatus_t;



typedef struct {
	EN_EXT_error_t pedButtonSenseControlErr;
	EN_EXT_error_t pedButtonCallBackFunctionErr;
	EN_EXT_error_t pedButtonInterruptEnableErr;
	
	EN_LED_error_t pedRedLedErr;
	EN_LED_error_t pedYellowLedErr;
	EN_LED_error_t pedGreenLedErr;
	
	EN_LED_error_t carRedLedErr;
	EN_LED_error_t carYellowLedErr;
	EN_LED_error_t carGreenLedErr;
	
}ST_APP_init_error_t;





/***********************************************************************************************************************/
/**********************************        APPLICATION INTERFACE FUNCTIONS       ***************************************/
/***********************************************************************************************************************/

void APP_init(ST_APP_init_error_t* AppinitErrPtr);
void APP_start();








#endif /* APP_H_ */