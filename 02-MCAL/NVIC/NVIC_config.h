/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 19 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/
#ifndef NVIC_CONFIG_H
#define NVIC_CONFIG_H



/*
*  NVIC_GROUPING_SYSTEM_XXX  : [0-7]Groups , [0]Subgroup
*  NVIC_GROUPING_SYSTEM_XXY  : [0-3]Groups , [0-1]Subgroup
*  NVIC_GROUPING_SYSTEM_XYY  : [0-1]Groups , [0-3]Subgroup
*  NVIC_GROUPING_SYSTEM_YYY  : [0]Groups   , [0-7]Subgroup Non-Preemption system
*/

#define NVIC_GROUPING_SYSTEM             NVIC_GROUPING_SYSTEM_XXY



#define NVIC_ACTIVATED_INT_SIZE                   5


const Nvic_CfgType Nvic_Cfg[NVIC_ACTIVATED_INT_SIZE] ={
/* Interrupt_Number	    Group_Priority            SubGroup_Priority */

 { NVIC_16_32_TIMER_5_A,     0,                        0                  },
 { NVIC_UART_2,              1,                        0                  },
 { NVIC_UART_3,              2,                        0                  },
 { NVIC_16_32_TIMER_5_B,     3,                        1                  },
 { NVIC_PWM_1_GEN_0,         1,                        1                  },
	
};
#endif 
