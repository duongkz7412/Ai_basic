#include<stdio.h>
#define tankcapacity_X 9
#define tankcapacity_y 4
#define goal 6
#define empty 0
#define Maxlength 100

typedef struct{
	int x;
	int y;
}State;

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

void makenull_State(State *state){
	state->x=0;
	state->y=0;
}

int goalcheck(State state){
	return (state.x == goal || state.y==goal);
}

void print_State(State state){
	printf("\n X:%d ---- Y:%d",state.x,state.y);
}

int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x<tankcapacity_X){
		result->x= tankcapacity_X;
		result->y= cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state,State *result){
	if(cur_state.y<tankcapacity_y){
		result->x=cur_state.x;
		result->y=tankcapacity_y;
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
	if(cur_state.x>0 && cur_state.y < tankcapacity_y){
		result->x=max(cur_state.x-(tankcapacity_Y-cur_state.y),empty);
		result->y=min(cur_state.x+cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state,State *result){
	if(cur_state.y>0 && cur_state.x<tankcapacity_X){
		result->x=min(cur_state.x+cur_state.y,tankcapacity_X);
		result->y=max(cur_state.y-(tankcapacity_X-cur_state.x),empty);
		return 1;
	}
	return 0;
}

int call_operator(State cur_state, State *result,int option){
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

const char* action[]={"First state","pour Water Full X",
"pour Water Full Y","pour Water Empty X",
"pour Water Empty Y","pour Water X to Y","pour Water Y to X"};

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int top_idx;
}Stack;

void makenull_Stack(Stack *stack){
	stack->top_idx==Maxlength;
}

int empty_Stack(Stack stack){
	return stack.top_idx==Maxlength;
}

int full_Stack(Stack stack){
	return stack.top_idx==0;
}

Node* top(Stack stack){
	if(!empty_Stack(stack)){
		return stack.Elements[stack.top_idx];
	}
	return NULL;
}

void pop(Stack *stack){
	if(!empty_Stack(stack)){
		stack->top_idx+=1;
	}
	else{
		printf("Error stack is empty");
	}
}

int compareStates(State X, State Y){
	if(X.x == Y.x && X.y == Y.y){
		return 1;
	}
	return 0;
}

int findState(State Stack openStack){
	while(!empty_Stack(openStack)){
		if(compareStates(top(openStack)->state,state)){
			return 1;
		}
		pop(&openStack);
	}
	return 0;
}


//
//void push_Stack(Stack *stack){
//	if
//}
