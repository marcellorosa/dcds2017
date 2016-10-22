/*
 * fsm_master.c
 *
 *  Created on: 23/09/2016
 *      Author: Marcelo
 */

#include "fsm_mestre.h"
#include "mbRTU.h"
#include "mbcrc.h"

static eQueue frame;

volatile USHORT  length_replay;

extern volatile UCHAR flagTimer;

queue *fila;

UCHAR *mb_PDU;

void init_master(queue *queue){

	fila = queue;

	mb_PDU = rtuBuffer;
	countBuffer = 0;

	UARTConfigure();
	TIMERAConfigure();

}


USHORT start_communication(){

	while (fila->prox > 0) {

		remove_queue(fila, &frame);

		length_replay = montar_data_PDU(&frame, mb_PDU);

		UARTSendString((unsigned char*) rtuBuffer, (unsigned short *)&countBuffer);

		//aguarda por resposta
		while (length_replay != countBuffer && flagTimer == 0);

		TIMERDisableTimeOut();

		if (flagTimer == 1) {

			if (mb_PDU[0] != 0) {

				//processar erro time_out;
				//a++;
			}

			continue;
		}

		//check crc
		if(usMBCRC16(rtuBuffer,countBuffer) != 0){

			//processar erro de crc

			continue;
		}

		//processar resposta
		switch (rtuBuffer[1]) {
			case 3:
				mb_processReplayReadHoldingRegisters(rtuBuffer, countBuffer);
				break;
			case 16:
				break;

		}



	}


	return 1;

}

