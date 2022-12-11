
#include<stdio.h>
#include<stdlib.h>
#define G 6
#define Maxlength 100
#include <stack>
#include <queue>
using namespace std;

typedef struct Node{
	int state[G];
	struct Node* Parent;
	int no_function;
}Node;

const char *action[]={"First State", "Ly 1 2 3",
					"Ly 2 3 4","Ly 3 4 5",
					"Ly 4 5 6"};


void Print_State(int state[]){
	printf("\n %d, %d, %d, %d, %d, %d",state[0],state[1],state[2],state[3],state[4],state[5]);
}

int goalcheck(int state[]){
	int i;
	for(i=0;i<=G;i++){
		if(state[i] ==-1){
			return 0;
		}	
	}
	return 1;
}

int ly123(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=0;i<=2;i++){
		result[i] = state[i] * -1;
	}
}

int ly234(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=1;i<=3;i++){
		result[i] = state[i] * -1;
	}
}

int ly345(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=2;i<=4;i++){
		result[i] = state[i] * -1;
	}
}

int ly456(int state[], int result[]){
	int i;
	for(i=0;i<=5;i++){
		result[i] = state[i];
	}
	for(i=3;i<=5;i++){
		result[i] = state[i] * -1;
	}
}

int call_operator(int state[], int result[], int option){
	switch(option){
		case 1: return ly123(state,result);
		case 2: return ly234(state,result);
		case 3: return ly345(state,result);
		case 4: return ly456(state,result);
		default :
		return 0;
	}
}

int compareState(int X[], int Y[]){
	int i;
	for(i=1;i<G;i++){
		if(X[i] != Y[i]){
			return 0;
		}
	}
	return 1;
}

int find_Queue(int state[], queue<Node*> q){
	while (!q.empty()){
		if (compareState(q.front()->state, state))
			return 1;
		q.pop();
	}
	return 0;
}

Node* BFS_Algorithm(int state[]){
	queue<Node*> Open_BFS;
	queue<Node*> Close_BFs;
	Node* root = (Node*)malloc(sizeof(Node));
	int i;
	for(i=0;i<=G;i++){
		root->state[i]=state[i];
	}
	root->Parent=NULL;
	root->no_function=0;
	Open_BFS.push(root);
	while(!Open_BFS.empty()){
		Node* node=Open_BFS.front();
		Open_BFS.pop();
		Open_BFS.push(node);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt=1;opt<=6;opt++){
			int newstate[G];
			if(call_operator(node->state,newstate,opt)){
				if(find_Queue(newstate,Open_BFS) || find_Queue(newstate,Close_BFs)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				for(i=0;i<G;i++){
					newNode->state[i]=newstate[i];
				}
				newNode->Parent=node;
				newNode->no_function=opt;
				Open_BFS.push(newNode);
			}
		}
	}
	return NULL;
}

void Print_WaysToGetGoal(Node* node){
	stack<Node*> stackPrint;
	while(node->Parent!=NULL){
		stackPrint.push(node);
		node = node->Parent;
	}
	stackPrint.push(node);
	int no_action=0;
	while(!stackPrint.empty()){
		printf("\n Action %d: %s",no_action,action[stackPrint.top()->no_function]);
		Print_State(stackPrint.top()->state);
		stackPrint.pop();
		no_action++;
	}
}

int main(){
	int state[G] = {1, -1, 1, -1, 1, -1};
	Print_WaysToGetGoal(BFS_Algorithm(state));
	return 0;
}
