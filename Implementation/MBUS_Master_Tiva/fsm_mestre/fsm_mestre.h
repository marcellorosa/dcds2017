/*
 * fsm_mestre.h
 *
 *  Created on: 01/10/2016
 *      Author: Marcelo
 */

#ifndef FSM_MESTRE_FSM_MESTRE_H_
#define FSM_MESTRE_FSM_MESTRE_H_

#include "queue.h"
#include "config_rtu.h"
#include "port.h"


extern unsigned char rtuBuffer[MAX_SIZE_BUFFER_RTU ];

extern volatile unsigned short countBuffer;

//extern unsigned char *mb_PDU ;

//extern queue fila;

/******************* Function FSM ************************/

void 	init_master(queue *queue);

USHORT	start_communication();

#endif /* FSM_MESTRE_FSM_MESTRE_H_ */
