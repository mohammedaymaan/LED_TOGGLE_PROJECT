#ifndef  DIO_PRIVATE_H
#define  DIO_PRIVATE_H




#define DIO_PORTS_NUMBER 6
extern const uint32 GPIOPortsBaseAddress[DIO_PORTS_NUMBER] ;

typedef struct {
    /* 0x3FC */ volatile unsigned long GPIODATA ;
    /* 0x400 */ volatile unsigned long GPIODIR  ;
    /* 0x404 */ volatile unsigned long GPIOIS   ;
    /* 0x408 */ volatile unsigned long GPIOIBE  ;
    /* 0x40C */ volatile unsigned long GPIOIEV  ;
    /* 0x410 */ volatile unsigned long GPIOIM   ;
    /* 0x414 */ volatile unsigned long GPIORIS  ;
    /* 0x418 */ volatile unsigned long GPIOMIS  ;
    /* 0x41C */ volatile unsigned long GPIOICR  ;
    /* 0x420 */ volatile unsigned long GPIOAFSEL;
     /*gap*/    unsigned long  RESERVED1[55];
    /* 0x500 */ volatile unsigned long GPIODR2R ;
    /* 0x504 */ volatile unsigned long GPIODR4R ;
    /* 0x508 */ volatile unsigned long GPIODR8R ;
    /* 0x50C */ volatile unsigned long GPIOODR  ;
    /* 0x510 */ volatile unsigned long GPIOPUR  ;
    /* 0x514 */ volatile unsigned long GPIOPDR  ;
    /* 0x518 */ volatile unsigned long GPIOSLR  ;
    /* 0x51C */ volatile unsigned long GPIODEN  ;
    /* 0x520 */ volatile unsigned long GPIOLOCK ;
    /* 0x524*/  volatile unsigned long GPIOCR   ;
	/* 0x528*/  volatile unsigned long GPIOAMSEL ; 
	/*0x52C*/   volatile unsigned long GPIOPCTL ; 
	/*0x530*/   volatile unsigned long GPIOADCCTL ; 
}GPIO_typedef;

#define  GPIO_DATA_REGISTER_OFFSET         0x3FC 
#define  GPIO_DIR_REGISTER_OFFSET          0x400 
#define  GPIO_IS_REGISTER_OFFSET           0x404 
#define  GPIO_IBE_REGISTER_OFFSET          0x408 
#define  GPIO_IEV_REGISTER_OFFSET          0x40C 
#define  GPIO_IM_REGISTER_OFFSET           0x410 
#define  GPIO_RIS_REGISTER_OFFSET          0x414 
#define  GPIO_MIS_REGISTER_OFFSET          0x418 
#define  GPIO_ICR_REGISTER_OFFSET          0x41C 
#define  GPIO_AFSEL_REGISTER_OFFSET        0x420 
#define  GPIO_DR2R_REGISTER_OFFSET         0x500 
#define  GPIO_DR4R_REGISTER_OFFSET         0x504 
#define  GPIO_DR8R_REGISTER_OFFSET         0x508 
#define  GPIO_ODR_REGISTER_OFFSET          0x50C 
#define  GPIO_PUR_REGISTER_OFFSET          0x510 
#define  GPIO_PDR_REGISTER_OFFSET          0x514 
#define  GPIO_SLR_REGISTER_OFFSET          0x518 
#define  GPIO_DEN_REGISTER_OFFSET          0x51C 
#define  GPIO_LOCK_REGISTER_OFFSET         0x520 
#define  GPIO_CR_REGISTER_OFFSET           0x524 
#define  GPIO_AMSEL_REGISTER_OFFSET        0x528 
#define  GPIO_PCTL _REGISTER_OFFSET	       0x52C
#define  GPIO_ADCCTL_REGISTER_OFFSET	   0x530

		
		
#define GPIODATA(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DATA_REGISTER_OFFSET))
#define GPIODIR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DIR_REGISTER_OFFSET))
#define GPIODATA(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DATA_REGISTER_OFFSET))
#define GPIOCR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_CR_REGISTER_OFFSET))
#define GPIOAFSEL(PORT_ID)  (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_AFSEL_REGISTER_OFFSET))
#define GPIOPUR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_PUR_REGISTER_OFFSET))
#define GPIOPDR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_PDR_REGISTER_OFFSET))
#define GPIODEN(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DEN_REGISTER_OFFSET))
#define GPIOLOCK(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_LOCK_REGISTER_OFFSET))
#define GPIOAMSEL(PORT_ID)  (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_AMSEL_REGISTER_OFFSET))
#define GPIOCR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_CR_REGISTER_OFFSET))
#define GPIOODR(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ODR_REGISTER_OFFSET))
#define ADCCTL(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ADCCTL_REGISTER_OFFSET))
#define GPIOPCTL(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_ADCCTL_REGISTER_OFFSET))
#define GPIODR2R(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR2R_REGISTER_OFFSET))
#define GPIODR4R(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR4R_REGISTER_OFFSET))
#define GPIODR8R(PORT_ID)   (*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_DR8R_REGISTER_OFFSET))
#define GPIOIBE(PORT_ID)	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IBE_REGISTER_OFFSET))
#define GPIOIEV(PORT_ID)	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IEV_REGISTER_OFFSET))
#define GPIOIM(PORT_ID) 	(*(volatile uint32 *)(GPIOPortsBaseAddress[PORT_ID] + GPIO_IM_REGISTER_OFFSET))









#endif