#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#define max 100

int main(){

	char str[max];
	char* tok;
	
	STACK* stack = create_stack();
	QUEUE* queue = create_queue();

	printf("enter the string : ");
	gets(str);

	tok = strtok(str, " ");

	while(tok != NULL){
		printf("tok = %s\n", tok);
		push(stack, tok);
		enqueue(queue, tok);
		tok = strtok(NULL, " ");
	}
	
	printf("pop------------------\n");
	while(stack -> count != 0)	printf("%c\n",*((char*)pop(stack)));
	printf("dequeue--------------\n");
	while(queue -> count != 0)	printf("%c\n",*((char*)dequeue(queue)));

	return 0;
}	
		
