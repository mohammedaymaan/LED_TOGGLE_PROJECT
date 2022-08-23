#include "Std_Types.h"
#include "Mcu_Hw.h"


#include "Mcu_interface.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GPT_interface.h"
#include "LED.h"


void LED_init(void (*Set_Call_Back_Ptr)(void)) 
{ 
    /* NVIC_Init Call Config Pointer */   
	Nvic_Init(&Nvic_CfgType)   ;
	/* MCU_Init Call Config Pointer */ 
	Mcu_Init (&Mcu_Clock_0) ;
	
    /*PORT Init Call Config Pointer */
	Port_Init(&Port_Config)    ; 
	
 /*Intialize timer */
  Gpt_ConfigType Gpt_Config[1] =
    {
        {GPT_16_32_BIT_TIMER0, PERIODIC, CONCATENATE_TIMERS, 0 , Set_Call_Back_Ptr}
    };
    GPT_init(Gpt_Config);
    GPT_enableNotification(GPT_16_32_BIT_TIMER0);
   	GPT_startTimer(GPT_16_32_BIT_TIMER0, 2000000);

}
void LED_ON()
{
	Dio_WriteChannel( DIO_CHANNEL_A5 , STD_HIGH );
	
}
void LED_OFF(); 
{
	
	
	Dio_WriteChannel( DIO_CHANNEL_A5 , STD_LOW );
	
	
} 
 
