/*
 * util.h
 *
 *  Created on: 03/10/2016
 *      Author: Marcelo
 */

#ifndef UTIL_H_
#define UTIL_H_

/***************** FSM Supervisor ***************************************/

#define NTRANS 67	//Number of Transition
#define NSTATES 12	//Number of states
#define BUFFER 10  	//Size Buffer

/*******************************************************************************/

#define sizeA	1
#define sizeB	6
#define sizeC	6
#define sizeD	1

extern unsigned short refA[sizeA];
extern unsigned short refB[sizeB];
extern unsigned short refC[sizeC];
extern unsigned short refD[sizeD];

typedef struct{
	unsigned short *events;
	unsigned char qtde;
}eBuffer;

extern eBuffer buffer[BUFFER];
extern unsigned char n_buffer;

unsigned short occur_event;				//Ocurrent event

unsigned char existRefinaments(short *event, short *rnext, short k, eBuffer *piMask);


#endif /* UTIL_H_ */
