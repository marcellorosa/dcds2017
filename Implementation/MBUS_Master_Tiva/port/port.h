/*
 * port.h
 *
 *  Created on: 27/09/2016
 *      Author: Marcelo
 */

#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>

#include "config_rtu.h"

extern uint32_t g_ui32SysClock;

extern volatile unsigned short countBuffer;

extern unsigned char rtuBuffer[MAX_SIZE_BUFFER_RTU];

typedef char    BOOL;

typedef unsigned char UCHAR;

typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif



/********************* PortUART **************************************/

void 	UARTConfigure();

void 	UARTIntHandler();

void 	UARTSendString(unsigned char *data, unsigned short *length);

void 	UARTPutChar(uint32_t ui32Base, unsigned char ucData);

/*********************************************************************/

/********************* PortTimer ************************************/

void 	TIMERAConfigure();

void 	TIMEREnableTimeOut();

void 	TIMERDisableTimeOut();

void 	TIMEREnableTurnaround();

void 	TIMERDisableTurnaround();

void 	TIMEREnableDebouncer();

void 	TIMERDisableDebouncer();

void 	Timer0IntHandler(void);

void 	Timer1IntHandler(void);

void 	Timer2IntHandler(void);


/********************************************************************/

/************ PORT IO ***********************************************/

void 	configIO();

void 	GPIOKIntHandler();

void 	verficarPorta();
/*******************************************************************/

#endif /* PORT_H_ */
