/*
 * config_hw.c
 *
 *  Created on: 10/09/2016
 *      Author: Marcelo
 */

#include <msp430.h>

//Set up of peripherals
//--------------------------------------------------------------
//--------------------------------------------------------------
void config_clk(void)	//Set  clock
{
	//SMCLK=16,0Mhz
    BCSCTL2 = SELM_0 + DIVM_0 + DIVS_0;

    if (CALBC1_16MHZ != 0xFF) {
        /* Adjust this accordingly to your VCC rise time */
        __delay_cycles(100000);

        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
        DCOCTL = CALDCO_16MHZ;
    }

    /*
     * Basic Clock System Control 1
     *
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     *
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF + DIVA_0;

    /*
     * Basic Clock System Control 3
     *
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_0 -- If XTS = 0, XT1 = 32768kHz Crystal ; If XTS = 1, XT1 = 0.4 - 1-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;

    _enable_interrupt();		//Enables general interrupt
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void config_io(void)	//Set up inputs e outputs
{
	//By default PORT 1 will be considered input and output PORT 2
	P1DIR = 0;				//Initially all the port P1 as the input
	P1DIR |= BIT0; 			//P1.3 as output RS485 control (not use because P1.0 is used as debug in transmission)
	P1OUT &= ~BIT0;

	//P1REN |= BIT3;	//Enables resistors of pull(up/down)
	//P1OUT |= BIT3;	//pull UP

    /* Port 1 Port Select Register */
    P1SEL = BIT1 + BIT2;	//Select function TX RX for pins P1.1 e P1.2
    P1SEL2 = BIT1 + BIT2;	//

    P2DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P2OUT &= BIT0;
}

//--------------------------------------------------------------



