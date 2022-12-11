#include <stdio.h>
#include <stdlib.h>
#define tankcapacity_X 9 //suc chua binh x
#define tankcapacity_Y 4 //suc chua binh y
#define empty 0
#define  goal 6 //Muc tieu can dong duoc
#define  Maxlength 100 //Su dung cai dat ngan xep (Stack)

const char* action[] = {"First State", "pour Water Full X","pour Water Ful Y",
						"pour Water Empty X","pour Water Empty Y",
						"pour Water X to Y","pour Water Y to X"};

typedef struct{
	int x; //luong nuoc trong binh x
	int y; //luong nuoc trong binh y
}State;

void makeNullState (State *state){
	state->x =0;
	state->y =0;
}

void print_State(State state){
	printf("\n	X:%d --- Y:%d",state.x,state.y);
}

int goalcheck(State state){
	return (state.x==goal || state.y==goal);
}

int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x<tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y<tankcapacity_Y){
		result->y=tankcapacity_Y;
		result->x=cur_state.x;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x>0){
		result->x = empty;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y>0){
		result->y = empty;
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x>0 && cur_state.y<tankcapacity_Y){
		result->x=max(cur_state.x - (tankcapacity_Y-cur_state.y),empty);
		result->y=min(cur_state.x + cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.y>0 && cur_state.x<tankcapacity_X){
		result->y=max(cur_state.y-(tankcapacity_X-cur_state.x),empty);
		result->x=min(cur_state.x+cur_state.y,tankcapacity_X);
		return 1;
	}
	return 0;
}

int call_operator (State cur_state, State *result, int option){
	switch(option){
		case 1:return pourWaterFullX(cur_state,result);
		case 2:return pourWaterFullY(cur_state,result);
		case 3:return pourWaterEmptyX(cur_state,result);
		case 4:return pourWaterEmptyY(cur_state,result);
		case 5:return pourWaterXY(cur_state,result);
		case 6:return pourWaterYX(cur_state,result);
		default:printf("ERROR calls operators");
			return 0;
	}
}

int min(int x, int y){
	if(x<y){
		return x;
	}
	else return y;
}
int max(int x, int y){
	if(x>y){
		return x;
	}
	else return y;
}

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int front,rear;
}Queue;

void push_Queue(Node* x, Queue *queue){
	if(!full_Queue(*queue)){
		queue->front = 0;
		queue->rear = (queue->rear+1) % Maxlength;
		queue->Elements[queue->rear]=x;
	}
	else printf("Error, Push");
}

//Khoi tao hang doi rong
void makeNull_Queue(Queue *queue){
	queue->front = -1;
	queue->rear = -1;
}

//Kiem tra hang doi day
int full_Queue(Queue queue){
	return ((queue.rear-queue.front+1)%Maxlength)==0;
}

//Kiem tra xem hang doi co rong khong
int empty_Queue(Queue queue){
	return queue.front == -1;
}

//Tra ve phan tu dau hang doi
Node* get_Front(Queue queue){
	if(empty_Queue(queue))
		printf("Queue is empty");
	else
		return queue.Elements[queue.front];
}

//Xoa bo p=mot phan tu khoi hang doi
void del_Queue(Queue *queue){
	if(!empty_Queue(*queue)){
		if(queue->front==queue->rear)
			makeNull_Queue(queue);
		else queue->front = (queue->front+1)%Maxlength;
	}
	else printf("Error,Delete");
}

int find_State(State state, Queue openQueue){
	while (!empty_Queue(openQueue)){
		if(compareStates(get_Front(openQueue)->state,state))
			return 1;
		del_Queue(&openQueue);
	}
	return 0;
}

int compareStates(State state1, State state2){
		return (state1.x == state2.x) && (state1.y == state2.y);
}

//Duyet theo chieu sau
Node* DFS_Algorithm(State state){
	Queue Open_DFS;
	Queue Close_DFS;
	makeNull_Queue(&Open_DFS);
	makeNull_Queue(&Close_DFS);
	Node* root=(Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->no_function=0;
	push_Queue(root,&Open_DFS);
	
	while(!empty_Queue(Open_DFS)){
		Node* node= get_Front(Open_DFS);
		del_Queue(&Open_DFS);
		push_Queue(node,&Close_DFS);
		if(goalcheck(node->state))
			return node;
		int opt;
		for(opt=1;opt<=6;opt++){
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate,opt)){
				if(find_State(newstate, Close_DFS)==1|| find_State(newstate, Open_DFS)==1)
				 continue;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				push_Queue(newNode,&Open_DFS);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	Queue queuePrint;
	makeNull_Queue(&queuePrint);
	while(node->Parent!=NULL){
		push_Queue(node,&queuePrint);
		node=node->Parent;
	}
	push_Queue(node,&queuePrint);
	int no_action=0;
	while(!empty_Queue(queuePrint)){
		printf("\nAction %d:%s", no_action,action[get_Front(queuePrint)->no_function]);
		print_State(get_Front(queuePrint)->state);
		del_Queue(&queuePrint);
		no_action++;
	}
}

int main(){
	State cur_state = {0,0};
	print_WaysToGetGoal(DFS_Algorithm(cur_state));
	return 0;
}
