#include "queue.h"

QUEUE* create_queue(){
	QUEUE* queue;
	queue = (QUEUE*)malloc(sizeof(QUEUE));

	if(queue){
		queue -> front = NULL;
		queue -> rear = NULL;
		queue -> count = 0;
		return queue;
	}else{
		return NULL;
	}
}

bool enqueue(QUEUE* queue, void* in){
	QUEUE_NODE* new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	new_node -> data_ptr = in;
	new_node -> next = NULL;

	if(queue -> count == 0)	queue -> front = new_node;
	else	queue -> rear -> next = new_node;

	queue -> rear = new_node;
	(queue -> count)++;

	return 1;
}

void* dequeue(QUEUE* queue){
	if(queue -> count == 0)	return NULL;

	QUEUE_NODE* deleted_node = queue->front;
	void* item_ptr = queue -> front -> data_ptr;
	
	if(queue -> count == 1){
		queue -> front = NULL;
		queue -> rear = NULL;
	}else{
		queue -> front = queue -> front -> next;
	}

	free(deleted_node);
	(queue -> count)--;
	return item_ptr;
}
