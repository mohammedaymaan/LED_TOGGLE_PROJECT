#ifndef  PORT_PRIVATE_H
#define  PORT_PRIVATE_H


#define GPIO_APB_BASE_ADDRESS_A          0x40004000
#define GPIO_APB_BASE_ADDRESS_B          0x40005000
#define GPIO_APB_BASE_ADDRESS_C          0x40006000
#define GPIO_APB_BASE_ADDRESS_D          0x40007000
#define GPIO_APB_BASE_ADDRESS_E          0x40024000
#define GPIO_APB_BASE_ADDRESS_F          0x40025000

#define GPIODIR_OFFSET			           0x400
#define GPIODIR(BaseAddr)               *((volatile uint32*)BaseAddr+GPIODIR_OFFSET) 




#endif