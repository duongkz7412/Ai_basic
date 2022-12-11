#include<stdio.h>
#define ROWS 3
#define COLS 3
#define empty 0
#define Maxlength 100

typedef struct{
	int eightPuzzel[ROWS][COLS];
	int emptyRow;
	int emptyCol;
}State;

const char *action[]={"First State","Move cell empty to Up",
					"Move cell empty to Down","Move cell empty to Left",
					"Move cell empty to Right"};

void printState(State state){
	int row,col;
	printf("\n----------\n");
	for(row =0;row<ROWS;row++){
		for(col=0;col<COLS;col++){
			printf("|%d ",state.eightPuzzel[row][col]);
		}
		printf("|\n");
	}
	printf("----------\n");
}

int compareState(State X, State Y){
	if(X.emptyRow != Y.emptyRow || X.emptyCol != Y.emptyCol){
		return 0;
	}
	int row,col;
	for(row=0;row<ROWS;row++){
		for(col=0;col<COLS;col++){
			if(X.eightPuzzel[row][col] != Y.eightPuzzel[row][col]){
				return 0;
			}
		}
	}
	return 1;
}

int goalcheck(State state, State goal){
	return compareState(state,goal);
}

int upOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow;
	int empColCurrent = state.emptyCol;
	if(empRowCurrent >0){
		result->emptyRow=empRowCurrent-1;
		result->emptyCol=empColCurrent;
		result->eightPuzzel[empRowCurrent][empColCurrent]=state.eightPuzzel[empRowCurrent-1][empColCurrent];
		result->eightPuzzel[empRowCurrent-1][empColCurrent]=empty;
		return 1;
	}
	return 0;
}

int dowOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow;
	int empColCurrent = state.emptyCol;
	if(empRowCurrent >0 ){
		result->emptyRow=empRowCurrent+1;
		result->emptyCol=empColCurrent;
		result->eightPuzzel[empRowCurrent][empColCurrent]=state.eightPuzzel[empRowCurrent+1][empColCurrent];
		result->eightPuzzel[empRowCurrent+1][empColCurrent]=empty;
		return 1;
	}
	return 0;
}

int leftOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow;
	int empColCurrent = state.emptyCol;
	if(empColCurrent >0){
		result->emptyRow=empRowCurrent;
		result->emptyCol=empColCurrent-1;
		result->eightPuzzel[empRowCurrent][empColCurrent]= state.eightPuzzel[empRowCurrent][empColCurrent-1];
		result->eightPuzzel[empRowCurrent][empColCurrent-1]=empty;
		return 1;
	}
	return 0;
}

int rightOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow;
	int empColCurrent = state.emptyCol;
	if(empColCurrent > 0){
		result->emptyRow=empRowCurrent;
		result->emptyCol=empColCurrent+1;
		result->eightPuzzel[empRowCurrent][empColCurrent] =state.eightPuzzel[empRowCurrent][empColCurrent+1];
		result->eightPuzzel[empRowCurrent][empColCurrent+1] = empty;
		return 1;
	}
	return 0;
}

int call_operation(State state, State *result, int option){
	switch(option){
		case 1: return upOperator(state,result);
		case 2: return dowOperator(state,result);
		case 3: return leftOperator(state,result);
		case 4: return rightOperator(state,result);
		default:
			return 0;
	}
}

int main(){
	State state,result;
	state.emptyRow=1;
	state.emptyCol=1;
	state.eightPuzzel[0][0] = 3;
	state.eightPuzzel[0][1] = 4;
	state.eightPuzzel[0][2] = 5;
	state.eightPuzzel[1][0] = 1;
	state.eightPuzzel[1][1] = 0;
	state.eightPuzzel[1][2] = 2;
	state.eightPuzzel[2][0] = 6;
	state.eightPuzzel[2][1] = 7;
	state.eightPuzzel[2][2] = 8;
	printf("Trang thai bat dau\n");
	printState(state);
	int opt;
	for(opt=1;opt<=4;opt++){
		call_operation(state,&result,opt);
		if(!compareState(state,result)){
			printf("Hanh dong %s thanh cong\n",action[opt]);
			printState(result);
		}
		else{
			printf("Hanh dong %s khong thanh cong \n",action[opt]);
		}
	}
	return 0;
}
