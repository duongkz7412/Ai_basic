#include<stdio.h>
#include<stdlib.h>
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6
#define Maxlength 100

typedef struct{
	int x;
	int y;
}State;

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int front, rear;
}Queue;

void makenull_Queue(Queue *queue){
	queue->front=-1;
	queue->rear=-1;
}

int empty_Queue(Queue queue){
	return queue.front==-1;
}

int full_Queue(Queue queue){
	return ((queue.rear-queue.front+1)%Maxlength)==0;
}

//tr ve phan tu dau hang doi
Node* get_Front(Queue queue){
	if(empty_Queue(queue)){
		printf("Queue is empty");
	}
	else{
		return queue.Elements[queue.front];
	}
}

void del_Queue(Queue *queue){
	if(!empty_Queue(*queue)){
		if(queue->front == queue->rear){
			makenull_Queue(queue);
		}
		else{
			queue->front=(queue->front+1)%Maxlength;
		}
	}
	else{
		printf("Error, Delete");
	}
}

void push_Queue(Node* x, Queue* queue){
	if(!full_Queue(*queue)){
		if(empty_Queue(*queue)){
			queue->front=0;
		}
		queue->rear=(queue->rear+1)%Maxlength;
		queue->Elements[queue->rear]=x;
	}
	else{
		printf("Error Push");
	}
}

void makenull_State(State *state){
	state->x=0;
	state->y=0;
}

void print_State(State state){
	printf("\n X:%d ---- Y:%d",state.x,state.y);
}

int compareQueue(State X, State Y){
	if(X.x==Y.x && X.y==Y.y){
		return 1;
	}
	else{
		return 0;
	}
}

int find_state(State state, Queue openQueue){
	while(!empty_Queue(openQueue)){
		if(compareQueue(get_Front(openQueue)->state,state)){
			return 1;
		}
		del_Queue(&openQueue);
	}
	return 0;
}

int goalcheck(State state){
	return (state.x==goal || state.y==goal);
}

int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x<tankcapacity_X){
		result->x=tankcapacity_X;
		result->y=cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state,State *result){
	if(cur_state.y>tankcapacity_Y){
		result->x=cur_state.x;
		result->y=tankcapacity_Y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x>0){
		result->x=empty;
		result->y=cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y>0){
		result->x=cur_state.x;
		result->y=empty;
		return 1;
	}
	return 0;
}

int max(int x, int y){
	if(x>=y){
		return 1;
	}
	return 0;
}

int min(int x, int y){
	if(x<=y){
		return 1;
	}
	return 0;
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x>0&&cur_state.y<tankcapacity_Y){
		result->x=max(cur_state.x-(tankcapacity_Y-cur_state.y),empty);
		result->y=min(cur_state.x+cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.y>0 && cur_state.x<tankcapacity_X){
		result->x=min(cur_state.x+cur_state.y,tankcapacity_X);
		result->y=max(cur_state.y-(tankcapacity_X-cur_state.x),empty);
		return 1;
	}
	return 0;
}

int call_operator(State cur_state,State *result,int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state,result);
		case 2: return pourWaterFullY(cur_state,result);
		case 3: return pourWaterEmptyX(cur_state,result);
		case 4: return pourWaterEmptyY(cur_state,result);
		case 5: return pourWaterXY(cur_state,result);
		case 6: return pourWaterYX(cur_state,result);
		default: printf("Error calls operator");
		return 0;
	}
}

const char* action[]={"First State","pour Water Full X","pour Water Full Y","pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"};

Node* BFS_Algorithm(State state){
	Queue Open_BFS;
	Queue Close_BFS;
	makenull_Queue(&Open_BFS);
	makenull_Queue(&Close_BFS);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function=0;
	push_Queue(root,&Open_BFS);
	while(!empty_Queue(Open_BFS)){
		Node* node = get_Front(Open_BFS);
		del_Queue(&Open_BFS);
		push_Queue(node,&Close_BFS);
		
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt=1;opt<=6;opt++){
			State newstate;
			makenull_State(&newstate);
			if(call_operator(node->state,&newstate,opt)){
				if(find_state(newstate,Close_BFS) || find_state(newstate,Open_BFS)){
					continue;
				}
				Node* newNode =(Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function=opt;
				push_Queue(newNode,&Open_BFS);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	Queue queuePrint;
	makenull_Queue(&queuePrint);
	while(node->Parent != NULL){
		push_Queue(node,&queuePrint);
		node = node->Parent;
	} 
	push_Queue(node,&queuePrint);
	int no_action =0;
	while(!empty_Queue(queuePrint)){
		printf("\n Action %d : %s",no_action,action[get_Front(queuePrint)->no_function]);
		print_State(get_Front(queuePrint)->state);
		del_Queue(&queuePrint);
		no_action++;
	}
}

int main(){
	State cur_state = {0,0};
	Node* p = BFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}
