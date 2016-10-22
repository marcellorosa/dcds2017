/*
 * mbRTU.c
 *
 *  Created on: 24/09/2016
 *      Author: Marcelo
 */

#include "mbRTU.h"
#include "port.h"
#include "mbcrc.h"



unsigned short montar_data_PDU(eQueue *frame, UCHAR *modBus_PDU){

	unsigned short CRC16;
	unsigned short comprimento = 0;

	countBuffer = 0; //ver isso depois



	modBus_PDU[countBuffer++] = frame->address_slave;
	modBus_PDU[countBuffer++] = frame->function_code;

	switch (frame->function_code) {
		case 3:
			mb_readHoldingRegisters(modBus_PDU,frame->size_data);
			comprimento = 4 + 2*frame->size_data + 1; //(code_function + add.Slave + byte_count + Register )
			break;
		case 16:
			mb_writeMultipleRegisters(modBus_PDU,frame->data,frame->size_data);
			comprimento = 8;
			break;
		//default:
		//	break;
	}

	CRC16 = usMBCRC16(modBus_PDU,countBuffer);
	modBus_PDU[countBuffer++] = (UCHAR) (CRC16 & 0xFF);
	modBus_PDU[countBuffer++] = (UCHAR) (CRC16 >> 8);

	return comprimento;
}

unsigned char mb_writeMultipleRegisters(UCHAR *data_PDU, USHORT *data, USHORT length){


	//UCHAR index = 1;

	//Starting Address
	data_PDU[countBuffer++] = (UCHAR) WRT_STARTING_REG >> 8;
	data_PDU[countBuffer++] = (UCHAR) (WRT_STARTING_REG & 0xFF);

	//Quantity of Registers
	data_PDU[countBuffer++] = (UCHAR) (length >> 8);
	data_PDU[countBuffer++] = (UCHAR) (length & 0xFF);

	//Byte Count
	data_PDU[countBuffer++] = (UCHAR) (2*length);

	while((countBuffer - 7) < 2*length){
		data_PDU[countBuffer++] = (UCHAR) (*data) >> 8;
		data_PDU[countBuffer++] = (UCHAR) (*data & 0xFF);
		data++;
	}

	return 1;
}

unsigned char mb_readHoldingRegisters(UCHAR *data_PDU, USHORT qtd_regs){

	//Starting Address
	data_PDU[countBuffer++] = (UCHAR) READ_STARTING_REG >> 8;
	data_PDU[countBuffer++] = (UCHAR) (READ_STARTING_REG & 0xFF);

	//Quantity of Registers
	data_PDU[countBuffer++] = (UCHAR) (qtd_regs >> 8);
	data_PDU[countBuffer++] = (UCHAR) (qtd_regs & 0xFF);

	return 1;
}


unsigned char mb_processReplayReadHoldingRegisters(UCHAR *data_PDU, USHORT length){

	occur_event = data_PDU[3];
	occur_event |= data_PDU[4];

	return 1;
}

