#include "Std_Types.h"
#include "Mcu_Hw.h"

#include "Mcu_interface.h"
#include "Mcu_private.h"
#include "Mcu_config.h"

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Mcu.c
 *        \brief  Microcontroller Unit Driver
 *                
 *      \details The MCU driver provides services for basic microcontroller initialization, 
 *               Clock Control and reset
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define APINT_VECTKEY_FIELD_OFFSET   16u
#define SYSRESREQ_FIELD_OFFSET       2u
#define APINT_VECTKEY                0x05FA
#define MCU_PLL_OUTPUT_DIV2          200
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static const Mcu_ConfigType* Mcu_ConfigPtr = NULL_PTR;
static Mcu_StatusType Mcu_Status = MCU_NOT_INITIALIZED;


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
* \Syntax          : void Mcu_Init ( const Mcu_ConfigType* ConfigPtr )        
* \Description     : This service initializes the MCU driver.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr       Pointer to MCU driver configuration set.                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Mcu_Init ( const Mcu_ConfigType* ConfigPtr )
{
	Mcu_Status = MCU_INITIALIZED;
	Mcu_ConfigPtr = ConfigPtr;
}


/******************************************************************************
* \Syntax          : Mcu_RawResetType Mcu_GetResetRawValue( void )        
* \Description     : The service reads the reset type from the hardware, if supported.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                            
* \Parameters (out): None                                                      
* \Return value:   : Mcu_RawResetType   Reset raw value
*******************************************************************************/
Mcu_RawResetType Mcu_GetResetRawValue( void )
{
	Mcu_RawResetType resetCause = RESC;
	RESC = 0x0;
	return resetCause;
}

/******************************************************************************
* \Syntax          : void Mcu_PerformReset( void )        
* \Description     : The service performs a microcontroller reset.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                           
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
#if (MCU_PERFORM_RESET_API==STD_ON)

/*RESET CAUSE*/ 
void Mcu_PerformReset( void )
{
	/*Clear Reset Cause Register */
	RESC = 0x0;
	/*SET TO TRUE */
	/*Perform Reset */
	APINT = (APINT_VECTKEY<<APINT_VECTKEY_FIELD_OFFSET) |
	        (1<<SYSRESREQ_FIELD_OFFSET);
	
}
#endif  
/*MCU_PERFORM_RESET_API==STD_ON*/

/******************************************************************************
* \Syntax          : void Mcu_Init ( const Mcu_ConfigType* ConfigPtr )        
* \Description     : This service initializes the PLL and other MCU specific clock options.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ClockSetting       ClockSetting.                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType 
*******************************************************************************/

Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting )
{
	Std_ReturnType ret = E_NOT_OK;
	uint8 i, locGateRegOffset,locGateBitOffset;
	uint8 locSourceFreq_MHz;
	volatile uint32 xTest;
	
	if(Mcu_Status == MCU_INITIALIZED)
	{
	    /*Enable Configured Pripherals Gates */
		/*User Should Change It From Config_Type */ 
		/* WORD_LENGTH_BYTES = 4 in PlatformsTypes.h */ 
        /* WORD_LENGTH_BITS =  32 in PlatformsTypes.h */ 
        /*Global Func IN mcu_hw.h :#define GET_HWREG(BaseAddr,RegOffset)      *((volatile uint32*)(BaseAddr+RegOffset))*/ 

	 for(i=0;i<MCU_ACTIVATED_CLOCK_GATES_SIZE;i++)
	    {
	    	locGateRegOffset = (Mcu_ActivatedClockGates[i] / 10) * WORD_LENGTH_BYTES ;
	    	locGateBitOffset = Mcu_ActivatedClockGates[i] % 10 ;
	    	GET_HWREG(SYSCTR_RCG_BASE_ADDR,locGateRegOffset ) |= (1<<locGateBitOffset);	
	    }
	        RCC.B.OSCSRC = Mcu_ConfigPtr[ClockSetting].ClockSource ;
	    
	    /* Calculate SYS_DIV Value */
	    
	    if(Mcu_ConfigPtr[ClockSetting].PllUse == ENABLE)
	    {
	    	/*Enable PLL*/
	    	RCC.B.PWRDN = 0x0;
			
	    	xTest = (MCU_PLL_OUTPUT_DIV2 / (Mcu_ConfigPtr[ClockSetting].Freq_KHz/1000))-1;	
	    	RCC.B.SYSDIV = (MCU_PLL_OUTPUT_DIV2 / (Mcu_ConfigPtr[ClockSetting].Freq_KHz/1000))-1;	
	    }
	    else
	    {
	    	if (Mcu_ConfigPtr[ClockSetting].ClockSource == MCU_CLOCK_SOURCE_LFIOSC)
	    	{
	    		RCC.B.SYSDIV = 0x0;
	    	}
	    	else
	    	{
	    		if(Mcu_ConfigPtr[ClockSetting].ClockSource == MCU_CLOCK_SOURCE_MOSC)
	            {
	            	RCC.B.MOSCDIS = 0x0;
	            	RCC.B.XTAL = MCU_XTAL_CLOCK_FREQ_MHZ ; /*TODO : The value need to be mapped */
	    	    	locSourceFreq_MHz = MCU_XTAL_CLOCK_FREQ_MHZ;
	            }
	    	    else if (Mcu_ConfigPtr[ClockSetting].ClockSource == MCU_CLOCK_SOURCE_PIOSC)
	    	    {
	    	    	locSourceFreq_MHz = 16;
	    	    	
	    	    }
	    	    else if (Mcu_ConfigPtr[ClockSetting].ClockSource == MCU_CLOCK_SOURCE_PIOSC_Div4)
	    	    {
	    	    	locSourceFreq_MHz = 4;
	    	    	
	    	    }
				RCC.B.SYSDIV = (locSourceFreq_MHz / (Mcu_ConfigPtr[ClockSetting].Freq_KHz/1000))-1;	
	    	}	
	    }
        ret = E_OK;
    }
	return ret;
}

