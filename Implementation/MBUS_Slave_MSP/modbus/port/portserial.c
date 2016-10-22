/*
 * FreeModbus Libary: MSP430 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.3 2006/11/19 03:57:49 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

//extern void USCI_A0_graceInit(void);

/* ----------------------- Defines ------------------------------------------*/
#define U0_CHAR                 ( 0x10 )        /* Data 0:7-bits / 1:8-bits */

#define DEBUG_PERFORMANCE       ( 1 )

#if DEBUG_PERFORMANCE == 0
#define DEBUG_PIN_RX            ( 0 )
#define DEBUG_PIN_TX            ( 1 )
#define DEBUG_PORT_DIR          ( P1DIR )
#define DEBUG_PORT_OUT          ( P1OUT )
#define DEBUG_INIT( )           \
  do \
  { \
    DEBUG_PORT_DIR |= ( 1 << DEBUG_PIN_RX ) | ( 1 << DEBUG_PIN_TX ); \
    DEBUG_PORT_OUT &= ~( ( 1 << DEBUG_PIN_RX ) | ( 1 << DEBUG_PIN_TX ) ); \
  } while( 0 ); 
#define DEBUG_TOGGLE_RX( ) DEBUG_PORT_OUT ^= ( 1 << DEBUG_PIN_RX )
#define DEBUG_TOGGLE_TX( ) DEBUG_PORT_OUT ^= ( 1 << DEBUG_PIN_TX )

#else

#define DEBUG_INIT( )
#define DEBUG_TOGGLE_RX( )
#define DEBUG_TOGGLE_TX( )
#endif

/* ----------------------- Static variables ---------------------------------*/
UCHAR           ucGIEWasEnabled = FALSE;
UCHAR           ucCriticalNesting = 0x00;

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    ENTER_CRITICAL_SECTION(  );
    if( xRxEnable )
    {
    	//IFG2 |= UCA0RXIFG;
    	IE2 |= UCA0RXIE;
    }
    else
    {
        IE2 &= ~UCA0RXIE;
    }
    if( xTxEnable )
    {
        //pino de controle RS485 em nível alto
    	P1OUT |= BIT0;
    	IE2 |= UCA0TXIE;
        IFG2 |= UCA0TXIFG;
    }
    else
    {
        IE2 &= ~UCA0TXIE;
        //pino de controle RS485 em nível baixo
        P1OUT &=~BIT0;
    }
    EXIT_CRITICAL_SECTION(  );
}

BOOL
xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    BOOL            bInitialized = TRUE;
    //USHORT          UxCTL = 0;
    USHORT          UxBR = ( USHORT ) ( SMCLK / ulBaudRate );

    /* initialize Config for the MSP430 USCI_A0 */
    /* Disable USCI */
    UCA0CTL1 |= UCSWRST; //reset a USCI
    UCA0CTL0 = UCMODE_0; //UCMODEx = 00 UART mode


#if 0
    /*
     * Control Register 0
     *
     * UCPEN -- Parity Enabled
     * UCPAR -- Even parity
     * UCMSB -- MSB first
     * ~UC7BIT -- 8-bit
     * ~UCSPB -- One stop bit
     * UCMODE_0 -- UART Mode
     * ~UCSYNC -- Asynchronous mode
     *
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCA0CTL0 = UCPEN | UCPAR | UCMODE_0;

    /*
     * Control Register 1
     *
     * UCSSEL_2 -- SMCLK
     * ~UCRXEIE -- Erroneous characters rejected and UCAxRXIFG is not set
     * ~UCBRKIE -- Received break characters do not set UCAxRXIFG
     * ~UCDORM -- Not dormant. All received characters will set UCAxRXIFG
     * ~UCTXADDR -- Next frame transmitted is data
     * ~UCTXBRK -- Next frame transmitted is not a break
     * UCSWRST -- Enabled. USCI logic held in reset state
     *
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCA0CTL1 = UCSSEL_2 | UCSWRST;


    /* Baud rate control register 0 */
    UCA0BR0 = 17;

    /* Baud rate control register 1 */
    UCA0BR1 = 0;

    /*
     * Modulation Control Register
     *
     * UCBRF_0 -- First stage 0
     * UCBRS_7 -- Second stage 7
     * ~UCOS16 -- Disabled
     *
     * Note: ~UCOS16 indicates that UCOS16 has value zero
     */
    UCA0MCTL = UCBRF_6 | UCBRS_0 | UCOS16;

    /* Enable USCI */
    UCA0CTL1 &= ~UCSWRST;
    return bInitialized;

