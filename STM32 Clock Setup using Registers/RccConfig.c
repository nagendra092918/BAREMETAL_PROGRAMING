#include <stm32f10x.h>
#include "RccConfig.h"









/********************************************************************************************************************
																			Step by Step process Setting PLL as RCC 
*********************************************************************************************************************/
/*
				Enable HSE and wait for the HSE to become Ready
				Set the POWER ENABLE clock and VOLTAGE REGULATOR
				Configure the FLASH PREFETCH and the LATENCY related settings
				Configure the PRESCALARS HCLK,PCLK1,PCLK2
				Configure the main PLL
				Enable the PLL and wait for it to become ready
				Select the clock source and wait for it to be set
*/
void Sys_clock_setting(void)
{
	/* Enable HSE and wait for the HSE to become Ready*/
	RCC->CR &= (uint32_t)(~(1<<16));			// Clear the HSE bit in RCC Control register 
	
	RCC->CR |= (1<<16);									// Turn on HSE bit in RCC control register
	
	while(!(RCC->CR & (1<<17)));				// Wait untill the HSE bit set in RCC control Register
	
	/*Set the POWER ENABLE clock and VOLTAGE REGULATOR*/
	
	RCC->APB1ENR &= (uint32_t)~(1<<28);  // Clear the Power enable clock bit in RCC APB1ENR Register 
	RCC->APB1ENR |= (1<<28);						// SET the Power enable bit in RCC APB1ENR Register 
	
	/*Configure the FLASH PREFETCH and the LATENCY related settings*/
		
	FLASH->ACR &= (uint32_t)(~(8<<0));		// Clear the FLASH LATENCY bits in FLASH_ACR Register
	FLASH->ACR |= (2<<0);									// Set the FLASH LATENCY bits in FLASH_ACR Register
	
	FLASH->ACR &= (uint32_t)(~(1<<4));		// Clear the FLASH PREFETCH BIT in FLASH_ACR Register
	FLASH->ACR |= (1<<4);									// Set the FLASH PREFETCH BIT in FLASH_ACR Register
	
	while(!(FLASH->ACR & (1<<5)));				// Wait until PREFETCH BUFFER ENABLE in FLASH_ACR Register
	
	/*Configure the PRESCALARS HCLK,PCLK1,PCLK2*/
	
	RCC->CFGR &= (uint32_t)~(16<<4);		// SYSCLK not divided AHB prescaler
	
	RCC->CFGR &= (uint32_t)~(8<<8);			// Clear the APB low-speed prescaler bits before setting
	RCC->CFGR |= (4<<1);								// HCLK divided by 2 APB low-speed prescaler (APB1)
	
	RCC->CFGR &= (uint32_t)~(8<<11);		// HCLK not divided APB high-speed prescaler (APB2)
	
	
	/*Configure the main PLL*/
	
	RCC->CFGR &= (uint32_t)~(1<<16);    //Clear the PLL entry clock source bit in RCC_Clock configuration register
	RCC->CFGR |= (1<<16);								//SET PLL entry clock source bit as HSE oscillator clock selected as PLL input clock in RCC_Clock configuration register
	
	RCC->CFGR &= (uint32_t)~(16<<18);   //Clear the PLL multiplication factor bits in RCC_Clock configuration register
	RCC->CFGR |= (8<<18);							  //SET PLL multiplication factor as PLL input clock x 9 in RCC_Clock configuration register
	
	/*Enable the PLL and wait for it to become ready*/
	
	RCC->CR &= (uint32_t)~(1<<24);			// Clear the PLL bit in RCC Control Register
	RCC->CR |= (1<<24);									// Turn on PLL bit in RCC control Register
	while(!(RCC->CR & (1<<25)));				// wait untill the PLL bit set in RCC control Register
	
	/*Select the clock source and wait for it to be set*/
	
	RCC->CFGR &= (uint32_t)~(3<<0);      // Clear the System clock switch in  RCC_Clock configuration register
	RCC->CFGR |= (2<<0);								 // Set System clock switch bits as a PLL selected as system clock in RCC_Clock configuration register
	
	while(!(RCC->CFGR & (2<<2)));				// wait untill Set System clock switch bits as a PLL selected as system clock in RCC_Clock configuration register
	
}