/******************************************************************************
* \Syntax          : Std_ReturnType Mcu_DistributePllClock( void )        
* \Description     : This service activates the PLL clock to the MCU clock distribution.                                                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                            
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType 
*                    E_OK: Command has been accepted
*                    E_NOT_OK: Command has not been accepted
*******************************************************************************/
Std_ReturnType Mcu_DistributePllClock( void )
{
	Std_ReturnType ret = E_NOT_OK ;
	
	/*Check if PLL is Enabled 
	  Write 0               */
	if(RCC.B.PWRDN == 0)
	{
		/*Check if PLL locked */
	    if(Mcu_GetPllStatus() == MCU_PLL_LOCKED)
	    {
	    	/* Distrubute PLL */
	        RCC.B.BYPASS = 1;
			ret = E_OK;
        }
	}
	return ret;
}

/******************************************************************************
* \Syntax          : Mcu_PllStatusType Mcu_GetPllStatus        
* \Description     : This service provides the lock status of the PLL.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : Mcu_PllStatusType  PLL Status
*******************************************************************************/
Mcu_PllStatusType Mcu_GetPllStatus( void )
{
	return PLLSTAT;
}

/* FOR MCU Lcfg.c*/
#define MCU_CLOCK_GATE_GPIOA     20u
#define MCU_CLOCK_GATE_GPIOB     21u
#define MCU_CLOCK_GATE_GPIOE     24u


#define MCU_CLOCK_GATE_WD0       00u
#define MCU_CLOCK_GATE_WD1       01u

#define Mcu_Clock_0        0
#define Mcu_Clock_1        1
#define Mcu_Clock_2        2


uint8 Mcu_ActivatedClockGates[MCU_ACTIVATED_CLOCK_GATES_SIZE]=
{
	MCU_CLOCK_GATE_GPIOA,
	MCU_CLOCK_GATE_GPIOB,
	MCU_CLOCK_GATE_GPIOE,
	MCU_CLOCK_GATE_WD0

	
};

const Mcu_ConfigType McuConfig[MCU_CLOCK_SETTINGS_SIZE]=
{
	/*ClockSettingID*/ /* ClockSource                        PllUse     Freq_KHz  */
	/* 0            */ {  MCU_CLOCK_SOURCE_MOSC             ,ENABLE     ,25000},
	/* 1            */ {  MCU_CLOCK_SOURCE_PIOSC            ,DISABLE    ,16000},
};

