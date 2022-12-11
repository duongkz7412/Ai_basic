#include<stdio.h>
#include<stdlib.h>
#define Maxlength 100
#define NB_ROWS 8
#define NB_COLUMS 8
#define empty 0
#define Max_Value 10
#define Area_Square_size 3
#define INF 999999

typedef struct{
	int x,y;
}Coord;

typedef struct{
	Coord data[Maxlength];
	int size;
}ListCoord;

typedef struct{
	int data[NB_ROWS*NB_COLUMS][NB_ROWS*NB_COLUMS];
	int n;
}Constrains;

typedef struct{
	int cell[NB_ROWS][NB_COLUMS];
	Constrains constrains;
}Queen;

typedef struct{
	int data[Maxlength];
	int size;
}List;

void initList(List *L){
	L->size =0;
}

void appendList(List *L, int coord){
	L->data[L->size++] = coord; 
}


void initListCoord(ListCoord *L){
	L->size =0;
}

void appendListCoord(ListCoord *L, Coord coord){
	L->data[L->size++] = coord; 
}

void initContrains(Constrains *contrains){
	int i,j;
	for(i=0;i<NB_ROWS*NB_COLUMS;i++){
		for(j=0;j<NB_ROWS*NB_COLUMS;j++){
			contrains->data[i][j] = 0;
		}
	}
	contrains->n = NB_ROWS*NB_COLUMS;
}

int indexOf(Coord coord){
	return (NB_ROWS*coord.x+coord.y);
}

Coord positionOfVerter(int verter){
	Coord coord;
	coord.x = verter / NB_ROWS;
	coord.y = verter % NB_COLUMS;
	return coord;
}

int addConstrain(Constrains *constrains, Coord source, Coord target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(constrains->data[u][v] == 0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] = 1;
		return 1;
	}
	return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord){
	int i;
	int v= indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i =0;i< constrains.n;i++){
		if(constrains.data[v][i] == 1){
			appendListCoord(&result,positionOfVerter(i));
		}
	}
	return result;	
}

void initSudoku(Queen *queen){
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			queen->cell[i][j] = empty;
		}
	}
	initContrains(&queen->constrains);
}

void initSudokuWithValues(Queen* queen, int inputs[NB_ROWS][NB_COLUMS]){
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			queen->cell[i][j] = inputs[i][j];
		}
	}
	initContrains(&queen->constrains);
}

int clearContrains(Constrains *constrains){
	return constrains->n==0;
}

void print_8_queen(Queen queen){
	int i,j;
	printf("Queen:\n");
	for(i=0;i<NB_ROWS;i++){
		if(i%Area_Square_size == 0 ){
			printf("");
		}
		for(j=0;j<NB_COLUMS;j++){
			if(j % Area_Square_size == 0){
				printf("");
			}
			printf("%d ",queen.cell[i][j]);
		}
		printf("\n");
	}
}

int isFilledSudoku(Queen queen){
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			if(queen.cell[i][j] == empty){
				return 0;
			}
		}
	}
	return 1;
}

void spreadConstrainsFrom(Coord position, Constrains* constrains,ListCoord *changeds){
	int row = position.x;
	int colum = position.y;
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		if(i != row){
			Coord pos = {i,colum};
			if(addConstrain(constrains,position,pos)){
				appendListCoord(changeds,pos);
			}
		}
	}
	for(i=0;i<NB_COLUMS;i++){
		if(i!=colum){
			Coord pos = {row,i};
			if(addConstrain(constrains,position,pos)){
				appendListCoord(changeds,pos);
			}
		}
	}
	for(i=0;i<Area_Square_size;i++){
		for(j=0;j<Area_Square_size;j++){
			int areaX = (row/Area_Square_size) *Area_Square_size;
			int areaY = (colum/Area_Square_size)*Area_Square_size;
			if(areaX+i != row || areaY+j != colum){
				Coord pos = {areaX+i ,areaY+j};
				if(addConstrain(constrains,position,pos)){
					appendListCoord(changeds,pos);
				}
			}
		}
	}
}

List getAvailableValues(Coord position, Queen queen){
	ListCoord posList = getConstrains(queen.constrains,position);
	int availables[Max_Value];
	int i;
	for(i=1;i<Max_Value;i++){
		availables[i] =1;
	}
	for(i=0;i<posList.size;i++){
		Coord pos = posList.data[i];
		if(queen.cell[pos.x][pos.y] != empty){
			availables[queen.cell[pos.x][pos.y]] = 0;
		}
	}
	List resutl;
	initList(&resutl);
	for(i=1;i<Max_Value;i++){
		if(availables[i]){
			appendList(&resutl,i);
		}
	}
	return resutl;
}

Coord getNextEmptyCell(Queen queen){
	int i,j;
	for(i=0;i< NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			Coord pos ={i,j};
			if(queen.cell[i][j] == empty){
				return pos;
			}
		}
	}
}

Coord getNextMinDomainCell(Queen queen){
	int minLength = INF;
	int i,j;
	Coord result;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			if(queen.cell[i][j] == empty){
				Coord pos = {i,j};
				int availablesLength = getAvailableValues(pos,queen).size;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

int exploredCounter =0;
int sudoluBackTracking(Queen *queen){
	if(isFilledSudoku(*queen)){
		return 1;
	}
	Coord position = getNextMinDomainCell(*queen);
	List available = getAvailableValues(position,*queen);
	if(available.size == 0){
		return 0;
	}
	int j;
	for(j=0;j<available.size;j++){
		int value = available.data[j];
		queen->cell[position.x][position.y] = value;
		exploredCounter++;
		ListCoord history;
		initListCoord(&history);
		if(sudoluBackTracking(queen)){
			return 1;
		}
		queen->cell[position.x][position.y] = empty;
	}
	return 0;
}

Queen solveQueen(Queen queen){
	int i,j;
	clearContrains(&queen.constrains);
	for(i=0;i< NB_ROWS;i++){
		for(j=0;j<NB_COLUMS;j++){
			//if(queen.cell[i][j] != empty){
				ListCoord history;
				initListCoord(&history);
				Coord pos = {i,j};
				spreadConstrainsFrom(pos,&queen.constrains,&history);
		//	}	
		}
	}
	exploredCounter =0;
	if(sudoluBackTracking(&queen)){
		printf("Solved \n");
	}
	else{
		printf("can't solved\n");
	}
	printf("Exlored %d states\n",exploredCounter);
	return queen;
}


int inputs[8][8] = { 
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
					};	

int main(){
	Queen queen;
	initSudokuWithValues(&queen,inputs);
	print_8_queen(queen);
	Queen result = solveQueen(queen);
	print_8_queen(result);
	return 0;
}
