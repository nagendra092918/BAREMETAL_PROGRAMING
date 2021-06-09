#include <stdint.h>

#define		RCC_BASE		0x40021000 
#define 	GPIOC_BASE 	0x40011000
#define 	GPIOA_BASE	0x40010800

#define		APB2_ENR_REG			*((volatile uint32_t *)(RCC_BASE+0x18))

#define		GPIOC_CRH_REG			*((volatile uint32_t *)(GPIOC_BASE+0x04))
#define 	GPIOC_ODR_REG			*((volatile uint32_t *)(GPIOC_BASE+0x0C))

#define		GPIOA_CRL_REG			*((volatile uint32_t *)(GPIOA_BASE+0x00))
#define		GPIOA_IDR_REG			*((volatile uint32_t *)(GPIOA_BASE+0x08))

#define 	RCC_IOPAEN				(1<<2)
#define		RCC_IOPCEN				(1<<4)

#define   GPIOC_ODR13 			(1<<13)
#define		GPIOC_CRH_MODE13	((1<<20) |(1<<21))
#define		GPIOC_CRH_CNF13		((1<<22)|(1<<23))

#define 	GPIOA_CRL_MODE0		((1<<0)|(1<<1))
#define		GPIOA_CRL_CNF0		((1<<2)|(1<<3))
#define 	GPIOA_IDR0				(1<<0)

int main ()
{
	volatile uint32_t  READ_BIT=0;
	APB2_ENR_REG  |=  (RCC_IOPAEN | RCC_IOPCEN);
	
	GPIOC_CRH_REG		&=		(~(uint32_t)(GPIOC_CRH_MODE13));       //clear the 20 and 21 bits in CRH Reg
	GPIOC_CRH_REG		&=		(~(uint32_t)(GPIOC_CRH_CNF13));				// clear the 22 and 23 bits in CRH Reg
	
	GPIOC_CRH_REG		|=    (1<<21);															//set 21st bit for low speed
	
	//GPIOC_ODR_REG   |=    (GPIOC_ODR13);												//set 13th bit of ODR
	
	GPIOA_CRL_REG   &= 		(~(uint32_t)(GPIOA_CRL_MODE0));	
	GPIOA_CRL_REG		&=		(~(uint32_t)(GPIOA_CRL_CNF0));
	
	
	GPIOA_CRL_REG   |=    (1<<3);
	
	while(1)
	{
	
	READ_BIT  =  (GPIOA_IDR_REG) & (GPIOA_IDR0);
	
	if(!(READ_BIT))
	{
		GPIOC_ODR_REG    &=   ~((volatile uint32_t)GPIOC_ODR13);
		for(volatile int i=0;i<500000;i++);
	}
	else
	{		 
		GPIOC_ODR_REG   |=     (volatile uint32_t) GPIOC_ODR13;
		for(volatile int i=0;i<500000;i++);
	}
	}
}
