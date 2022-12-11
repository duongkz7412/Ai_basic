#include<stdio.h>
#include<stdlib.h>
#define G 6
#define Maxlength 100

typedef struct Node{
	int state[G];
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int top_idx;
}Stack;

typedef struct{
	Node* Elements[Maxlength];
	int front, rear;
}Queue;

const char *action[]={"First State", "Ly 1 2 3",
					"Ly 2 3 4","Ly 3 4 5",
					"Ly 4 5 6"};

void makenullStack(Stack *stack){
	stack->top_idx=Maxlength;
}

int empty_Stack(Stack stack){
	return stack.top_idx==Maxlength;
}

int full_Stack(Stack stack){
	return stack.top_idx==0;
}

void Push_Stack(Node *x,Stack *stack){
	if(full_Stack(*stack)){
		printf("Error");
	}
	else{
		stack->top_idx -= 1;
		stack->Elements[stack->top_idx]=x;
	}
}

void Pop(Stack *stack){
	if(!empty_Stack(*stack)){
		stack->top_idx+=1;
	}
}

Node* Top(Stack stack){
	if(!empty_Stack(stack)){
		return stack.Elements[stack.top_idx];
	}
	return NULL;
}

void makenull_Queue(Queue *queue){
	queue->front=-1;
	queue->rear=-1;
}

int empty_Queue(Queue queue){
	return queue.front==-1;
}

int full_Queue(Queue queue){
	return ((queue.rear-queue.front+1) % Maxlength)==0;
}

Node* Get_Front(Queue queue){
	if(empty_Queue(queue)){
		printf("Error");
	}
	else{
		return queue.Elements[queue.front];
	}
}

void del_Queue(Queue *queue){
	if(!empty_Queue(*queue)){
		if(queue->front==queue->rear){
			makenull_Queue(queue);
		}
		else{
			queue->front=(queue->front+1)%Maxlength;
		}
	}
}

void Push_Queue(Node *x,Queue *queue){
	if(!full_Queue(*queue)){
		if(empty_Queue(*queue)){
			queue->front=0;
		}
		queue->rear=(queue->rear+1)%Maxlength;
		queue->Elements[queue->rear]=x;
	}
}

void Print_State(int state[]){
	printf("\n %d, %d, %d, %d, %d, %d",state[0],state[1],state[2],state[3],state[4],state[5]);
}

int goalcheck(int state[]){
	int i;
	for(i=0;i<=G;i++){
		if(state[i] ==-1){
			return 0;
		}	
	}
	return 1;
}

int ly123(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=0;i<=2;i++){
		result[i] = state[i] * -1;
	}
}

int ly234(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=1;i<=3;i++){
		result[i] = state[i] * -1;
	}
}

int ly345(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=2;i<=4;i++){
		result[i] = state[i] * -1;
	}
}

int ly456(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=3;i<=5;i++){
		result[i] = state[i] * -1;
	}
}

int call_operator(int state[], int result[], int option){
	switch(option){
		case 1: return ly123(state,result);
		case 2: return ly234(state,result);
		case 3: return ly345(state,result);
		case 4: return ly456(state,result);
		default :
		return 0;
	}
}

int compareState(int X[], int Y[]){
	int i;
	for(i=1;i<G;i++){
		if(X[i] != Y[i]){
			return 0;
		}
	}
	return 1;
}

int find_Queue(int state[], Queue openQueue){
	while(!empty_Queue(openQueue)){
		if(compareState(Get_Front(openQueue)->state,state)){
			return 1;
		}
		del_Queue(&openQueue);
	}
	return 0;
}

Node* BFS_Algorithm(int state[]){
	Queue Open_BFS;
	Queue Close_BFs;
	makenull_Queue(&Open_BFS);
	makenull_Queue(&Close_BFs);
	Node* root = (Node*)malloc(sizeof(Node));
	int i;
	for(i=0;i<=G;i++){
		root->state[i]=state[i];
	}
	root->Parent=NULL;
	root->no_function=0;
	Push_Queue(root,&Open_BFS);
	while(!empty_Queue(Open_BFS)){
		Node* node=Get_Front(Open_BFS);
		del_Queue(&Open_BFS);
		Push_Queue(node,&Open_BFS);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt=1;opt<=6;opt++){
			int newstate[G];
			if(call_operator(node->state,newstate,opt)){
				if(find_Queue(newstate,Open_BFS) || find_Queue(newstate,Close_BFs)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				for(i=0;i<G;i++){
					newNode->state[i]=newstate[i];
				}
				newNode->Parent=node;
				newNode->no_function=opt;
				Push_Queue(newNode,&Open_BFS);
			}
		}
	}
	return NULL;
}

void Print_WaysToGetGoal(Node* node){
	Stack stackPrint;
	makenullStack(&stackPrint);
	while(node->Parent!=NULL){
		Push_Stack(node,&stackPrint);
		node = node->Parent;
	}
	Push_Stack(node,&stackPrint);
	int no_action=0;
	while(!empty_Stack(stackPrint)){
		printf("\n Action %d: %s",no_action,action[Top(stackPrint)->no_function]);
		Print_State(Top(stackPrint)->state);
		Pop(&stackPrint);
		no_action++;
	}
}

int main(){
	int state[G] = {1, -1, 1, -1, 1, -1};
	Print_WaysToGetGoal(BFS_Algorithm(state));
	return 0;
}
