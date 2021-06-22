#include <stm32f10x.h>
#include "GPIO_Config.h"

void GPIO_Cnfg(void )
{
		RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN;      // IO port C clock enable
		GPIOC->CRH 		|=  GPIO_CRH_MODE13_1;			//set Output mode, max speed 2 MHz
		GPIOC->CRH      &=  (uint32_t)~(3<<22);			// configure General purpose output push-pull  
}


void TOGGLE(void )
{
	GPIOC->ODR |= 1<<13;
	Delay(2000000);
	//for((uint32_t) i = 0;i<5000000;i++);
	GPIOC->ODR &= (uint32_t)~(1<<13);
	Delay(2000000);
	//for((uint32_t) i = 0;i<5000000;i++);
}


void Delay(uint32_t volatile count)
{
	while(count--);
}
