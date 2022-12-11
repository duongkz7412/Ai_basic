#include<stdio.h>
#include<stdlib.h>
#define ROWS 3
#define COLS 3
#define empty 0
#define Maxlength 500
#define Max_Operator 4

const char* action[]= {"First State","Move cell EMPTY to UP",
						"Move cell EMPTY to DOWN","Move cell EMPTY to LEFT",
						"Move cell EMPTY to RIGHT"};

typedef struct{
	int eightPuzzel[ROWS][COLS];
	int emptyRow;
	int emptyCol;
}State;

void Print_State(State state){
	int row,col;
	printf("\n----------\n");
	for(row=0;row<ROWS;row++){
		for(col=0;col<COLS;col++){
			printf("|%d",state.eightPuzzel[row][col]);
		}
		printf("|\n");
	}
	printf("----------\n");
}

int compareStates(State X,State Y){
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

int goalcheck(State state,State goal){
	return compareStates(state,goal);
}

int upOperator(State state, State *result){
	*result = state;
	int emptyRowCurrent = state.emptyRow;
	int emptyColCurrent = state.emptyCol;
	if(emptyRowCurrent > 0){
		result->emptyRow= emptyRowCurrent-1;
		result->emptyCol=emptyColCurrent;
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent-1][emptyColCurrent];
		result->eightPuzzel[emptyRowCurrent-1][emptyColCurrent] = empty;
		return 1;
	}
	return 0;
}

int dowOperator(State state, State *result){
	*result = state;
	int emptyRowCurrent = state.emptyRow;
	int emptyColCurrent = state.emptyCol;
	if(emptyRowCurrent < 2){
		result->emptyRow= emptyRowCurrent+1;
		result->emptyCol=emptyColCurrent;
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent+1][emptyColCurrent];
		result->eightPuzzel[emptyRowCurrent+1][emptyColCurrent] = empty;
		return 1;
	}
	return 0;
}

int lefOperator(State state,State *result){
	*result=state;
	int emptyRowCurrent = state.emptyRow;
	int emptyColCurrent = state.emptyCol;
	if(emptyColCurrent >0){
		result->emptyRow = emptyRowCurrent;
		result->emptyCol = emptyColCurrent-1;
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent-1];
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent-1]=empty;
		return 1;
	}
	return 0;
}

int rightOperator(State state,State *result){
	*result=state;
	int emptyRowCurrent = state.emptyRow;
	int emptyColCurrent = state.emptyCol;
	if(emptyColCurrent <2 ){
		result->emptyRow = emptyRowCurrent;
		result->emptyCol = emptyColCurrent+1;
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent+1];
		result->eightPuzzel[emptyRowCurrent][emptyColCurrent+1]=empty;
		return 1;
	}
	return 0;
}

int callOperator(State state,State *result,int opt){
	switch(opt){
		case 1: return upOperator(state,result);
		case 2: return dowOperator(state,result);
		case 3: return lefOperator(state,result);
		case 4: return rightOperator(state,result);
		default:
			return 0;
	}
}

int heuristic1 (State state, State goal){
	int row,col,count=0;
	for(row=0;row<ROWS;row++){
		for(col=0;col<COLS;col++){
			if(state.eightPuzzel[row][col] != goal.eightPuzzel[row][col]){
				count++;
			}
		}
	}
	return count;
}

int heuristic2 (State state, State goal){
	int count =0;
	int row,col,row_g,col_g;
	for(row=0; row<ROWS;row++){
		for(col=0;col<COLS;col++){
			if(state.eightPuzzel[row][col] != empty){
				for(row_g=0; row_g<ROWS;row_g++){
					for(col_g=0;col_g<COLS;col_g++){
						if(state.eightPuzzel[row][col] == goal.eightPuzzel[row_g][col_g]){
							count += abs(row-row_g) + abs(col-col_g);
							col_g=COLS;
							row_g=ROWS;
						}
					}
				}
			}
		}
	}
	return count;
}

typedef struct Node{
	State state;
	struct Node *Parent;
	int no_function;
	int heuristic;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int size;
}List;

void makenull_List(List *L){
	L->size=0;
}

int empty_List(List L){
	return L.size==0;
}

int full_List(List L){
	return L.size==Maxlength;
}

Node* element_at(int p,List L){
	return L.Elements[p-1];
}

void Push_List(Node *x, int position,List *L){
	if(!full_List(*L)){
		int q;
		for(q=L->size;q>=position;q--){
			L->Elements[q]=L->Elements[q-1];
		}
		L->Elements[position-1]=x;
		L->size++;
	}
}

