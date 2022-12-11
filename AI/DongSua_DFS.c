#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define tankcapacity_A 10
#define tankcapacity_B 5
#define tankcapacity_C 6
#define goal 8
#define empty 0
#define Maxlength 100

typedef struct{
	int A;
	int B;
	int C;
}State;

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int Top_idx;
}Stack;

void makenull_State(State *state){
	state->A=0;
	state->B=0;
	state->C=0;
}

int goalcheck(State state){
	return (state.A == goal || state.B == goal || state.C == goal);
}

void print_State(State state){
	printf("\n A:%d -- B:%d -- C:%d",state.A,state.B,state.C);
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

int pourWaterAB(State cur_state,State *result){
	if(cur_state.A >0 && cur_state.B <tankcapacity_B){
		result->A=max(cur_state.A-(tankcapacity_B-cur_state.B),empty);
		result->B=min(cur_state.A+cur_state.B,tankcapacity_B);
		result->C=cur_state.C;
		return 1;
	}
	return 0;
}

int pourWaterAC(State cur_state, State *result){
	if(cur_state.A>0 && cur_state.C<tankcapacity_C){
		result->A=max(cur_state.A-(tankcapacity_C - cur_state.C),empty);
		result->B=cur_state.B;
		result->C=min(cur_state.A+cur_state.C,tankcapacity_C);
		return 1;
	}
	return 0;
}

int pourWaterBA(State cur_state, State *result){
	if(cur_state.B > 0 && cur_state.A < tankcapacity_A){
		result->A=min(cur_state.A+cur_state.B,tankcapacity_A);
		result->B=max(cur_state.B-(tankcapacity_A-cur_state.A),empty);
		result->C=cur_state.C;
		return 1;
	}
	return 0;
}

int pourWaterBC(State cur_state, State *result){
	if(cur_state.B>0 && cur_state.C<tankcapacity_C){
		result->A=cur_state.A;
		result->B=max(cur_state.B -(tankcapacity_C-cur_state.C),empty);
		result->C=min(cur_state.B+cur_state.C,tankcapacity_C);
		return 1;
	}
	return 0;
}

int pourWaterCA(State cur_state, State *result){
	if(cur_state.C>0 && cur_state.A<tankcapacity_A){
		result->A=min(cur_state.A+cur_state.C,tankcapacity_A);
		result->B=cur_state.B;
		result->C=max(cur_state.C-(tankcapacity_A-cur_state.A),empty);
		return 1;
	}
	return 0;
}

int pourWaterCB(State cur_state, State *result){
	if(cur_state.C>0 && cur_state.B < tankcapacity_B){
		result->A=cur_state.A;
		result->B=min(cur_state.B+cur_state.C,tankcapacity_B);
		result->C=max(cur_state.C-(tankcapacity_B-cur_state.B),empty);
		return 1;
	}
	return 0;
}

int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterAB(cur_state,result);
		case 2: return pourWaterAC(cur_state,result);
		case 3: return pourWaterBA(cur_state,result);
		case 4: return pourWaterBC(cur_state,result);
		case 5: return pourWaterCA(cur_state,result);
		case 6: return pourWaterCB(cur_state,result);
		default: printf("Error");
		return 0;
	}
}

const char* action[]={"First State","pour Water A to B",
						"pour Water A to C","pour Water B to A",
						"pour Water B to C","pour Water C to A",
						"pour Water C to B"};

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

int compareStates(State X, State Y){
	if( (X.A == Y.A) && (X.B == Y.B) &&(X.C == Y.C) ){
		return 1;
	}
	return 0;
}

int find_State(State state, Stack openStack){
	while(!empty_Stack(openStack)){
		if(compareStates(top(openStack)->state,state)){
			return 1;
		}
		pop_Stack(&openStack);
	}
	return 0;
}

Node* DFS_Algorithm(State state){
	Stack Open_DFS;
	Stack Close_DFS;
	makenull_Stack(&Open_DFS);
	makenull_Stack(&Close_DFS);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state= state;
	root->Parent=NULL;
	root->no_function=0;
	push_Stack(root,&Open_DFS);
	
	while(!empty_Stack(Open_DFS)){
		Node* node = top(Open_DFS);
		pop_Stack(&Open_DFS);
		push_Stack(node,&Close_DFS);
		
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt=1;opt<=6;opt++){
			State newstate;
			makenull_State(&newstate);
			if(call_operator(node->state,&newstate,opt)){
				if(find_State(newstate,Close_DFS) || find_State(newstate,Open_DFS)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				push_Stack(newNode,&Open_DFS);
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
		printf("\nAction %d : a%s",no_action,action[top(stackPrint)->no_function]);
		print_State(top(stackPrint)->state);
		pop_Stack(&stackPrint);
		no_action++;
	}
}

int main(){
	State cur_state = {10,0,0};
	Node* p=DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}
