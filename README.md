# Datastructure-examples
1. 개요
공백으로 구분된 한 라인을 입력으로 받아 strtok함수를 사용해 구분하여 stack/queue에 저장하고 차례로 출력한다.

2. 프로그램 구조 설명
 2.1 함수에 관한 설명

-STACK* create_stack() : 
 STACK을 생성하는 함수. 아무것도 담겨 있지 않은 상태를 반환한다.

-int push(STACK* stack, void* in) : 
 stack에 데이터 in을 넣는 함수. 성공하면 1을 반환한다.

-void* pop(STACK* stack) :
 stack의 top을 빼내는 함수 top안의 data_ptr을 반환한다.

-QUEUE* create_queue() : 
 QUEUE을 생성하는 함수. 아무것도 담겨 있지 않은 상태를 
 반환한다.

-bool enqueue(QUEUE* queue, void* in) :
 queue에 데이터 in을 넣는 함수. 성공하면 true을 반환한다.

-void* dequeue(QUEUE* queue) :

 

 2.2 다이어그램
 



3. 실행 결과
-실행 결과

1 2 3 4 5를 입력받아 공백 단위로 끊은 것을 임시로 tok이라는 변수에 담아 출력했고, 올바르게 끊겼다는 사실을 알 수 있다. stack에 1 2 3 4 5 순으로 담은 후 pop을 했을 때 5 4 3 2 1 순으로 나와야 하는데 올바른 결과가 도출되었다. 마찬가지로 queue에 1 2 3 4 5 순으로 담은 후 dequeue를 했을 때 1 2 3 4 5 순으로 올바른 결과가 도출되었다는 사실을 알 수 있다.

4. 고찰
 stack과 queue를 짜고 컴파일을 하는데 node라는 구조체가 충돌한다는 에러가 났다. stack.h 와 queue.h 에는 각각 STACK_NODE, QUEUE_NODE가 있는데 처음에 typedef struct node{...}STACK_NODE, typedef struct node{...}QUEUE_NODE 로 돼있었다. 둘이 이름이 달라서 문제가 없을 것이라 생각했는데 node라는 이름이 같아서 충돌한 것이었다. 그래서 둘을 구분하기 위해 stack의 node를 s_node로 바꿨고, 문제가 해결되었다.
 처음에 strtok함수로 구분한 문자를 어떻게 stack과 queue에 넣을지 고민했었다. 그래서 고안해 낸 방법이 구분한 문자를 새로운 배열에 담는 것이었다. 입력할 문자가 정수형이라고 생각해서 정수형 배열을 선언한 후에 담았는데 구분한 문자는 문자형이고 배열은 정수형이라서 에러가 났다. 이를 해결하기 위해 문자형을 정수형으로 변환해주는 함수 atoi()를 사용해서 구분한 문자를 형변환 한 후 배열에 담으니 해결이 되었다. 
 그러나 문자열을 입력할 때마다 배열에 크기가 달라지니 비효율적인 코드라는 생각이 들었다. 그래서 배열에다 담지 않고 구분한 즉시 stack과 queue에 담는 게 더 효율적이라는 생각이 들었다. 그러기 위해 구분한 문자를 임시 변수에 담고 바로 stack과 queue에 담았다. 데이터를 모두 담은 후 다시 빼내기 위해 pop과 dequeue를 하는데 다시 에러가 생겼다. pop과 dequeue는 void*를 반환하는데 int*로 형변환을 하니 자료형이 올바르지 않다는 에러가 났다. char*로 형변환을 하니 문제가 해결이 되었고, 배열을 새로 만들지 않아도 돼서 더 효율적이게 되었다.
 공백을 입력받기 위해 scanf가 아닌 gets함수를 사용하였는데, gets()함수를 사용하니 배열의 크기보다 문자열의 크기가 다를 수 있어서 그런지 경고 메시지가 있었다. 이를 해결하기 위해 gets_s()를 사용해 보았지만 별다른 차이가 없어 그냥 gets()함수를 썼다. 비록 에러는 나지 않았지만 런타임 에러가 생길  가능성을 제거하지 못한 점에 대해 아쉬움이 많이 남았다.    
 자료형에 의한 에러를 많이 경험 하다 보니 형변환을 잘 해야겠다고 생각했다. 특히 pop과 dequeue의 경우, void*형을 반환하므로 올바른 자료형으로 형변환을 하는 것이 중요하다는 것을 느꼈다. void타입이 다양한 데이터를 다룰 수 있어 편리하지만 이런 부분에서 사용이 까다롭다는 것도 깨달았다. 마찬가지로 동적 할당 또한 free를 항상 해야 해서 불편함이 따랐다. 둘 다 조심히 사용해야겠다고 생각했다.
 명령어들을 하나씩 입력하다가 makefile을 사용하니 내가 자주 쓰는 명령어들을 묶어서 사용할 수 있어서 편리하다고 느꼈다.   

5. 프로그램 소스 파일

<stack.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{
	void* data_ptr; //모든 데이터를 담기 위해 void*로 선언
	struct s_node* link; 
}STACK_NODE; //stack 안에 데이터를 담을 노드, 데이터와 다음 노드를 가리키는 주소로 구성 
 
typedef struct stack{
	int count;
	STACK_NODE* top;
}STACK; //stack, 노드의 수인 count와 젤 위 노드인 top으로 구성

STACK* create_stack(); //stack을 만드는 함수
int push(STACK* stack, void* in); //stack에 데이터를 넣는 함수
void* pop(STACK* stack); //stack에서 데이터를 빼내는 함수

<stack.c>
#include "stack.h“ //stack.h를 참조

STACK* create_stack(){
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if(!stack)	return 0;
	stack -> count = 0;
	stack -> top = 0;
	return stack;
} //동적 할당해서 stack을 만들고, 노드가 없는 상태로 초기화한 후 반환

