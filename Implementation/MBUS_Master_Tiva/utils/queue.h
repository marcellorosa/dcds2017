/*
 * queue.h
 *
 *  Created on: 24/09/2016
 *      Author: Marcelo
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define SIZE_FILA 		5

typedef struct{
	unsigned char 	address_slave;
	unsigned char 	function_code;
	unsigned short 	*data;
	unsigned char 	size_data;

}eQueue;

typedef struct{
	eQueue e_queue[SIZE_FILA];
	//unsigned short size_queue;
	unsigned short prox;
}queue;


unsigned char 	create_queue(queue *fila, unsigned char size_fila);
unsigned char 	insert_queue(queue *fila, eQueue *element);
unsigned char 	remove_queue(queue *fila, eQueue *element);

void 			init_queue(queue *fila);



#endif /* QUEUE_H_ */
