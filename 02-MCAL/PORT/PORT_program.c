#include "Std_Types.h"
#include "Mcu_Hw.h"

#include "PORT_interface.h"
#include "PORT_private.h"
#include "PORT_config.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define CHANNEL_SIZE_IN_PORT               8u
#define MAX_NUMBER_OF_GPIO_PORTS           6u
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const uint32 Port_BaseAddr[MAX_NUMBER_OF_GPIO_PORTS] = {GPIO_APB_BASE_ADDRESS_A,
	                                                           GPIO_APB_BASE_ADDRESS_B,
	                                                           GPIO_APB_BASE_ADDRESS_C,
	                                                           GPIO_APB_BASE_ADDRESS_D,
	                                                           GPIO_APB_BASE_ADDRESS_E,
	                                                           GPIO_APB_BASE_ADDRESS_F};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Port_Init ( const Port_ConfigType* ConfigPtr )        
* \Description     : Initializes the Port Driver module.                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr       Pointer to configuration set.                     
* \Parameters (out): None                                                      
* \Return value:   : None  
*                                                                      
*******************************************************************************/
void Port_Init ( const Port_ConfigType* ConfigPtr )
{
	Port_PinType                locPinId;
	Port_PinDirectionType       locPinDir;
	Port_PinModeType            locPinMode;
	Port_PinOutputCurrentType   locCurrentStrength;
	Port_PinInternalAttachType  locInternalAttach;
	Port_PinExternalIntType     locExternalInt;
	uint8 PortIndex,PinIndex,i;
	uint32 PortBaseAddr;
	
	for(i=0;i<PORT_ACTIVATED_CHANNELS_SIZE;i++)
	{
		locPinId             = ConfigPtr[i].pinId;
		locPinDir            = ConfigPtr[i].pinDir;
		locPinMode           = ConfigPtr[i].pinMode;
		locCurrentStrength   = ConfigPtr[i].currentStrength;
		locInternalAttach    = ConfigPtr[i].internalAttach;
		locExternalInt       = ConfigPtr[i].externalInt;
		
		PortIndex    = locPinId / CHANNEL_SIZE_IN_PORT ;
		PinIndex     = locPinId % CHANNEL_SIZE_IN_PORT ;
        PortBaseAddr = Port_BaseAddr[PortIndex] ;
		
		GPIODIR(PortBaseAddr) |= (locPinDir<< PinIndex) ; 
		
		
		
		
	}
	
	
}


/*FOR PORT_Lcfg.c*/

const Port_ConfigType Port_Config[PORT_ACTIVATED_CHANNELS_SIZE]=
{
	/* pinId           pinDir          pinMode                     currentStrength        internalAttach          externalInt*/
	{  Port_Pin_A2     ,PORT_PIN_IN   ,Port_PinMode_PA2_SSI0Clk    ,PORT_PIN_CURRENT_NA   ,PORT_ATTACH_PULLUP     ,PORT_EXT_INT_DISABLE},
	{  Port_Pin_B5     ,PORT_PIN_IN   ,Port_PinMode_X_DIO          ,PORT_PIN_CURRENT_NA   ,PORT_ATTACH_PULLDOWN   ,PORT_EXT_INT_DISABLE},
	{  Port_Pin_B7     ,PORT_PIN_OUT  ,Port_PinMode_X_DIO          ,PORT_PIN_CURRENT_8m   ,PORT_ATTACH_OPENDRAIN  ,PORT_EXT_INT_DISABLE}
	
};