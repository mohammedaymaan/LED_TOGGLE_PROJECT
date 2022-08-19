#include "Std_Types.h"
#include "Mcu_Hw.h"


#include "GPT_interface.h"
#include "GPT_private.h"
#include "GPT_config.h"



static uint8 g_gptTimersMode[NUM_OF_GPT];                                            

static volatile Gpt_NotificationType g_gptChannelNotification[NUM_OF_GPT] = {       
                                                                                  



} 																				  
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

/*************************************************************************************************
* \Syntax          : void GPT_init (const Gpt_ConfigType* ConfigPtr)       
* \Description     : Enable each timer with the required configuration and start the predef timers
                    - mode 1 : periodic or one-shot.
                    - mode 2 : split or concatenate timers.
                    - prescaler : to set the clock for each timer.
                    - set the call back function and disable interrupts it at the beginning                               
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr   Pointer to struct to hold the configuration for each timer                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_init (const Gpt_ConfigType* ConfigPtr)
{
    uint8 i;
    Gpt_ChannelType chId;
    Gpt_ChannelModeType chMode;
    uint16 prescalerValue;

    for (i=0; i < NUM_OF_ACTIVATED_CHANNEL; i++)
    {
        chId                           = ConfigPtr[i].Channel;
        chMode                         = ConfigPtr[i].Mode;
        g_gptTimersMode[chId]          = ConfigPtr[i].TimerMode;
        prescalerValue                 = ConfigPtr[i].Prescaler;
        g_gptChannelNotification[chId] = ConfigPtr[i].GptNotification; 
        
        
        CLEAR_BIT(GPTMCTL(chId),TAEN);
        GPTMCFG(chId) = g_gptTimersMode[chId];
        CLEAR_BIT(GPTMTAMR(chId),TACDIR);
        
        if ( g_gptTimersMode[chId] == SPLIT_TIMERS )
        {
            if ( chId < 6 )
            {
                prescalerValue &= 0x00FF;
            }
            GPTMTAPR(chId) = prescalerValue;
        }

        if ( chMode == PERIODIC )
        {
           GPTMTAMR(chId) = ( GPTMTAMR(chId) & 0xFFFFFFFC ) | (1<<1);
        }
        else if ( chMode == ONESHOT )
        {
           GPTMTAMR(chId) = ( GPTMTAMR(chId) & 0xFFFFFFFE ) | (1<<0);
        }

        GPT_disableNotification(chId);
    }

#if ( GPT_PREDEF_TIMER_1US_16BIT == ENABLE )
    CLEAR_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER0),TBEN);
    GPTMCFG(GPT_32_64_BIT_WIDE_TIMER0) |= SPLIT_TIMERS;
    GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER0) = ( GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER0) & 0xFFFFFFFC ) | (1<<1);
    CLEAR_BIT(GPTMIMR(GPT_32_64_BIT_WIDE_TIMER0),TBTOIM);
    GPTMTBILR(GPT_32_64_BIT_WIDE_TIMER0) = 0xFFFFFFFF;
    SET_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER0), TBEN);

#elif (GPT_PREDEF_TIMER_1US_24BIT == ENABLE )
    CLEAR_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER1),TBEN);
    GPTMCFG(GPT_32_64_BIT_WIDE_TIMER1) |= SPLIT_TIMERS;
    GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER1) = ( GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER1) & 0xFFFFFFFC ) | (1<<1);
    CLEAR_BIT(GPTMIMR(GPT_32_64_BIT_WIDE_TIMER1),TBTOIM);
    GPTMTBILR(GPT_32_64_BIT_WIDE_TIMER1) = 0xFFFFFFFF;
    SET_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER1), TBEN);

#elif (GPT_PREDEF_TIMER_1US_32BIT == ENABLE )
    CLEAR_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER2),TBEN);
    GPTMCFG(GPT_32_64_BIT_WIDE_TIMER2) |= SPLIT_TIMERS;
    GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER2) = ( GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER2) & 0xFFFFFFFC ) | (1<<1);
    CLEAR_BIT(GPTMIMR(GPT_32_64_BIT_WIDE_TIMER2),TBTOIM);
    GPTMTBILR(GPT_32_64_BIT_WIDE_TIMER2) = 0xFFFFFFFF;
    SET_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER2), TBEN);

#elif (GPT_PREDEF_TIMER_100US_32BIT == ENABLE )
    CLEAR_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER3),TBEN);
    GPTMCFG(GPT_32_64_BIT_WIDE_TIMER3) |= SPLIT_TIMERS;
    GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER3) = ( GPTMTBMR(GPT_32_64_BIT_WIDE_TIMER3) & 0xFFFFFFFC ) | (1<<1);
    CLEAR_BIT(GPTMIMR(GPT_32_64_BIT_WIDE_TIMER3),TBTOIM);
    GPTMTBILR(GPT_32_64_BIT_WIDE_TIMER3) = 0xFFFFFFFF;
    SET_BIT(GPTMCTL(GPT_32_64_BIT_WIDE_TIMER3), TBEN); 

#endif

}

/*************************************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType Channel)       
* \Description     : disable the required channel notification etc. interrupt                             
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel   timer channel ID                    
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_disableNotification(Gpt_ChannelType a_channel)
{
    CLEAR_BIT(GPTMIMR(a_channel),TATOIM);
}


/*************************************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType Channel)       
* \Description     : enable the required channel notification etc. interrupt                             
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel   timer channel ID                    
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_enableNotification(Gpt_ChannelType a_channel)
{
	/*Set TATOIM in IM Register*/
	SET_BIT(GPTMIMR(a_channel),TATOIM);
}

