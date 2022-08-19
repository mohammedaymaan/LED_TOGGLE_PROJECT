#ifndef MCU_PRIVATE_H
#define MCU_PRIVATE_H


#define SYSCTR_BASE_ADDRESS                0x400FE000

/* REST CAUSE */ 
#define RESC                               *((volatile uint32*)0x400FE05C)

/* RCGCGPIO   : GENERAL PURPOSE CLOCK GATING CONTROL */ 
#define RCGCGPIO_OFFSET                   0x608
#define RCGCGPIO                         *((volatile uint32*)(SYSCTR_BASE_ADDRESS+RCGCGPIO_OFFSET)

/*RCC REGISTER_BIT */  
typedef struct
{
	uint32 MOSCDIS  :1;
	uint32          :3;  //RESERVED 
	uint32 OSCSRC   :2;
	uint32 XTAL     :5;
	uint32 BYPASS   :1;
	uint32          :1; //RESERVED 
	uint32 PWRDN    :1;
	uint32          :3; //RESERVED 
	uint32 PWMDIV   :3;
	uint32 USEPWMDIV:1;
	uint32          :1; //RESERVED 
	uint32 USESYSDIV:1;
	uint32 SYSDIV   :4;
	uint32 ACG      :1;
	uint32          :4;	 //RESERVED 
}Mcu_StrBF;	
	
/*union Mcu_StrBF as 32 bit*/ 
  
typedef union
{
	uint32 R;
	Mcu_StrBF B;

}RCC_TAG;

#define RCC                     (*((volatile RCC_TAG*)0x400FE060))
#define RCC2                    (*((volatile *)0x400FE070))
#define PLLSTAT                 (*(volatile uint32*)0x400FE168)









#endif