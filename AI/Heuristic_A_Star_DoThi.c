#include<stdio.h>
#include<stdlib.h>
#define ROWS 3
#define COLS 3
#define empty 0
#define Maxlength 500
#define Max_Operator 4
#define Max_Vertices 100

const char name[]={'A','B','C','D','G'};

typedef struct{
	int vertex;
}State;

void Print_State(State state){
	printf("%c",name[state.vertex]);
}

int compareStates(State X, State Y){
	return X.vertex == Y.vertex;
}

int goalcheck(State state,State goal){
	return compareStates(state,goal);
}

typedef struct Node{
	State state;
	struct Node* Parent;
	int f,g,h;
}Node;

typedef struct{
	Node *Elements[Maxlength];
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

Node* element_at(int p, List L){
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

void delete_List(int position,List *L){
	if(empty_List(*L)){
		printf("empty");
	}
	else if(position <1 || position > L->size){
		printf("Position is not possible to delete\n");
	}
	else{
		int i;
		for(i=position-1;i < L->size-1;i++){
			L->Elements[i] = L->Elements[i+1];
		}
		L->size--;
	}
}

void sort_List(List *L){
	int i,j;
	for(i=0;i<L->size-1;i++){
		for(j=i+1;j<L->size;j++){
			if(L->Elements[i]->h > L->Elements[j]->h){
				Node *node = L->Elements[i];
				L->Elements[i]=L->Elements[j];
				L->Elements[j] = node;
			}
		}
	}
}

Node *find_State(State state, List L,int *position){
	int i;
	for(i=1;i<=L.size;i++){
		if(compareStates(element_at(i,L)->state,state)){
			*position=i;
			return element_at(i,L);
		}
	}
	return NULL;
}

//int upOperator(State state,State *result){
//	*result = state;
//	int emptyRowCurrent = state.emptyRow;
//	int emptyColCurrent = state.emptyCol;
//	if(emptyRowCurrent>0){
//		result->emptyRow=emptyRowCurrent-1;
//		result->emptyCol=emptyColCurrent;
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent-1][emptyColCurrent];
//		result->eightPuzzel[emptyRowCurrent-1][emptyColCurrent]=empty;
//		return 1;
//	}
//	return 0;
//}
//
//int dowOperator(State state,State *result){
//	*result = state;
//	int emptyRowCurrent = state.emptyRow;
//	int emptyColCurrent = state.emptyCol;
//	if(emptyRowCurrent <2){
//		result->emptyRow=emptyRowCurrent+1;
//		result->emptyCol=emptyColCurrent;
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent+1][emptyColCurrent];
//		result->eightPuzzel[emptyRowCurrent+1][emptyColCurrent]=empty;
//		return 1;
//	}
//	return 0;
//}
//
//int leftOperator(State state, State *result){
//	*result = state;
//	int emptyRowCurrent = state.emptyRow;
//	int emptyColCurrent = state.emptyCol;
//	if(emptyColCurrent>0){
//		result->emptyRow=emptyRowCurrent;
//		result->emptyCol=emptyColCurrent-1;
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent-1];
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent-1]=empty;
//		return 1;
//	}
//	return 0;
//}
//
//int rightOperator(State state, State *result){
//	*result = state;
//	int emptyRowCurrent = state.emptyRow;
//	int emptyColCurrent = state.emptyCol;
//	if(emptyColCurrent<2){
//		result->emptyRow=emptyRowCurrent;
//		result->emptyCol=emptyColCurrent+1;
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent+1];
//		result->eightPuzzel[emptyRowCurrent][emptyColCurrent+1]=empty;
//		return 1;
//	}
//	return 0;
//}
//
//int call_Operator(State state,State *result, int opt){
//	switch(opt){
//		case 1: return upOperator(state,result);
//		case 2: return dowOperator(state,result);
//		case 3: return leftOperator(state,result);
//		case 4: return rightOperator(state,result);
//		default:
//			return 0;
//	}
//}
//
//int heuristic1(State state,State goal){
//	int row,col,count=0;
//	for(row=0;row<ROWS;row++){
//		for(col=0;col<COLS;col++){
//			if(state.eightPuzzel[row][col] != goal.eightPuzzel[row][col]){
//				count++;
//			}
//		}
//	}
//	return count;
//}
//
//int heuristic2(State state,State goal){
//	int count=0,row,col,row_g,col_g;
//	for(row=0;row<ROWS;row++){
//		for(col=0;col<COLS;col++){
//			if(state.eightPuzzel[row][col] != 0){
//				for(row_g=0;row_g<ROWS;row_g++){
//					for(col_g=0;col_g<COLS;col_g++){
//						if(state.eightPuzzel[row][col] == goal.eightPuzzel[row_g][col_g]){
//							count += abs(row-row_g) + abs(col-col_g);
//							row_g = ROWS;
//							col_g=COLS;
//						}
//					}
//				}
//			}
//		}
//	}
//	return count;
//}