#endif

    switch ( eParity )
    {
    	case MB_PAR_NONE:
    		break;
    	case MB_PAR_ODD:
    		UCA0CTL0 |= UCPEN;			//habilita paridade
    		break;
    	case MB_PAR_EVEN:
    		UCA0CTL0 |= UCPEN + UCPAR;	//habilita paridade e bit par
        break;
    }
    switch ( ucDataBits )
    {
    	case 8:
    		break;
    	case 7:
    		UCA0CTL0 |=UC7BIT;
    		break;
    	default:
    		bInitialized = FALSE;
    }

    UCA0CTL1 = UCSSEL_2 | UCSWRST; //UCSSELx = 11 ou 10 -> SMCLK

    /* Configure USART0 Baudrate Registers. */
    UCA0BR0 = ( UxBR & 0xFF );
    UCA0BR1 = ( UxBR >> 8 );
    UCA0MCTL = 0;

    //UC0IE |= UCA0RXIE + UCA0TXIE; // Enable USCI_A0 RX and TX interrupt

    /* Enable USCI */
    UCA0CTL1 &= ~UCSWRST;

    return bInitialized;
#if 0
    if( bInitialized )
    {
        ENTER_CRITICAL_SECTION(  );
        /* Reset USART */
        U0CTL |= SWRST;
        /* Initialize all UART registers */
        U0CTL = UxCTL | SWRST;
        /* SSELx = 11 = SMCLK. Use only if PLL is synchronized ! */
        U0TCTL = SSEL1 | SSEL0;
        U0RCTL = URXEIE;
        /* Configure USART0 Baudrate Registers. */
        U0BR0 = ( UxBR & 0xFF );
        U0BR1 = ( UxBR >> 8 );
        U0MCTL = 0;
        /* Enable UART */
        ME1 |= UTXE0 | URXE0;
        /* Clear reset flag. */
        U0CTL &= ~SWRST;

        /* USART0 TXD/RXD */
        P3SEL |= 0x30;
        P3DIR |= 0x10;

        EXIT_CRITICAL_SECTION(  );

        DEBUG_INIT( );
    }
    c
#endif
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
	//__delay_cycles(1000);
	UCA0TXBUF = ucByte;
	while(!(IFG2 & UCA0TXIFG));
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    if (IFG2 & UCA0RXIFG)
    {
    	*pucByte = UCA0RXBUF;
    	return TRUE;
    }else
    {
    	return FALSE;
    }

}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void)
{
    DEBUG_TOGGLE_RX( );
    pxMBFrameCBByteReceived(  );
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void)
{
    DEBUG_TOGGLE_TX( );
    pxMBFrameCBTransmitterEmpty(  );
}



void EnterCriticalSection( void )
{
    //USHORT usOldSR;
    if( ucCriticalNesting == 0 )
    {

        //usOldSR = _DINT( );
    	_DINT( );

        //ucGIEWasEnabled = usOldSR & GIE ? TRUE : FALSE;
    }
    ucCriticalNesting++;
}

void ExitCriticalSection( void )
{
	ucCriticalNesting--;
    if( ucCriticalNesting == 0 )
    {
        //if( ucGIEWasEnabled )
        //{
        _EINT(  );
        //}
    }
}

