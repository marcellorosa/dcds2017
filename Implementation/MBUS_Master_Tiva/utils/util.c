/*
 * util.c
 *
 *  Created on: 03/10/2016
 *      Author: Marcelo
 */

#include "util.h"

unsigned char existRefinaments(short *event, short *rnext, short k, eBuffer *piMask){

	unsigned char mod = piMask->events[0] % 2;
	unsigned char modE;

	while( k > 0){
		k--;

		modE = event[k] % 2;

		if(event[k] >= piMask->events[0] && event[k] <= piMask->events[piMask->qtde - 1]){

			if( mod == 0 && modE == 0){
				return 1;
			}else if(mod == 1 && modE == 1){
				return 1;
			}

		}

		k = rnext[k];
	}

	return 0;

}


