
#ifndef MCU_CONFIG_H
#define MCU_CONFIG_H


#define MCU_PERFORM_RESET_API                    STD_ON
#define MCU_ACTIVATED_CLOCK_GATES_SIZE           5
#define MCU_CLOCK_SETTINGS_SIZE                  2


#define MCU_XTAL_CLOCK_FREQ_MHZ                  16



#define MCU_CLOCK_GATE_GPIOA             20u
#define MCU_CLOCK_GATE_GPIOB             21u
#define MCU_CLOCK_GATE_GPIOE             24u
#define TIMER_16_32_PERIPH_CLOCK_GATE   0x604
#define TIMER_32_64_PERIPH_CLOCK_GATE   0x65C

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
    TIMER_16_32_PERIPH_CLOCK_GATE,
	MCU_CLOCK_GATE_WD0

	
};

extern uint8 Mcu_ActivatedClockGates[];

const Mcu_ConfigType McuConfig[MCU_CLOCK_SETTINGS_SIZE]=
{
	/*ClockSettingID*/   /* ClockSource                      PllUse     Freq_KHz  */
	/* 0            */ {  MCU_CLOCK_SOURCE_PIOSC             ,ENABLE     ,16000},
	/* 1            */ {  MCU_ MCU_CLOCK_SOURCE_PIOSC      ,DISABLE      ,16000},
};
#endif