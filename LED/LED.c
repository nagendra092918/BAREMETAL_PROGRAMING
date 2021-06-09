//#include "stm32f10x.h"
#include <stdint.h>


int main ()
{
	volatile uint32_t *pRccReg,*pbusadd,*pportadd,*pgpio_odr;
	pRccReg = ( uint32_t*) 0x40021018;           /* Rcc base address + APB2ENR offset address : 0x40021000+0x18*/
	pbusadd = (uint32_t*)	0x40011000;
	pportadd = (uint32_t*) 0x40011004;
	pgpio_odr = (uint32_t*) 0x4001100C;
	
	*pRccReg &= (volatile uint32_t) (~(1<<4));				//CLEAR_BIT 
	*pRccReg |= (volatile uint32_t) (1<<4);					//setting bit
	*pportadd &= ((volatile uint32_t)(~((1<<20)| (1<<21))));     /*clear bits*/
	*pportadd |= (volatile uint32_t)(1<<21);									/*seting bit*/
	*pportadd &= ((volatile uint32_t)(~((1<<22)| (1<<23))));   //clear bits
	while(1)
	{
	*pgpio_odr ^= (volatile uint32_t)(1UL<<13);
	for(volatile int i=0;i<500000;i++);
	//*pgpio_odr &=  (volatile uint32_t)(~(1UL<<13));
	//for(volatile int i=0;i<500000;i++);
	}
}