typedef struct{
	int neighbor[Maxlength];
	int h;
}Vertices;

typedef struct{
	int num_vertices;
	Vertices v[Max_Vertices];
}Graph;

int init_Graph(int num_vertices,Graph *G){
	G->num_vertices=num_vertices;
	int i,j;
	for(i=0;i<num_vertices;i++){
		for(j=0;j<num_vertices;j++){
			G->v[i].neighbor[j]=0;
			G->v[i].h=0;
		}
	}
}

Node *A_Star(Graph G,State state,State goal){
	List Open_A_Star;
	List Close_A_Star;
	makenull_List(&Open_A_Star);
	makenull_List(&Close_A_Star);
	Node* root =(Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->g=0;
	root->h = G.v[state.vertex].h;
	root->f = root->g + root->h;
	Push_List(root,Open_A_Star.size+1,&Open_A_Star);
	while(!empty_List(Open_A_Star)){
		Node* node = element_at(1,Open_A_Star);
		delete_List(1,&Open_A_Star);
		Push_List(node,Close_A_Star.size+1,&Close_A_Star);
		if(goalcheck(node->state,goal)){
			return node;
		}
		int opt;
		for(opt=0;opt< G.num_vertices;opt++){
			State newstate;
			if(G.v[node->state.vertex].neighbor[opt >0]){
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state.vertex=opt;
				newNode->Parent=node;
				newNode->g=node->g+ G.v[node->state.vertex].neighbor[opt];
				newNode->h= G.v[opt].h;
				newNode->f=newNode->g+newNode->h;
				int pos_Open,pos_Close;
				Node* nodeFoundOpen = find_State(newstate,Open_A_Star,&pos_Open);
				Node* nodeFoundClose= find_State(newstate,Close_A_Star,&pos_Close);
				if(nodeFoundOpen == NULL && nodeFoundClose ==NULL){
					Push_List(newNode,Open_A_Star.size+1,&Open_A_Star);
				}
				else if(nodeFoundOpen != NULL && nodeFoundOpen->g > newNode->g){
					delete_List(pos_Open,&Open_A_Star);
					Push_List(newNode,pos_Open,&Open_A_Star);
				}
				else if(nodeFoundClose != NULL && nodeFoundClose->g > newNode->g){
					delete_List(pos_Close,&Close_A_Star);
					Push_List(newNode,Open_A_Star.size+1,&Open_A_Star);
				}
			}
		}
		sort_List(&Open_A_Star);
	}
	return NULL;
}

void Print_WaysToGetGoal(Node *node){
	List ListPrint;
	makenull_List(&ListPrint);
	while(node->Parent){
		Push_List(node,ListPrint.size+1,&ListPrint);
		node = node->Parent;
	}
	Push_List(node,ListPrint.size+1,&ListPrint);
	int no_action=0,i;
	for(i=ListPrint.size;i>0;i--){
		Print_State(element_at(i,ListPrint)->state);
		if(i!=1){
			printf("->");
		}
		no_action++;
	}
}

int main(){
	int i,j;
	Graph graph;
	freopen("test.txt","r",stdin);
	init_Graph(Max_Vertices,&graph);
	for(i=0;i<Max_Vertices;i++){
		int x;
		scanf("%d",&x);
		graph.v[i].h=x;
		for(j=0;j<Max_Vertices;j++){
			scanf("%d",&x);
			graph.v[i].neighbor[j]=x;
		}
	}
	State A,G;
	A.vertex=0;
	G.vertex=4;
	Node* result = A_Star(graph,A,G);
	Print_WaysToGetGoal(result);
	return 0;
}
