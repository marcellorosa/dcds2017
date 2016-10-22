/*
 * queue.c
 *
 *  Created on: 24/09/2016
 *      Author: Marcelo
 */

#include "queue.h"
#include <stdlib.h>

#include "string.h"

#if 0
unsigned char create_queue(queue *fila, unsigned char size_fila){

	unsigned char retorno = 0;

	//Ver como implementar região critica
	int a = sizeof(eQueue);

	//fila->e_queue = (eQueue *) malloc(sizeof(eQueue)*size_fila);
	//fila->e_queue = (eQueue *) umm_malloc(sizeof(eQueue)*size_fila);

	//

	fila->qtd = 0;
	fila->size_queue = size_fila;

	if(fila->e_queue != 0)
		retorno = 1;

	return retorno;
}
#endif

void init_queue(queue *fila){

	memset(fila->e_queue,0, sizeof(eQueue)*SIZE_FILA);

	fila->prox = 0;

}

unsigned char insert_queue(queue *fila, eQueue *element){

	unsigned char was_insert = 0;

	if(fila->prox < SIZE_FILA){
		fila->e_queue[(fila->prox)++] = *element;

		was_insert = 1;
	}

	return was_insert;
}

unsigned char remove_queue(queue *fila, eQueue *element){

	unsigned char was_remove = 0;
	unsigned char i;


	if(fila->prox > 0){
		*element = fila->e_queue[0];
		fila->prox--;
		was_remove = 1;

		for(i = 0; i <= (SIZE_FILA - 1); i++ ){
			fila->e_queue[i] = fila->e_queue[i+1];
		}

	}

	return was_remove;
}


