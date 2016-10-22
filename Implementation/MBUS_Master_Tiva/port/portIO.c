/*
 * portIO.c
 *
 *  Created on: 04/10/2016
 *      Author: Marcelo
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

#include "util.h"
#include "port.h"


void configIO(){

	//Enables port K e L as GPIO
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);

	//Set up porta K as input
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTK_BASE, GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3);

	//Enables resistor de pull_up in port K
	GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	//Set up interrupt  port K
	GPIOIntRegister(GPIO_PORTK_BASE,GPIOKIntHandler);
	MAP_GPIOIntTypeSet(GPIO_PORTK_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_FALLING_EDGE); //Borda de descida
	GPIOIntEnable(GPIO_PORTK_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	MAP_IntEnable(INT_GPIOK);

	//Set up port L as output
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE,GPIO_PIN_0|GPIO_PIN_1| GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE,0xFF,0);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE,GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_2);

}

int flag;

void GPIOKIntHandler()
{

	MAP_IntDisable(INT_GPIOK);

	flag = MAP_GPIOIntStatus(GPIO_PORTK_BASE, 0xFF);

	ROM_GPIOIntClear(GPIO_PORTK_BASE,0xFF);	//clear flag port B


	TIMEREnableDebouncer();
}

void verficarPorta(){

	TIMERDisableDebouncer();

	eBuffer piMask;

	if (flag & GPIO_PIN_0)
	{
		MAP_GPIOIntClear(GPIO_PORTK_BASE, GPIO_PIN_0);
		piMask.events = refA;
		piMask.qtde = sizeA;
		buffer[n_buffer] = piMask;

		if (n_buffer < BUFFER - 1)
			n_buffer++;
	}

	if (flag & GPIO_PIN_1)
	{
		ROM_GPIOIntClear(GPIO_PORTK_BASE, GPIO_PIN_1);
		piMask.events = refB;
		piMask.qtde = sizeB;
		buffer[n_buffer] = piMask;

		if (n_buffer < BUFFER - 1)
			n_buffer++;
	}

	if (flag & GPIO_PIN_2)
	{
		ROM_GPIOIntClear(GPIO_PORTK_BASE, GPIO_PIN_2);
		piMask.events = refC;
		piMask.qtde = sizeC;

		buffer[n_buffer] = piMask;
		if (n_buffer < BUFFER - 1)
			n_buffer++;
	}

	if (flag & GPIO_PIN_3)
	{
		ROM_GPIOIntClear(GPIO_PORTK_BASE, GPIO_PIN_3);
		piMask.events = refD;
		piMask.qtde = sizeD;

		buffer[n_buffer] = piMask;
		if (n_buffer < BUFFER - 1)
			n_buffer++;
	}


	MAP_IntEnable(INT_GPIOK);
}
