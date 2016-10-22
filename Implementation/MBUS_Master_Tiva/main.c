/*
 * main.c
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
#include "queue.h"
#include "mbRTU.h"
#include "fsm_mestre.h"
#include "util.h"

#define FCLK 		120000000


uint32_t g_ui32SysClock;

unsigned char rtuBuffer[MAX_SIZE_BUFFER_RTU];

volatile unsigned short countBuffer = 0;

unsigned short refA[sizeA] = {1};
unsigned short refB[sizeB] = {2, 4, 6, 8, 10, 12};
unsigned short refC[sizeC] = {3, 5, 7, 9, 11, 13};
unsigned short refD[sizeD] = {14};

USHORT size = 6;

extern volatile USHORT  length_replay;
extern volatile UCHAR flagTimer;

queue filamestre;

/***************** FSM Supervisor ***************************************/

const unsigned short event[NTRANS]={5,7,9,11,13,1,14,1,4,6,8,12,5,7,9,11,13,2,10,4,6,8,12,14,2,10,5,3,7,9,11,13,14,1,5,2,4,6,8,12,3,7,9,11,13,10,2,4,6,8,12,
		14,10,13,5,7,9,11,14,13,5,3,7,9,11,14,1};
const unsigned int in_state[NTRANS]={1,1,1,1,1,2,0,3,0,0,0,0,3,3,3,3,3,4,8,1,1,1,1,2,5,9,1,5,5,5,5,5,4,7,3,4,4,4,4,4,7,7,7,7,7,10,5,5,5,5,5,
		6,11,1,9,9,9,9,8,5,9,11,11,11,11,10,6};
const unsigned short rfirst[NSTATES] = {6,8,19,26,67,34,46,53,58,59,65,66};
const unsigned short rnext[NTRANS] = {0,1,2,3,4,5,0,7,0,9,10,11,12,13,14,15,16,17,18,0,20,21,22,23,24,25,0,27,28,29,30,31,0,33,0,35,36,37,38,39,40,41,42,43,44,45,0,47,48,49,50,
		51,52,0,54,55,56,57,0,0,60,61,62,63,64,0,32};


//Define variable global
eBuffer buffer[BUFFER];			//Buffer to store the event external queue
unsigned char n_buffer = 0;		//Number of events at the buffer
int generate_event = 1;			//Flag to enable the timing controllable events

/**********************************************************************************/
void actionEventA();
void actionEventB();
void actionEventC();
void actionEventD();

int main(void) {

	g_ui32SysClock = ROM_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ|SYSCTL_OSC_MAIN|SYSCTL_USE_PLL|SYSCTL_CFG_VCO_480),FCLK);

	init_queue(&filamestre);

	eQueue element;

	init_master(&filamestre);

	configIO();

	unsigned int k;
	eBuffer piMask;
	unsigned int current_state = 0;		//Current status initialized with initial state
	unsigned char g=0; 					//Flag para gerador aleatório de eventos
	unsigned char mealy_output = 0;		//Flag for random generator events


	while (1) {

		if (n_buffer == 0)//If there is no event in the buffer then generate an internal event (Event controllable)
				{
			if (generate_event == 1) {
				switch (g)//Here it is implemented an automatic generator of controllable events
				{
				case (0): //Event A
					piMask.events = refA;
					piMask.qtde = 1;
					g++;
					break;
				case (1): //Event C
					piMask.events = refC;
					piMask.qtde = 6;
					g=0;
					break;

				}
			}
		} else 	//If there is not controllable event catch buffer
		{

			piMask = buffer[0];
			n_buffer--;
			k = 0;

			while (k < n_buffer) {
				buffer[k] = buffer[k + 1];
				k++;
			}
		}

		//Jogador de autômato
		k = rfirst[current_state];

		if(piMask.qtde == 1){ // If there is no refinement, it is the own event
			occur_event = *(piMask.events);

		}else{// |Da(s)| > 1

			char ret = existRefinaments(event, rnext, k, &piMask);

			if(ret){ // If there is more than one qualified refinements in the state belonging to the set of refinements (Da (s)) consult HD

				element.address_slave = 10;
				element.function_code = 0x10;
				element.data = piMask.events;
				element.size_data = piMask.qtde;

				insert_queue(&filamestre,&element);

				element.function_code = 0x03;
				element.data = piMask.events;
				element.size_data = 1;

				insert_queue(&filamestre, &element);

				start_communication(); // Start communication with Slave -> HD
									 // The distinguisher response is to set the variable Occur event the response function -> mb_processReplayReadHoldingRegisters ()

			}else{
				occur_event = piMask.events[0];
			}

		}

		if (k == 0) {
			return;     //Dead Lock!!!
		} else {


			while (k > 0) {
				k--;

				if (event[k] == occur_event) {

					current_state = in_state[k];
					mealy_output = 1;
					break;
				}


				k = rnext[k];
			}
		}

		if (mealy_output) //Se o evento ocorrido for válido, então imprimir saída física
		{
			switch (occur_event) {
			//controllable events
			case (1):
				actionEventA();
				break;
			case (3):
				actionEventC();
				break;
			case (5):
				actionEventC();
				break;
			case (7):
				actionEventC();

				break;
			case (9):
				actionEventC();

				break;
			case (11):
				actionEventC();

				break;
			case (13):
				actionEventC();

				break;
				//eventos não controláveis
			case (2):
				actionEventB();
				generate_event = 1;
				break;
			case (4):
				actionEventB();

				generate_event = 1;
				break;
			case (6):
				actionEventB();

				generate_event = 1;
				break;
			case (8):
				actionEventB();
				generate_event = 1;
				break;
			case (10):
				actionEventB();
				generate_event = 1;
				break;
			case (12):
				actionEventB();
				generate_event = 1;
				break;
			case (14):
				actionEventD();
				generate_event = 1;
				break;
			}	//end switch
			mealy_output = 0;
			occur_event = -1;
		}	//end if(mealy_output)
	}	//end while(1)

	return 0;
}	//end main

void actionEventA(){
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0,~GPIO_PIN_0);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1,GPIO_PIN_1);
}

void actionEventB(){
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1,~GPIO_PIN_1);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0,GPIO_PIN_0);
}

void actionEventC(){
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2,~GPIO_PIN_2);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3,GPIO_PIN_3);
}

void actionEventD(){
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2,GPIO_PIN_2);
	MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3,~GPIO_PIN_3);
}
