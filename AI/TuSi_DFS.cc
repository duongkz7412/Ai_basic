#include<stdio.h>
#include<stdlib.h>
#include<stack>
#define G 3
#define Maxlength 100

using namespace std;

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
	return (X.so_quy == Y.so_quy && X.so_tusi== Y.so_tusi && X.vitri_thuyen == Y.vitri_thuyen);
}

int findStack(State state, stack<Node*> s){
	while (!s.empty()){
		if (compareStates(s.top()->state, state))
			return 1;
		s.pop();
	}
	return 0;
}

Node* DFS_AIgorithm(State state){
	stack <Node*> open_dfs;
	stack <Node*> close_dfs;
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	open_dfs.push(root);
	while (!open_dfs.empty()){
		Node* node = open_dfs.top();
		open_dfs.pop();
		close_dfs.push(node);
		if (goalcheck(node->state))
			return node;
		int opt;
		for (opt=1;opt<=6;opt++){
			State result;
			makenullState(&result);
			if (call_operator(node->state,&result,opt)){
				if (findStack(result,open_dfs) == 1 || findStack(result,close_dfs) == 1)
					continue;
				Node* m = (Node*)malloc(sizeof(Node));
				m->state = result;
				m->Parent = node;
				m->no_function = opt;
				open_dfs.push(m);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	stack<Node*> stackprint;
	while (node->Parent != NULL){
		stackprint.push(node);
		node = node->Parent;
	}
	stackprint.push(node);
	int i = 0;
	while (!stackprint.empty()){
		printf("\n Action %d: %s", i, action[stackprint.top()->no_function]);
		printState(stackprint.top()->state);
		stackprint.pop();
		i++;
	}
}


int main(){
	State state={3,3,1};
	Node *p=DFS_AIgorithm(state);
	print_WaysToGetGoal(p);
	return 0;
}
