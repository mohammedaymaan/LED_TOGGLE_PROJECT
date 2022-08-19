#include"LED.h"
#include"Std_Types.h"

void TIMER0A_Handler_Back (void);
void Blinker(void);


uint8 NUM_OF_TICKS ; 

int main()
{
	LED_init(TIMER0A_Handler_Back); 
	while(1)
	{
		Blinker(); 
		
	}		

}
void Blinker(){
	
	LED_STATE = !LED_STATE;
	Led_Set(LED_STATE);
}

void Led_Set(Led_State Led_StateTemp){
	switch(Led_StateTemp){
		case LED_ON : 
		Led_ON();
		break;
		case LED_OFF : 
		Led_OFF();
		break;
	}
}
void TIMER0A_Handler_Back (void)
{
	
	NUM_OF_TICKS++ ; 

	
}

