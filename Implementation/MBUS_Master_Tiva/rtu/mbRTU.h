/*
 * mbRTU.h
 *
 *  Created on: 24/09/2016
 *      Author: Marcelo
 */

#ifndef MBRTU_H_
#define MBRTU_H_

#include "queue.h"
#include "port.h"

#include "config_rtu.h"

extern unsigned char rtuBuffer[MAX_SIZE_BUFFER_RTU];

extern volatile unsigned short countBuffer;

extern unsigned short occur_event;



unsigned short		montar_data_PDU(eQueue *frame, UCHAR *modBus_PDU);

unsigned char 		mb_writeMultipleRegisters(UCHAR *data_PDU, USHORT *data, USHORT length);

unsigned char		mb_readHoldingRegisters(UCHAR *data_PDU, USHORT qtd_regs);


unsigned char 		mb_processReplayReadHoldingRegisters(UCHAR *data_PDU, USHORT length);



#endif /* MBRTU_H_ */
