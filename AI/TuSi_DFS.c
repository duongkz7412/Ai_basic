#include<stdio.h>
#include<stdlib.h>
#define G 3
#define Maxlength 100

typedef struct{
	int so_tusi;
	int so_quy;
	char vitri_thuyen;
}State;

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function; 
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int top_idx;
}Stack;

const char* action[] ={"First State","Chuyen 1 Quy",
						"Chuyen 1 Tu Si","Chuyen 2 Quy",
						"Chuyen 2 Tu Si","Chuyen 1 Quy 1 Tu Si"};

void makenullState(State *state){
	state->so_quy=G;
	state->so_tusi=G;
	state->vitri_thuyen=1;
}

void printState(State state){
	printf("\n quy: %d --- tusi: %d --- vi tri thuyen: %d",state.so_quy,state.so_tusi,state.vitri_thuyen);
}

int goalcheck(State state){
	return(state.so_quy==0 && state.so_tusi == 0);
}

int max(int a, int b){
	if(a>=b){
		return a;
	}
	return b;
}

int min(int a, int b){
	if(a<=b){
		return a;
	}
	return b;
}

void makenullStack(Stack *stack){
	stack->top_idx=Maxlength;
}

int empty_Stack(Stack stack){
	return stack.top_idx==Maxlength;
}

int full_Stack(Stack stack){
	return stack.top_idx==0;
}

void Push(Node* x, Stack *stack){
	if(full_Stack(*stack)){
		printf("Error");
	}
	else{
		stack->top_idx-=1;
		stack->Elements[stack->top_idx]=x;
	}
}

void pop(Stack *stack){
	if(!empty_Stack(*stack)){
		stack->top_idx+=1;
	}
}

Node* top(Stack stack){
	if(!empty_Stack(stack)){
		return stack.Elements[stack.top_idx];
	}
	else{
		return NULL;
	}
}

int DieuKien(State state){
	if(state.so_quy<0||state.so_quy> G || state.so_tusi <0 | state.so_tusi>G){
		return 0;
	}
	else{
		return (state.so_tusi==G||state.so_quy==state.so_tusi||state.so_tusi==0);
	}
}

int TuSi(State cur_state,State *result){
	if(cur_state.vitri_thuyen==1){
		cur_state.so_tusi= cur_state.so_tusi-1;
	}
	else{
		cur_state.so_tusi=cur_state.so_tusi+1;
	}
	if(DieuKien(cur_state)){
		result->so_quy=cur_state.so_quy;
		result->so_tusi=cur_state.so_tusi;
		result->vitri_thuyen=-cur_state.vitri_thuyen;
		return 1;
	}
	return 0;
}

int Quy(State cur_state,State *result){
	if(cur_state.vitri_thuyen==1){
		cur_state.so_quy=cur_state.so_quy-1;
	}
	else{
		cur_state.so_quy=cur_state.so_quy+1;
	}
	if(DieuKien(cur_state)){
		result->so_quy=cur_state.so_quy;
		result->so_tusi=cur_state.so_tusi;
		result->vitri_thuyen=-cur_state.vitri_thuyen;
		return 1;
	}
	return 0;
}

int TuSix2(State cur_state,State *result){
	if(cur_state.vitri_thuyen==1){
		cur_state.so_tusi=cur_state.so_tusi-2;
	}
	else{
		cur_state.so_tusi=cur_state.so_tusi+2;
	}
	if(DieuKien(cur_state)){
		result->so_quy=cur_state.so_quy;
		result->so_tusi=cur_state.so_tusi;
		result->vitri_thuyen=-cur_state.vitri_thuyen;
		return 1;
	}
	return 0;
}

int Quyx2(State cur_state ,State *result){
	if(cur_state.vitri_thuyen==1){
		cur_state.so_quy=cur_state.so_quy-2;
	}
	else{
		cur_state.so_quy=cur_state.so_quy+2;
	}
	if(DieuKien(cur_state)){
		result->so_quy=cur_state.so_quy;
		result->so_tusi=cur_state.so_tusi;
		result->vitri_thuyen=-cur_state.vitri_thuyen;
		return 1;
	}
	return 0;
}

int Quy_TuSi(State cur_state,State *result){
	if(cur_state.vitri_thuyen==1){
		cur_state.so_quy=cur_state.so_quy-1;
		cur_state.so_tusi=cur_state.so_tusi-1;
	}
	else{
		cur_state.so_quy=cur_state.so_quy+1;
		cur_state.so_tusi=cur_state.so_tusi+1;
	}
	if(DieuKien(cur_state)){
		result->so_quy=cur_state.so_quy;
		result->so_tusi=cur_state.so_tusi;
		result->vitri_thuyen=-cur_state.vitri_thuyen;
		return 1;
	}
	return 0;
}

int call_operator(State cur_state,State *result,int option){
	switch(option){
		case 1: return Quy(cur_state,result);
		case 2: return TuSi(cur_state,result);
		case 3: return Quyx2(cur_state,result);
		case 4: return TuSix2(cur_state,result);
		case 5: return Quy_TuSi(cur_state,result);
		default : 
		return 0;
	}
}

int compareStates(State X, State Y){
	if(X.so_quy == Y.so_quy && X.so_tusi== Y.so_tusi && X.vitri_thuyen == Y.vitri_thuyen){
		return 1;
	}
	return 0;
}

int find_State(State state,Stack openStack){
	while(!empty_Stack(openStack)){
		if(compareStates(top(openStack)->state,state)){
			return 1;
		}
		pop(&openStack);
	}
	return 0;
}

Node* DFS_Algorithm(State state){
	Stack Open_DFS;
	Stack Close_DFS;
	makenullStack(&Open_DFS);
	makenullStack(&Close_DFS);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->no_function=0;
	Push(root,&Open_DFS);
	
	while(!empty_Stack(Open_DFS)){
		Node* node=top(Open_DFS);
		pop(&Open_DFS);
		Push(node,&Close_DFS);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt=1;opt<=6;opt++){
			State newstate;
			makenullState(&newstate);
			if(call_operator(node->state,&newstate,opt)){
				if(find_State(newstate,Open_DFS) || find_State(newstate,Close_DFS)){
					continue;
				}
				Node* newNode =(Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				Push(newNode,&Open_DFS);
			}
		}
	}
	return NULL;
}

void Print_WaysToGetGoal(Node* node){
	Stack stackPrint;
	makenullStack(&stackPrint);
	
	while(node->Parent != NULL){
		Push(node,&stackPrint);
		node=node->Parent;
	}
	Push(node,&stackPrint);
	int no_action= 0;
	while(!empty_Stack(stackPrint)){
		printf("\n Action %d : %s",no_action,action[top(stackPrint)->no_function]);
		printState(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}

int main(){
	State state={3,3,1};
	Print_WaysToGetGoal(DFS_Algorithm(state));
	return 0;
}
