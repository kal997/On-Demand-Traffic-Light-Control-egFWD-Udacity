#include "APP/APP.h"

int main(void)
{
	
	ST_APP_init_error_t appInitErr;
	
	APP_init(&appInitErr);
	if ((appInitErr.carGreenLedErr == LED_OK)
	&& (appInitErr.carRedLedErr == LED_OK)
	&& (appInitErr.carYellowLedErr == LED_OK)
	&& (appInitErr.pedYellowLedErr == LED_OK)
	&& (appInitErr.pedRedLedErr == LED_OK)
	&& (appInitErr.pedGreenLedErr == LED_OK)
	&& (appInitErr.pedButtonSenseControlErr == EXT_INT_OK)
	&& (appInitErr.pedButtonInterruptEnableErr == EXT_INT_OK)
	&& (appInitErr.pedButtonCallBackFunctionErr == EXT_INT_OK))
	{
		APP_start();
	}
	else
	{
		// Error trap
		while (1);
	}
	return 0;
}