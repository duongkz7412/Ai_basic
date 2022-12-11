#include<stdio.h>
#include<stdlib.h>
#define tankcapacity_x 9
#define tankcapacity_y 4
#define empty 0
#define goal 6
#define Maxlength 100 

typedef struct{
	int x;
	int y;
}State;

//khoi tao trang thai trong binh
void makenullState(State *state){
	state->x=0;
	state->y=0;
}

//in trang thai 
void print_State(State state){
	printf("\n x:%d --- y:%d",state.x,state.y);
}

//ham kiem tra trang thai muc tieureturn
int goalcheck(State state){
	return(state.x==goal || state.y==goal);
}

// lam day nuoc binh X
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_x){
		result->x =tankcapacity_x;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

//lam day binh Y
int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < tankcapacity_y){
		result->x=cur_state.x;
		result->y=tankcapacity_y;
		return 1;
	}
	return 0;
}

//lam rong binh X
int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x >0){
		result->x=empty;
		result->y=cur_state.y;
		return 1;
	}
	return 0;
}

//lam  rong binh Y
int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y >0){
		result->x=cur_state.x;
		result->y=empty;
		return 1;
	}
	return 0;
}

//ham min
int min(int x, int y){
	if(x<= y){
		return x;
	}
	else{
		return y;
	}
}

int max(int x, int y){
	if(x >= y){
		return x;
	}
	else{
		return y;
	}
}

//chuyen nuoc tu X -> Y
int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 && cur_state.y<tankcapacity_y){
		result->x=max(cur_state.x - (tankcapacity_y - cur_state.y),empty );
		result->y=min( (cur_state.x+cur_state.y),tankcapacity_y);
		return 1;
	}
	return 0;
}

//chuyen nuoc tu Y -> X
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > 0 && cur_state.x < tankcapacity_x){
		result->x=min((cur_state.x+cur_state.y),tankcapacity_x);
		result->y=max(cur_state.y-(tankcapacity_x-cur_state.x),empty);
		return 1;
	}
	return 0;
}

//goi cac hanh dong
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state,result);
		case 2: return pourWaterFullY(cur_state,result);
		case 3: return pourWaterEmptyX(cur_state,result);
		case 4: return pourWaterEmptyY(cur_state,result);
		case 5: return pourWaterXY(cur_state,result);
		case 6: return pourWaterYX(cur_state,result);
		default: printf("Errol calls operators");
		 	return 0;
	}
}

const char* action[] = {"First State", "pour Water Full X","pour Water Full Y","pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"};

int main(){
	State cur_state = {5,4}, result;
	printf("Trang thai bat dau");
	print_State(cur_state);
	int opt;
	for(opt=1;opt<=6;opt++){
		int thuchien = call_operator(cur_state,&result,opt);
		if(thuchien == 1){
			printf("\nHanh dong %s thanh cong",action[opt]);
			print_State(result);
		}
		else{
			printf("\nHanh dong %s KHONG thanh cong", action[opt]);
		}
	}
}

