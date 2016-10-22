/*
 * portUART.c
 *
 *  Created on: 27/09/2016
 *      Author: Marcelo
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include "port.h"

uint32_t g_ui32Flags;


void UARTConfigure(){

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	ROM_IntMasterEnable();

	MAP_GPIOPinConfigure(GPIO_PC4_U7RX);

	MAP_GPIOPinConfigure(GPIO_PC5_U7TX);

	ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	ROM_UARTConfigSetExpClk(UART7_BASE, g_ui32SysClock, 57600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE| UART_CONFIG_PAR_EVEN));

	UARTIntRegister(UART7_BASE, UARTIntHandler);


	UARTFIFODisable(UART7_BASE);


	MAP_IntEnable(INT_UART7);

	MAP_UARTIntEnable(UART7_BASE, UART_INT_RX);


	/*******************************/

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);


	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0|GPIO_PIN_1));


}

void UARTIntHandler(){

	int32_t ui32Status;

	ui32Status = ROM_UARTIntStatus(UART7_BASE, true);

	UARTIntClear(UART7_BASE, ui32Status);


	if ((ui32Status & UART_INT_RX) == UART_INT_RX) {
		//
		// Loop while there are characters in the receive FIFO.
		//
		while (ROM_UARTCharsAvail(UART7_BASE)) {

			ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);

			//
			// Read the next character from the UART and write it back to the UART.
			//
			rtuBuffer[countBuffer++] = (unsigned char) ROM_UARTCharGetNonBlocking(UART7_BASE);


			ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_1, ~GPIO_PIN_1);

		}
	}

	if ((ui32Status & UART_INT_TX) == UART_INT_TX) {


		ROM_UARTIntDisable(UART7_BASE, UART_INT_TX);	 //disable interrupt

		ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_0, ~GPIO_PIN_0);
	}


}

void UARTSendString(unsigned char *data, unsigned short *length){

	UCHAR isBroadcast = 0;

	if(data[0] == 0){
		isBroadcast = 1;
	}


	while(*length > 0 ){

		ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

		UARTPutChar(UART7_BASE, *data);
		data++;
		(*length)--;
	}

	if(isBroadcast){
		TIMEREnableTurnaround();
	}else{
		TIMEREnableTimeOut();
	}

}

void UARTPutChar(uint32_t ui32Base, unsigned char ucData){

	//Wait until available space

	while(HWREG(ui32Base + UART_O_FR) & UART_FR_TXFF);

	//Send byte
	HWREG(ui32Base+UART_O_DR)= ucData;

	MAP_UARTIntEnable(ui32Base, UART_INT_TX);

}

