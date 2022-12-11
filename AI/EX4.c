#include<stdio.h>
#define tankcapacity_X 
#define goal 8
#define Maxlength 100

typedef struct{
	int x;
	int y; 	
	int z;
}State;

void makenull_State(State *state){
	state->x=0;
	state->y=0;
	state->z=0;
}

int goalcheck(State state){
	return (state.x==goal || state.y==goal || state.z == goal);
}

int max(int X, int Y){
	if(X>=Y || X >= ){
		return X;
	}
	return Y;
}

int min(int X, int Y){
	if(X<=Y){
		return X;
	}
	return Y;
}

int pourWaterFullX(State cur_state,State *result){
	if()
}
