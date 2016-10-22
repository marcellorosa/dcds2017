/*
 * util.h
 *
 *  Created on: 28/08/2016
 *      Author: Marcelo
 */

#ifndef UTIL_H_
#define UTIL_H_

//Date of automaton
#define NTRANS 4	// Number of Transition
#define NSTATES 2	// Number of states
#define BUFFER 10  	// Buffer size

#define NMODULOS 5 // Modules of the number distinguisher


typedef struct{
	unsigned int qtd;
	//unsigned int *evento;
	unsigned int events[2];
}eBlock;


typedef struct states_{
	unsigned char s0 : 1;
	unsigned char s1 : 1;
	unsigned char s2 : 1;
	unsigned char s3 : 1;
	unsigned char s4 : 1;
	unsigned char s5 : 1;
	unsigned char s6 : 1;
	unsigned char s7 : 1;
}states;

char mapearBloqueio(eBlock* evBlock, unsigned int *event, unsigned int *rfirst, unsigned int *rnext);

char statusEvent(unsigned int modulo, eBlock* evBlock, unsigned int* current_state, unsigned int evento);


#endif /* UTIL_H_ */
