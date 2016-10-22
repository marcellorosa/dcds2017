#include <msp430.h> 
#include "config_hw.h"
#include "util.h"
#include <string.h>

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START   0
//#define REG_INPUT_NREGS   5
#define REG_HOLDING_START 0
#define REG_HOLDING_NREGS 10

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegHoldingStart = REG_HOLDING_START;

static union _TESTE
{
	USHORT usRegHoldingBuf[REG_HOLDING_NREGS];
	//char   usHoldingText[REG_HOLDING_NREGS*2];
}HoldingReg;

/*-------------------- Automaton -------------------------*/
const unsigned int event[NTRANS] = { 2, 3, 5, 4 };
const unsigned int in_state[NTRANS] = { 1, 0, 0, 1 };
const unsigned int rfirst[NSTATES] = { 2, 4 };
const unsigned int rnext[NTRANS] = { 0, 1, 0, 3 };

//Define variable global
unsigned int buffer[BUFFER];				//Buffer to store the event queue
volatile unsigned char n_buffer = 0;		//Number of events at the buffer

//unsigned char flag;

int occur_event = 0;				//ocurrent event
states tst;

void main(void)
{
	volatile eMBErrorCode    eStatus;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	config_clk();				// Set up  clock
	config_io();				// Set up inputs e outputs


	eBlock evBlock[NSTATES];

	unsigned int k, modulo = 0;
	int mealy_output = 0;		//Init output of pepipheral


	unsigned int current_state[NMODULOS];

	memset(current_state,0,NMODULOS*sizeof(int));


	//Block map
	evBlock[0].events[0] = 4;
	evBlock[0].events[1] = 5;
	evBlock[0].qtd = 2;
	evBlock[1].events[0] = 2;
	evBlock[1].events[1] = 3;
	evBlock[1].qtd = 2;




	// >>>>> Fill-in user code here <<<<<9600
	/* Initialize Protocol Stack. */
	if( ( eStatus = eMBInit( MB_RTU, 0x0A, 0, 57600, MB_PAR_EVEN ) ) != MB_ENOERR )
	{
	}
	/* Enable the Modbus Protocol Stack. */
	else if( ( eStatus = eMBEnable(  ) ) != MB_ENOERR )
	{
	}
	else
	{
		for(;;)
		{

			( void )eMBPoll(  );

			if (n_buffer > 0) {

				occur_event = buffer[0];
				n_buffer--;
				k = 0;

				while (k < n_buffer) {
					buffer[k] = buffer[k + 1];
					k++;
				}

				buffer[k] = 0;

				modulo = 0;

				if(!statusEvent(modulo, evBlock,current_state, occur_event)) continue;

				while (modulo < NMODULOS) {

					//Player of  automaton

					k = rfirst[current_state[modulo]]; //posição da primeira transição estado atual

					if (k == 0) {
						return;     //Dead Lock!!!
					} else {

						while (k > 0) {
							k--;

							if ((event[k] + (2 * modulo)) == occur_event) {
								current_state[modulo] = in_state[k];
								mealy_output = 1;
								n_buffer = 0; // Discard remaining refinements from frame
								break;
							}

							k = rnext[k]; // Next position of the transition state current
						}
					}

					modulo++;
				} //while

			} //if

			if (mealy_output) //If the occurred event is valid, then print physical output
			{

				HoldingReg.usRegHoldingBuf[0] = occur_event;

				switch (occur_event) {
					case 2:
						P2OUT |= BIT1;
						P2OUT &= ~BIT0;
						break;
					case 3:
						P2OUT |= BIT0;
						break;
					case 4:
						P2OUT |= BIT2;
						P2OUT &= ~BIT1;
						break;
					case 5:
						P2OUT |= BIT0;
						P2OUT &= ~BIT1;
						break;
					case 6:
						P2OUT |= BIT3;
						P2OUT &= ~BIT2;
						break;
					case 7:
						P2OUT |= BIT1;
						P2OUT &= ~BIT2;
						break;
					case 8:
						P2OUT |= BIT4;
						P2OUT &= ~BIT3;
						break;
					case 9:
						P2OUT |= BIT2;
						P2OUT &= ~BIT3;
						break;
					case 10:
						P2OUT |= BIT5;
						P2OUT &= ~BIT4;
						break;
					case 11:
						P2OUT |= BIT3;
						P2OUT &= ~BIT4;
						break;
					case 12:
						P2OUT |= BIT5;
						break;
					case 13:
						P2OUT |= BIT4;
						P2OUT &= ~BIT5;
						break;
				}

				mealy_output = 0;
				occur_event = -1;
			}	//fim if(mealy_output)

		}
	}


}



eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int iRegIndex;
	if( ( usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs - 1 <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
	{
		iRegIndex = ( int )( usAddress - usRegHoldingStart - 1);
		switch ( eMode )
		{
		/* Pass current register values to the protocol stack. */
		case MB_REG_READ:
			while( usNRegs > 0 )
			{
				*pucRegBuffer++ = ( unsigned char )( HoldingReg.usRegHoldingBuf[iRegIndex] >> 8 );
				*pucRegBuffer++ = ( unsigned char )( HoldingReg.usRegHoldingBuf[iRegIndex] & 0xFF );
				iRegIndex++;
				usNRegs--;
			}
			break;
			/* Update current register values with new values from the
			 * protocol stack. */
		case MB_REG_WRITE:
			while( usNRegs > 0 )
			{
				HoldingReg.usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
				HoldingReg.usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;

				buffer[n_buffer] = HoldingReg.usRegHoldingBuf[iRegIndex];
				n_buffer++;

				iRegIndex++;
				usNRegs--;

			}
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