/*************************************************************************************************
* \Syntax          : void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)       
* \Description     : start the required timer with the required tick value                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel   timer channel ID
                     Value     timer count down start value                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_startTimer(Gpt_ChannelType a_channel, Gpt_ValueType a_value)
{
    /* in case of concatenate and 64 bit
     * we set the first 32 bit in GPTMTAILR register and the second in GPTMTBILR register 
     */
    if ( (g_gptTimersMode[a_channel] == CONCATENATE_TIMERS) && (a_channel > 5) )
    {
        uint32 tempValue = (uint32)a_value;
        GPTMTAILR(a_channel) = tempValue;

        tempValue = a_value >> 32; 
        GPTMTBILR(a_channel) = tempValue;
    }
    else
    {
        GPTMTAILR(a_channel) = a_value;
        SET_BIT(GPTMCTL(a_channel), TAEN);
    }     
}

/*************************************************************************************************
* \Syntax          : void GPT_stopTimer(Gpt_ChannelType Channel)       
* \Description     : stop the required timer                              
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel   timer channel ID                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_stopTimer(Gpt_ChannelType Channel)
{	
	CLEAR_BIT(GPTMCTL(Channel), TAEN);
}

/*************************************************************************************************
* \Deiscription : ISR for each timer 
                  clear interrupt flag and call the call back function
**************************************************************************************************/
void TIMER0A_Handler (void)
{
    SET_BIT(GPTMICR(GPT_16_32_BIT_TIMER0),0);
    (*g_gptChannelNotification[GPT_16_32_BIT_TIMER0])();
}

void TIMER1A_Handler (void)
{
    SET_BIT(GPTMICR(GPT_16_32_BIT_TIMER1),0);
    (*g_gptChannelNotification[GPT_16_32_BIT_TIMER1])();
}

void TIMER2A_Handler (void)
{
    SET_BIT(GPTMICR(GPT_16_32_BIT_TIMER2),0);
    (*g_gptChannelNotification[GPT_16_32_BIT_TIMER2])();
}

void TIMER3A_Handler (void)
{
    SET_BIT(GPTMICR(GPT_16_32_BIT_TIMER3),0);
    (*g_gptChannelNotification[GPT_16_32_BIT_TIMER3])();
}