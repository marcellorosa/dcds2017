/*
 * util.c
 *
 *  Created on: 28/08/2016
 *      Author: Marcelo
 */

#include <stdlib.h>
#include "util.h"

#if 0
char mapearBloqueio(eBlock *evBlock, unsigned int *event, unsigned int *rfirst, unsigned int *rnext){

	unsigned char i,j,k;
	unsigned char status[NTRANS];

	for(i = 0; i < NESTADOS; i++){

		for(j=0; j < NTRANS; j++) status[j] = 0;

		evBlock[i].qtd = 0;

		k = rfirst[i]; // first transition state

		while(k > 0){
			k--;
			status[k] = event[k];
			k = rnext[k];
			evBlock[i].qtd++;
		}


		__disable_interrupt();

		//evBlock[i].evento = (unsigned int*) malloc(sizeof(unsigned int)*evBlock[i].qtd);

		__enable_interrupt();

		k=0;

		for(j = 0; j < NTRANS; j++){

			if(status[j] == 0){
				(evBlock[i].evento[k++]) = event[j];
				//(evBlock[i].evento)++;
			}
		}

		//evBlock++;

	}

	return 1;
}

#endif

char statusEvent(unsigned int modulo, eBlock* evBlock, unsigned int* current_state, unsigned int evento){

	unsigned char eStatus = 1; //unlocked in the other modules

	unsigned char i,j;

	for(i = 0; i < NMODULOS; i++){

		//if(i == modulo) continue;

		for(j = 0; j < evBlock[current_state[i]].qtd; j++){

			if(evento == evBlock[current_state[i]].events[j] + (2*i)){
				return eStatus = 0; // blocked
			}

		}

	}

	return eStatus;
}


