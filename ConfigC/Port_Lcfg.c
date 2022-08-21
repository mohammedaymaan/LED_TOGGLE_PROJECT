#include "Std_Types.h"
#include "Port.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
const Port_ConfigType Port_Config[PORT_ACTIVATED_CHANNELS_SIZE]=
{
	/* pinId           pinDir          pinMode                     currentStrength        internalAttach          externalInt*/
	{  Port_Pin_A2     ,PORT_PIN_IN   ,Port_PinMode_PA2_SSI0Clk    ,PORT_PIN_CURRENT_NA   ,PORT_ATTACH_PULLUP     ,PORT_EXT_INT_DISABLE},
	{  Port_Pin_B5     ,PORT_PIN_IN   ,Port_PinMode_X_DIO          ,PORT_PIN_CURRENT_NA   ,PORT_ATTACH_PULLDOWN   ,PORT_EXT_INT_DISABLE},
	{  Port_Pin_B7     ,PORT_PIN_OUT  ,Port_PinMode_X_DIO          ,PORT_PIN_CURRENT_8m   ,PORT_ATTACH_OPENDRAIN  ,PORT_EXT_INT_DISABLE}
	
};