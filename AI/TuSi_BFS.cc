#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<stack>
#define G 3

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
	if(X.so_quy == Y.so_quy && X.so_tusi== Y.so_tusi && X.vitri_thuyen == Y.vitri_thuyen){
		return 1;
	}
	return 0;
}

int findQueue(State state, queue<Node*> q){
	while (!q.empty()){
		if (compareStates(q.front()->state, state))
			return 1;
		q.pop();
	}
	return 0;
}

Node* BFS_Algorithm(State state){
	queue <Node*> open_bfs; 
	queue <Node*> close_bfs;
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	open_bfs.push(root);
	while (!open_bfs.empty()){
		Node* node = open_bfs.front();
		open_bfs.pop();
		close_bfs.push(node);
		if (goalcheck(node->state))
			return node;
		int opt;
		for (opt=1;opt<=6;opt++){
			State newstate;
			makenullState(&newstate);
			if (call_operator(node->state,&newstate,opt)){
				if (findQueue(newstate,open_bfs) == 1 || findQueue(newstate,close_bfs) == 1)
					continue;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function = opt;
				open_bfs.push(newNode);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* n){
    stack<Node*> stack;
    
	while (n->Parent != NULL){
		stack.push(n);
		n = n->Parent;
	}
	stack.push(n);
	int i = 0;
	while (!stack.empty()){
		printf("\n Action %d: %s", i, action[stack.top()->no_function]);
		printState(stack.top()->state);
		stack.pop();
		i++;
	}
}

int main(){
	State state={3,3,1};
	Node *p=BFS_Algorithm(state);
	print_WaysToGetGoal(p);
	return 0;
}
