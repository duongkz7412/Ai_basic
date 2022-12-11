#include<stdio.h>
#include<stdlib.h>
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define goal 6
#define empty 0
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
	int front,rear;
}Queue;

typedef struct{
	Node* Elements[Maxlength];
	int Top_idx;
}Stack;

void makenull_State(State *state){
	state->x=0;
	state->y=0;
}

int goalcheck(State state){
	return (state.x==goal||state.y==goal);
}

void print_State(State state){
	printf("\n	X:%d --- Y:%d",state.x,state.y);
}

int max(int x, int y){
	if(x>=y){
		return x;
	}
	return y;
}

int min(int x, int y){
	if(x<=y){
		return x;
	}
	return y;
}

int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x<tankcapacity_X){
		result->x=tankcapacity_X;
		result->y=cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y<tankcapacity_Y){
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

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x>0 && cur_state.y<tankcapacity_Y){
		result->x=max(cur_state.x-(tankcapacity_Y-cur_state.y),empty);
		result->y=min(cur_state.x+cur_state.y,tankcapacity_Y);
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

const char* action[]={"First State","pour Water Full X","pour Water Full Y","pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"};

void push_Queue(Node* x, Queue *queue){
	if(!full_Queue(*queue)){
		queue->front = 0;
		queue->rear = (queue->rear+1) % Maxlength;
		queue->Elements[queue->rear]=x;
	}
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

int compareStates(State X, State Y){
		return (X.x == Y.x) && (X.y == Y.y);
}

void makenull_Stack(Stack *stack){
	stack->Top_idx=Maxlength;
}

int empty_Stack(Stack stack){
	return stack.Top_idx==Maxlength;
}

int full_Stack(Stack *stack){
	return stack->Top_idx==0;
}

void push_Stack(Node* x, Stack *stack){
	if(full_Stack(stack)){
		printf("Error Stack is full");
	}
	else{
		stack->Top_idx-=1;
		stack->Elements[stack->Top_idx]=x;
	}
}

Node* top(Stack stack){
	if(!empty_Stack(stack)){
		return stack.Elements[stack.Top_idx];
	}
	return NULL;
} 

void pop_Stack(Stack *stack){
	if(!empty_Stack(*stack)){
		stack->Top_idx+=1;
	}
	else{
		printf("Error Stack is empty");
	}
}

//Node* BFS_Algorithm(State state){
//	Stack Open_BFS;
//	Stack Close_BFS;
//	makeNull_Queue(&Open_BFS);
//	makeNull_Queue(&Close_BFS);
//	
//	Node* root = (Node*)malloc(sizeof(Node));
//	root->state= state;
//	root->Parent=NULL;
//	root->no_function=0;
//	push_Queue(root,&Open_BFS);
//	
//	while(!empty_Queue(Open_BFS)){
//		Node* node = get_Front(Open_BFS);
//		del_Queue(&Open_BFS);
//		push_Queue(node,&Close_BFS);
//		
//		if(goalcheck(node->state)){
//			return node;
//		}
//		int opt;
//		for(opt=1;opt<=6;opt++){
//			State newstate;
//			makenull_State(&newstate);
//			if(call_operator(node->state,&newstate,opt)){
//				if(find_State(newstate,Close_BFS) || find_State(newstate,Open_BFS)){
//					continue;
//				}
//				Node* newNode = (Node*)malloc(sizeof(Node));
//				newNode->state=newstate;
//				newNode->Parent=node;
//				newNode->no_function=opt;
//				push_Queue(newNode,&Open_BFS);
//			}
//		}
//	}
//	return NULL;
//}

Node* BFS_AIgorithm(State state){
	Queue open_bfs, close_bfs;
	makeNull_Queue(&open_bfs);
	makeNull_Queue(&close_bfs);
	Node* root = (Node*)malloc(sizeof(Node));
	
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push_Queue(root,&open_bfs);
	while (!empty_Queue(open_bfs)){
		Node* node = get_Front(open_bfs);
		del_Queue(&open_bfs);
		push_Queue(node,&close_bfs);
		if (goalcheck(node->state))
			return node;
		int opt;
		for (opt=1;opt<=6;opt++){
			State newstate;
			makenull_State(&newstate);
			if (call_operator(node->state,&newstate,opt)){
				if (find_State(newstate,open_bfs) == 1 || find_State(newstate,close_bfs) == 1)
					continue;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function = opt;
				push_Queue(newNode,&open_bfs);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	Stack stackPrint;
	makenull_Stack(&stackPrint);
	while(node->Parent != NULL){
		push_Stack(node,&stackPrint);
		node = node->Parent;
	}
	push_Stack(node,&stackPrint);
	int no_action =0;
	while(!empty_Stack(stackPrint)){
		printf("\nAction %d : %s",no_action,action[top(stackPrint)->no_function]);
		print_State(top(stackPrint)->state);
		pop_Stack(&stackPrint);
		no_action++;
	}
}

int main() {
	State state = {0,0};
	Node* p=BFS_AIgorithm(state);
	print_WaysToGetGoal(p);
	return 0;
}



//#include <stdio.h>
//#include <stdlib.h>
//#define tankcapacity_x 9 //suc chua binh x
//#define tankcapacity_y 4 //suc chua binh y
//#define empty 0
//#define  goal 6 //Muc tieu can dong duoc
//#define  Maxlength 100 //Su dung cai dat ngan xep (Stack)
//
//const char* action[] = {"First State", "pour Water Full X","pour Water Ful Y",
//						"pour Water Empty X","pour Water Empty Y",
//						"pour Water X to Y","pour Water Y to X"};
//
//typedef struct{
//	int x; //luong nuoc trong binh x
//	int y; //luong nuoc trong binh y
//}State;
//
//typedef struct Node{
//	State state;
//	struct Node* parent;
//	int no_function;
//}Node;
//
//typedef struct{
//	Node* Elements[Maxlength];
//	int front, rear;
//}Queue;
//
//void makeNullQueue(Queue *q){
//	q->front = -1;
//	q->rear = -1;
//}
//
//int fullQueue(Queue q){
//	return ((q.rear - q.front + 1) % Maxlength == 0);
//}
//
//int emptyQueue(Queue q){
//	return q.front == -1;
//}
//
//void enQueue(Node* x, Queue *q){
//	if (!fullQueue(*q)){
//		if (emptyQueue(*q))
//			q->front = 0;
//		q->rear = (q->rear + 1) % Maxlength;
//		q->Elements[q->rear] = x;
//	}
//}
//
//void deQueue(Queue *q){
//	if (!emptyQueue(*q)){
//		if (q->front == q->rear)
//			makeNullQueue(q);
//		else
//			q->front = (q->front + 1) % Maxlength;
//	}
//}
//
//typedef struct{
//	Node* Elements[Maxlength];
//	int Top_idx;
//}Stack;
//
//Node* getFront(Queue q){
//	if (!emptyQueue(q))
//		return q.Elements[q.front];
//}
//
//
//
//void makeNullStack(Stack *s){
//	s->Top_idx = Maxlength;
//}
//
//int emptyStack(Stack s){
//	return s.Top_idx == Maxlength;
//}
//
//void pop(Stack *s){
//	s->Top_idx+=1;
//}
//
//void push(Node* x, Stack *s){
//	s->Top_idx-=1;
//	s->Elements[s->Top_idx]=x;
//}
//Node* Top(Stack s){
//	return s.Elements[s.Top_idx];
//}
//
//void makeNullState(State *state){
//	state->x = 0;
//	state->y = 0; 
//}
//
//void print_State(State state){
//	printf("\n   X: %d --- Y: %d\n",state.x,state.y);
//}
//
//int check_Goal(State state){
//	return (state.x == goal || state.y == goal);
//}
//
//int max(int x, int y){
//	return x > y ? x : y;
//}
//
//int min(int x, int y){
//	return x < y ? x : y;
//}
//
//int pourWaterFullX(State state, State *result){
//	if (state.x < tankcapacity_x){
//		result->x = tankcapacity_x;
//		result->y = state.y;
//		return  1;
//	}
//	return 0;
//}
//
//int pourWaterFullY(State state, State *result){
//	if (state.y < tankcapacity_y){
//		result->x = state.x;
//		result->y = tankcapacity_y;
//		return  1;
//	}
//	return 0;
//}
//
//int pourWaterEmptyX(State state, State *result){
//	if (state.x > empty){
//		result->x = empty;
//		result->y = state.y;
//		return  1;
//	}
//	return 0; 
//}
//
//int pourWaterEmptyY(State state, State *result){
//	if (state.y > empty){
//		result->x = state.x;
//		result->y = empty;
//		return  1;
//	}
//	return 0; 
//}
//
//int pourWaterXY(State state, State *result){
//	if (state.x > 0 && state.y < tankcapacity_y){
//		result->x = max(state.x - (tankcapacity_y - state.y), 0);
//		result->y = min(state.x + state.y, tankcapacity_y);
//		return 1;
//	}
//	return 0;
//}
//
//int pourWaterYX(State state, State *result){
//	if (state.y > 0 && state.x < tankcapacity_x){
//		result->x = min(state.y + state.x, tankcapacity_x);
//		result->y = max(state.y - (tankcapacity_x - state.x), 0);return 1;
//	}
//	return 0;
//}
//
//int call_operator (State cur_state, State *result, int option){
//	switch(option){
//		case 1:return pourWaterFullX(cur_state,result);
//		case 2:return pourWaterFullY(cur_state,result);
//		case 3:return pourWaterEmptyX(cur_state,result);
//		case 4:return pourWaterEmptyY(cur_state,result);
//		case 5:return pourWaterXY(cur_state,result);
//		case 6:return pourWaterYX(cur_state,result);
//		default:printf("ERROR calls operators");
//			return 0;
//	}
//}
//
//
//int compareState(State state1, State state2){
//		return (state1.x == state2.x) && (state1.y == state2.y);
//}
//
//int findQueue(State state, Queue q){
//	while (!emptyQueue(q)){
//		if (compareState(getFront(q)->state, state))
//			return 1;
//		deQueue(&q);
//	}
//	return 0;
//}
//
//Node* BFS_AIgorithm(State state){
//	Queue open_bfs, close_bfs;
//	makeNullQueue(&open_bfs);
//	makeNullQueue(&close_bfs);
//	Node* root = (Node*)malloc(sizeof(Node));
//	root->state = state;
//	root->parent = NULL;
//	root->no_function = 0;
//	enQueue(root,&open_bfs);
//	while (!emptyQueue(open_bfs)){
//		Node* node = getFront(open_bfs);
//		deQueue(&open_bfs);
//		enQueue(node,&close_bfs);
//		if (check_Goal(node->state))
//			return node;
//		int opt;
//		for (opt=1;opt<=6;opt++){
//			State newstate;
//			makeNullState(&newstate);
//			if (call_operator(node->state,&newstate,opt)){
//				if (findQueue(newstate,open_bfs) == 1 || findQueue(newstate,close_bfs) == 1)
//					continue;
//				Node* newNode = (Node*)malloc(sizeof(Node));
//				newNode->state = newstate;
//				newNode->parent = node;
//				newNode->no_function = opt;
//				enQueue(newNode,&open_bfs);
//			}
//		}
//	}
//	return NULL;
//}
//
//void print_WaysToGetGoal(Node* n){
//	Stack stack;
//	makeNullStack(&stack);
//	//Duyet nguoc ve nut parent
//	while (n->parent != NULL){
//		push(n,&stack);
//		n = n->parent;
//	}
//	push(n,&stack);
//	int i = 0;
//	while (!emptyStack(stack)){
//		printf("Action %d: %s", i, action[Top(stack)->no_function]);
//		print_State(Top(stack)->state);
//		pop(&stack);
//		i++;
//	}
//}
//
//int main() {
//	State state = {0,0};
//	Node* p=BFS_AIgorithm(state);
//	print_WaysToGetGoal(p);
//	return 0;
//}