int push(STACK* stack, void* in){
	STACK_NODE* node = (STACK_NODE*)malloc(sizeof(STACK_NODE)); //노드를 동적할당
		if(!node) return 0; //노드가 만들어지지 않았으면 실패한 것이므로 0을 반환
	node -> data_ptr = in; //만들어진 노드의 데이터에 in을 담는다
	node -> link = stack -> top; //노드를 stack의 가장 위에 담기 위해 node의 link에 top연결
	stack -> top = node; //현재 노드가 가장 위에 존재하므로 stack의 top을 node로 바꾼다
	(stack -> count)++; //노드가 하나 증가했으므로 count 증가
	return 1; //여기까지 왔으면 성공한 것이므로 1 반환
} 

void* pop(STACK* stack){
	if(stack -> count == 0)	return 0; //stack의 count가 0이면 빼낼 데이터가 없으므로 0 반환
	else{
		STACK_NODE* tmp = stack -> top; //top을 없애기 전에 임시로 담아둔다
		void* data_out = stack -> top -> data_ptr; //top의 데이터를 임시로 담아둔다
		stack -> top = stack -> top -> link; //top의 다음 노드를 새로운 top으로 설정
		free(tmp); //top을 없앤다
		(stack -> count)--; //노드가 하나 없어졌으므로 count 감소
		return data_out; //임시로 담아 둔 데이터 반환
	}
}

<queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	void* data_ptr; //모든 데이터를 담기 위해 void*로 선언
	struct node* next;
}QUEUE_NODE; //queue안에 데이터를 담을 노드, 데이터와 다음 노드를 가리키는 주소로 구성 

typedef struct{
	int count;
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
}QUEUE; //stack, 노드의 수인 count와 젤 앞 노드인 front, 젤 뒤 노드인 rear로 구성

QUEUE* create_queue(); //queue를 만드는 함수
bool enqueue(QUEUE* queue, void* in); //queue에 데이터를 넣는 함수
void* dequeue(QUEUE* queue); //queue에서 데이터를 빼내는 함수

<queue.c>
#include "queue.h" //queue.h를 참조

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
} //동적 할당해서 stack을 만들고, 노드가 없는 상태로 초기화한 후 반환

bool enqueue(QUEUE* queue, void* in){
	QUEUE_NODE* new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE)); 
        //노드를동적할당
	new_node -> data_ptr = in; //만들어진 노드에 데이터 in을 담는다
	new_node -> next = NULL; //queue의 맨 뒤에 데이터를 담으므로 노드의 다음 주소는 null 
	if(queue -> count == 0)		queue -> front = new_node;
	//queue에 노드가 하나도 없었다면 새로운 노드가 front이므로 front를 새로운 노드로 설정
	else	queue -> rear -> next = new_node;
	//그렇지 않으면 queue의 맨 뒤 노드의 다음에 새로운 노드를 연결
	queue -> rear = new_node;
	//이제 새로운 노드가 맨 뒤에 있으므로 queue의 rear를 새로운 노드로 바꾼다
	(queue -> count)++; //노드가 하나 증가했으므로 count 증가
	return 1; //여기까지 왔으면 성공한 것이므로 1(true) 반환
}

void* dequeue(QUEUE* queue){
	if(queue -> count == 0)	return NULL; 
	//queue의 count가 0이면 빼낼 데이터가 없으므로 0 반환
	QUEUE_NODE* deleted_node = queue->front; //queued의 front를 임시로 담아둠
	void* item_ptr = queue -> front -> data_ptr; //front의 데이터를 임시로 담아둠

	if(queue -> count == 1){ 
		queue -> front = NULL;
		queue -> rear = NULL;
	} //count가 1이면 데이터 삭제 후 남아있는 데이터가 없으므로 초기화 한다
	else{
		queue -> front = queue -> front -> next;
	} //그렇지 않으면 front가 삭제되므로 queue의 front를 현재 front의 다음 노드로 설정
	
	free(deleted_node); //queue의 front를 없앤다
	(queue -> count)--; //노드가 하나 지워졌으므로 count 감소
	return item_ptr; //임시로 담아 둔 데이터 반환
}


<main.c>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#define max 100 //max를 100으로 설정

int main(){
	char str[max]; //입력받은 문자열을 담을 배열
	char* tok; //strtok 함수에 의해 구분된 문자를 임시로 담아둘 변수
	
	STACK* stack = create_stack(); //stack 생성
	QUEUE* queue = create_queue(); //queue 생성

	printf("enter the string : ");
	gets(str); //문자열을 입력받아 str에 저장
	
	tok = strtok(str, " "); //str를 “ ”로 구문한 후 tok에 담는다

	while(tok != NULL){ //구분할 문자가 없을 때까지 반복
		printf("tok = %s\n", tok); //구분된 문자 출력
		push(stack, tok); //구분된 문자를 stack에 담는다
		enqueue(queue, tok); //구분된 문자를 queue에 담는다
		tok = strtok(NULL, " "); //구분 후 남은 str를 다시 구분한다
	}

	printf("pop------------------\n");
	while(stack -> count != 0)	printf("%c\n",*((char*)pop(stack)));
	//stack의 개수만큼 pop을 한다
	//pop을 하면 문자형 데이터가 반환되므로 char*로 형변환 한다
	
	printf("dequeue--------------\n");
	while(queue -> count != 0)	printf("%c\n",*((char*)dequeue(queue)));
	//queue의 개수만큼 dequeue을 한다
	//dequeue를 하면 문자형 데이터가 반환되므로 char*로 형변환 한다
		
	return 0;
}		
		
6. 자료 출처
박대진 교수님 자료구조 수업자료 ppt