void delete_List(int position, List *L){
	if(empty_List(*L)){
		printf("empty");
	}
	else if(position<1 || position > L->size){
		printf("Position is not possible to delete\n");
	}
	else{
		int i;
		for(i=position-1; i < L->size-1;i++){
			L->Elements[i]=L->Elements[i+1];
		}
		L->size--;
	}
}

Node* find_state(State state, List L, int *position){
	int i;
	for(i=1;i<=L.size;i++){
		if(compareStates(element_at(i,L)->state,state)){
			*position=i;
			return element_at(i,L);	
		}
	}
	return NULL;	
}

void sort_List(List *L){
	int i,j;
	for(i=0;i< L->size-1;i++){
		for(j=i+1;j < L->size;j++){
			if(L->Elements[i]->heuristic > L->Elements[j]->heuristic){
				Node* node=L->Elements[i];
				L->Elements[i]=L->Elements[j];
				L->Elements[j]=node;
			}
		}
	}
}

Node* BFS(State state, State goal){
	List Open_BFS;
	List Close_BFS;
	makenull_List(&Open_BFS);
	makenull_List(&Close_BFS);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->no_function=0;
	root->heuristic=heuristic1(root->state,goal);
	Push_List(root,Open_BFS.size+1,&Open_BFS);
	while(!empty_List(Open_BFS)){
		Node* node = element_at(1,Open_BFS);
		delete_List(1,&Open_BFS);
		Push_List(node,Close_BFS.size+1,&Close_BFS);
		if(goalcheck(node->state,goal)){
			return node;
		}
		int opt;
		for(opt=1;opt<=Max_Operator;opt++){
			State newstate;
			newstate=node->state;
			if(callOperator(node->state,&newstate,opt)){
				Node* newNode =(Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				newNode->heuristic=heuristic1(newstate,goal);
				int pos_Open,pos_Close;
				Node* nodeFoundOpen = find_state(newstate,Open_BFS,&pos_Open);
				Node* nodeFoundClose=find_state(newstate,Close_BFS,&pos_Close);
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					Push_List(newNode,Open_BFS.size+1,&Open_BFS);
				}
				else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic){
					delete_List(pos_Open,&Open_BFS);
					Push_List(newNode,pos_Open,&Open_BFS);
				}
				else if(nodeFoundClose!=NULL && nodeFoundClose->heuristic > newNode->heuristic){
					delete_List(pos_Close,&Close_BFS);
					Push_List(newNode,Open_BFS.size+1,&Open_BFS);
				}
				sort_List(&Open_BFS);
			}
		}
	}
	return NULL;
}

void Print_WaysToGetGoal(Node* node){
	List ListPrint;
	makenull_List(&ListPrint);
	while(node->Parent){
		Push_List(node,ListPrint.size+1,&ListPrint);
		node = node->Parent;
	}
	Push_List(node,ListPrint.size+1,&ListPrint);
	int no_action=0,i;
	for(i=ListPrint.size;i>0;i--){
		printf("\nAction %d: %s",no_action,action[element_at(i,ListPrint)->no_function]);
		Print_State(element_at(i,ListPrint)->state);
		no_action++;
	}
}

int main(){
	State state;
	state.emptyRow=1;
	state.emptyCol=1;
	state.eightPuzzel[0][0]= 3;
	state.eightPuzzel[0][1]= 4;
	state.eightPuzzel[0][2]= 5;
	state.eightPuzzel[1][0]= 1;
	state.eightPuzzel[1][1]= 0;
	state.eightPuzzel[1][2]= 2;
	state.eightPuzzel[2][0]= 6;
	state.eightPuzzel[2][1]= 7;
	state.eightPuzzel[2][2]= 8;
	
	State goal;
	goal.emptyRow=0;
	goal.emptyCol=0;
	goal.eightPuzzel[0][0]= 0;
	goal.eightPuzzel[0][1]= 1;
	goal.eightPuzzel[0][2]= 2;
	goal.eightPuzzel[1][0]= 3;
	goal.eightPuzzel[1][1]= 4;
	goal.eightPuzzel[1][2]= 5;
	goal.eightPuzzel[2][0]= 6;
	goal.eightPuzzel[2][1]= 7;
	goal.eightPuzzel[2][2]= 8;
	
	Node* p =BFS(state,goal);
	Print_WaysToGetGoal(p);
	return 0;
}
