/*
 * portTimer.c
 *
 *  Created on: 27/09/2016
 *      Author: Marcelo
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "port.h"

uint32_t g_ui32Flags;

volatile UCHAR flagTimer;


void TIMERAConfigure(){

	USHORT fint_timerA0 = 1000/4; //-> 4ms; time_out
	USHORT fint_timerA1 = 10; //-> 100ms; turnaround
	USHORT fint_timerA2 = 1000/5; // debouncer 2ms

	//enable port
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);


	//Enable as input
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0|GPIO_PIN_1));

	//Enables timers
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

	//Enable interrupts  processor
	ROM_IntMasterEnable();

	//Set up 2 Timer periodics of 32 bits
	ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC_UP);

	ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock/fint_timerA0 - 1); // time_out
	ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock / fint_timerA1 - 1); // time_turnaround -> 100ms
	ROM_TimerLoadSet(TIMER2_BASE, TIMER_A, g_ui32SysClock / fint_timerA2 - 1); // debouncer -> 2ms

	// Set up RTI timers
	TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
	TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1IntHandler);
	TimerIntRegister(TIMER2_BASE, TIMER_A, Timer2IntHandler);

	// Enable interrupts
	ROM_IntEnable(INT_TIMER0A);
	ROM_IntEnable(INT_TIMER1A);
	ROM_IntEnable(INT_TIMER2A);

}


void TIMEREnableTimeOut(){

	ROM_TimerDisable(TIMER0_BASE,TIMER_A);

	HWREG(TIMER0_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER0_BASE + TIMER_O_TAV) = 0;

	ROM_TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	ROM_TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);

	flagTimer = 0;

	ROM_TimerEnable(TIMER0_BASE,TIMER_A);

}

void TIMERDisableTimeOut(){

	ROM_TimerDisable(TIMER0_BASE, TIMER_A);

	ROM_TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	HWREG(TIMER0_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER0_BASE + TIMER_O_TAV) = 0;


}

void TIMEREnableTurnaround(){

	ROM_TimerDisable(TIMER1_BASE,TIMER_A);

	HWREG(TIMER1_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER1_BASE + TIMER_O_TAV) = 0;

	ROM_TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	ROM_TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);

	flagTimer = 0;

	ROM_TimerEnable(TIMER1_BASE,TIMER_A);

	//ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_0,GPIO_PIN_0/*g_ui32Flags*/);

}

void TIMERDisableTurnaround(){

	ROM_TimerDisable(TIMER1_BASE, TIMER_A);

	HWREG(TIMER1_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER1_BASE + TIMER_O_TAV) = 0;

	ROM_TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT);

}

void TIMEREnableDebouncer(){

	ROM_TimerDisable(TIMER2_BASE,TIMER_A);

	HWREG(TIMER2_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER2_BASE + TIMER_O_TAV) = 0;

	ROM_TimerIntClear( TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	ROM_TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);


	ROM_TimerEnable(TIMER2_BASE,TIMER_A);

}

void TIMERDisableDebouncer(){

	ROM_TimerDisable(TIMER2_BASE, TIMER_A);

	HWREG(TIMER2_BASE + TIMER_O_TAR) = 0;

	HWREG(TIMER2_BASE + TIMER_O_TAV) = 0;

	ROM_TimerIntClear( TIMER2_BASE, TIMER_TIMA_TIMEOUT);

}


void Timer0IntHandler(void) {

	TIMERDisableTimeOut();

	flagTimer = 1;



	ROM_TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	HWREGBITW(&g_ui32Flags, 0) ^= 1;


	ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_0,g_ui32Flags);


	ROM_IntMasterDisable();
	ROM_IntMasterEnable();
}

void Timer1IntHandler(void) {

	TIMERDisableTurnaround();

	flagTimer = 1;


	ROM_TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT);


	HWREGBITW(&g_ui32Flags, 1) ^= 1;


	ROM_GPIOPinWrite( GPIO_PORTN_BASE, GPIO_PIN_1, g_ui32Flags );


	ROM_IntMasterDisable();
	ROM_IntMasterEnable();
}

void Timer2IntHandler(void) {

	TIMERDisableDebouncer();


	ROM_TimerIntClear( TIMER1_BASE, TIMER_TIMA_TIMEOUT);

	verficarPorta();

	// update interrupts
	ROM_IntMasterDisable();
	ROM_IntMasterEnable();
}

