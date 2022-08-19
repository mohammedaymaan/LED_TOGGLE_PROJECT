#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

typedef enum
{
    GPT_16_32_BIT_TIMER0,
    GPT_16_32_BIT_TIMER1,
	GPT_16_32_BIT_TIMER2,
	GPT_16_32_BIT_TIMER3,
	GPT_16_32_BIT_TIMER4,
	GPT_16_32_BIT_TIMER5,
}Gpt_ChannelType;

typedef uint64 Gpt_ValueType;

typedef enum
{
    PERIODIC,
    ONESHOT

}Gpt_ChannelModeType;

typedef enum
{
	CONCATENATE_TIMERS = 0,
	SPLIT_TIMERS = 0x4

}Gpt_TimerMode;

typedef void(*Gpt_NotificationType)(void);

typedef struct 
{
    Gpt_ChannelType Channel;
    Gpt_ChannelModeType Mode;
	Gpt_TimerMode TimerMode;
	uint16 Prescaler;
    Gpt_NotificationType GptNotification;

}Gpt_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*************************************************************************************************
* \Syntax          : void Gpt_init (const Gpt_ConfigType* ConfigPtr)       
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
void GPT_init (const Gpt_ConfigType* ConfigPtr);

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
void GPT_disableNotification(Gpt_ChannelType Channel);

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
void GPT_enableNotification(Gpt_ChannelType Channel);


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
void GPT_startTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);


/*************************************************************************************************
* \Syntax          : void Gpt_StopTimer(Gpt_ChannelType Channel)       
* \Description     : stop the required timer                              
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Channel   timer channel ID                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
**************************************************************************************************/
void GPT_stopTimer(Gpt_ChannelType Channel);

 
#endif  /* FILE_NAME_H */



#endif

