#include <stdio.h>
#include <stdlib.h>
#define tankcapacity_x 9 //suc chua binh x
#define tankcapacity_y 4 //suc chua binh y
#define Empty 0
#define  goal 6 //Muc tieu can dong duoc
#define  Maxlength 100 //Su dung cai dat ngan xep (Stack)
#include <stack>

using namespace std;

const char* action[] = {"First State", "pour Water Full X","pour Water Ful Y",
						"pour Water Empty X","pour Water Empty Y",
						"pour Water X to Y","pour Water Y to X"};

typedef struct{
	int x,y;
}State;

typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
}Node;

void makeNullState(State *state){
	state->x = 0;
	state->y = 0; 
}

void print_State(State state){
	printf("\n   X: %d --- Y: %d\n",state.x,state.y);
}

int check_Goal(State state){
	return (state.x == goal || state.y == goal);
}

int max(int x, int y){
	return (x > y)? x : y;
}

int min(int x, int y){
	return (x < y)? x : y;
}

int pourWaterFullX(State state, State *result){
	if (state.x < tankcapacity_x){
		result->x = tankcapacity_x;
		result->y = state.y;
		return  1;
	}
	return 0;
}

int pourWaterFullY(State state, State *result){
	if (state.y < tankcapacity_y){
		result->x = state.x;
		result->y = tankcapacity_y;
		return  1;
	}
	return 0;
}

int pourWaterEmptyX(State state, State *result){
	if (state.x > Empty){
		result->x = Empty;
		result->y = state.y;
		return  1;
	}
	return 0; 
}

int pourWaterEmptyY(State state, State *result){
	if (state.y > Empty){
		result->x = state.x;
		result->y = Empty;
		return  1;
	}
	return 0; 
}

int pourWaterXY(State state, State *result){
	if (state.x > 0 && state.y < tankcapacity_y){
		result->x = max(state.x - (tankcapacity_y - state.y), 0);
		result->y = min(state.x + state.y, tankcapacity_y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State state, State *result){
	if (state.y > 0 && state.x < tankcapacity_x){
		result->x = min(state.y + state.x, tankcapacity_x);
		result->y = max(state.y - (tankcapacity_x - state.x), 0);
		return 1;
	}
	return 0;
}

int call_operator(State state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(state,result);
		case 2: return pourWaterFullY(state,result);
		case 3: return pourWaterEmptyX(state,result);
		case 4: return pourWaterEmptyY(state,result);
		case 5: return pourWaterXY(state,result);
		case 6: return pourWaterYX(state,result);
		default: printf("Error calls operators");
			return 0;
	}
}

int compareState(State state1, State state2){
		return (state1.x == state2.x) && (state1.y == state2.y);
}

int findStack(State state, stack<Node*> s){
	while (!s.empty()){
		if (compareState(s.top()->state, state))
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
	root->parent = NULL;
	root->no_function = 0;
	open_dfs.push(root);
	while (!open_dfs.empty()){
		Node* node = open_dfs.top();
		open_dfs.pop();
		close_dfs.push(node);
		if (check_Goal(node->state))
			return node;
		int opt;
		for (opt=1;opt<=6;opt++){
			State result;
			makeNullState(&result);
			if (call_operator(node->state,&result,opt)){
				if (findStack(result,open_dfs) == 1 || findStack(result,close_dfs) == 1)
					continue;
				Node* m = (Node*)malloc(sizeof(Node));
				m->state = result;
				m->parent = node;
				m->no_function = opt;
				open_dfs.push(m);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	stack<Node*> stackprint;
	while (node->parent != NULL){
		stackprint.push(node);
		node = node->parent;
	}
	stackprint.push(node);
	int i = 0;
	while (!stackprint.empty()){
		printf("Action %d: %s", i, action[stackprint.top()->no_function]);
		print_State(stackprint.top()->state);
		stackprint.pop();
		i++;
	}
}

int main() {
	State state = {0,0};
	Node* p=DFS_AIgorithm(state);
	print_WaysToGetGoal(p);
	return 0;
}
