#include <stdint.h>
#include <stm32f10x.h>
#include "RccConfig.h"
#include "GPIO_Config.h"


int main()
{
	Sys_clock_setting();
	GPIO_Cnfg();
	while(1)
	{
	TOGGLE();
	}
	
}

