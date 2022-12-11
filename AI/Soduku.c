#include<stdio.h>
#include<stdlib.h>
#define NB_ROWS 9
#define NB_COLUMNS 9
#define Max_Value 10
#define empty 0
#define Area_Square_Size 3
#define INF 999999
#define Maxlength 500

typedef struct{
	int x,y;
}Coord;

typedef struct{
	Coord data[Maxlength];
	int size;
}ListCoord;

typedef struct{
	int data[NB_ROWS*NB_COLUMNS][NB_ROWS*NB_COLUMNS];
	int n;
}Constrains;

typedef struct{
	int  cells[NB_ROWS][NB_COLUMNS];
	Constrains constrains;
}Sudoku;

typedef struct{
	int data[Maxlength];
	int size;
}List;

void init_List(List *L){
	L->size=0;
}

void appendList(List *L,int e){
	L->data[L->size++]=e;
}

void initListCoord(ListCoord *L){
	L->size =0;
}

void appendListCoord(ListCoord *L, Coord coord){
	L->data[L->size++]=coord;
}

void initConstrains(Constrains *constrains){
	int i,j;
	for(i=0;i< NB_ROWS*NB_COLUMNS;i++){
		for(j=0;j< NB_ROWS*NB_COLUMNS;j++){
			constrains->data[i][j] = 0;
		}
	}
	constrains->n = NB_ROWS*NB_COLUMNS;
}

int indexOf(Coord coord){
	return(NB_ROWS*coord.x + coord.y);
}

Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / NB_ROWS;
	coord.y = vertex % NB_COLUMNS;
return coord;
}

int addConstrains(Constrains *constrains, Coord source,Coord target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(constrains->data[u][v] == 0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] =1 ;
		return 1;
	}
	return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i=0;i<constrains.n;i++){
		if(constrains.data[v][i] == 1){
			appendListCoord(&result,positionOfVertex(i));
		}
	}
	return result;
}

void initSudoku(Sudoku *sudoku){
	int i,j;
	for(i=0;i< NB_ROWS;i++){
		for(j=0;j<NB_COLUMNS;j++){
			sudoku->cells[i][j] = empty;
		}
	}
	initConstrains(&sudoku->constrains);
}

void initSudokuWithValues(Sudoku* sudoku, int inputs[NB_ROWS][NB_COLUMNS]){
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMNS;j++){
			sudoku->cells[i][j] = inputs[i][j];
		}
	}
	initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku){
	int i,j;
	printf("Sudoku:\n");
	for(i=0;i<NB_ROWS;i++){
		if(i%Area_Square_Size==0){
			printf("-------------------------\n");
		}
		for(j =0 ; j< NB_COLUMNS;j++){
			if(j%Area_Square_Size ==0){
				printf("| ");
			}
			printf("%d ",sudoku.cells[i][j]);
		}
		printf("|\n");
	}
	printf("-------------------------\n");
}

int isFilledSudoku(Sudoku sudoku){
	int i,j;
	for(i=0;i< NB_ROWS;i++){
		for(j=0;j< NB_COLUMNS;j++){
			if(sudoku.cells[i][j] == empty){
				return 0;
			}
		}
	}
	return 1;
}

void speadConstrainsFrom(Coord position, Constrains* constrains, ListCoord *changeds){
	int row = position.x;
	int column = position.y;
	int i,j;
	for(i=0;i<NB_COLUMNS;i++){
		if(i!=row){
			Coord pos={i,column};
			if(addConstrains(constrains,position,pos)){
				appendListCoord(changeds,pos);
			}
		}
	}
	for(i=0;i<NB_COLUMNS;i++){
		if(i!=column){
			Coord pos ={row,i};
			if(addConstrains(constrains,position,pos)){
				appendListCoord(changeds,pos);
			}
		}
	}
	for(i=0;i<Area_Square_Size;i++){
		for(j=0;j<Area_Square_Size;j++){
			int areaX = (row/Area_Square_Size)*Area_Square_Size;
			int areaY = (column/Area_Square_Size)*Area_Square_Size;
			if(areaX +i != row || areaY+j != column){
				Coord pos = {areaX+i,areaY+j};
				if(addConstrains(constrains,position,pos)){
					appendListCoord(changeds,pos);
				}
			}
		}
	}
}

List getAvaiableValues(Coord position, Sudoku sudoku){
	ListCoord posList = getConstrains(sudoku.constrains,position);
	int availables[Max_Value];	
	int i;
	for(i=1;i< Max_Value;i++){
		availables[i]=1;
	}
	for(i=0;i<posList.size;i++){
		Coord pos = posList.data[i];
		if(sudoku.cells[pos.x][pos.y] != empty){
			availables[sudoku.cells[pos.x][pos.y]]=0;
		}
	}
	List result;
	init_List(&result);
	for(i=1;i<Max_Value;i++){
		if(availables[i]){
			appendList(&result,i);
		}
	}
	return result;
}

Coord getNextEmptyCell(Sudoku sudoku){
	int i,j;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMNS;j++){
			Coord pos ={i,j};
			if(sudoku.cells[i][j] == empty){
				return pos;
			}
		}
	}
}

Coord getNextMinDomainCell(Sudoku sudoku){
	int minLength = INF;
	int i,j;
	Coord result;
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMNS;j++){
			if(sudoku.cells[i][j] == empty){
				Coord pos = {i,j};
				int availablesLength = getAvaiableValues(pos,sudoku).size;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
					
				}
			}
		}
	}
	return result;
}

int exloredCounter =0;
int sudokuBackTracking(Sudoku *sudoku){
	if(isFilledSudoku(*sudoku)){
		return 1;
	}
	Coord position = getNextMinDomainCell(*sudoku);
	List availables = getAvaiableValues(position,*sudoku);
	if(availables.size ==0){
		return 0;
	}
	int j;
	for(j=0;j<availables.size;j++){
		int value = availables.data[j];
		sudoku->cells[position.x][position.y] = value;
		exloredCounter++;
		if(sudokuBackTracking(sudoku)){
			return 1;
		}
		sudoku->cells[position.x][position.y]=empty;
	}
	return 0;
}

int clearContrains(Constrains *constrains){
	return constrains->n==0;
}

//int clearContrains(Constrains *constrains){
//	int i,j;
//	for(i=0;i< NB_ROWS*NB_COLUMNS;i++){
//		for(j=0;j< NB_ROWS*NB_COLUMNS;j++){
//			constrains->data[i][j]=0;
//		}
//	}
//	return constrains->n = NB_ROWS*NB_COLUMNS;
//}


Sudoku solveSudoku(Sudoku sudoku){
	int i,j;
	clearContrains(&sudoku.constrains);
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLUMNS;j++){
				ListCoord history ;
				initListCoord(&history);
				Coord pos ={i,j};
				speadConstrainsFrom(pos,&sudoku.constrains,&history);
		}
	}
	exloredCounter =0;
	if(sudokuBackTracking(&sudoku)){
		printf("Solved\n");
	}
	else{
		printf("Can't solve\n");
	}
	printf("Explored %d states\n",exloredCounter);
	return sudoku;
}

int inputs1[9][9] = { 
						{0,6,1,0,0,7,0,0,3},
						{0,9,2,0,0,3,0,0,0},
						{0,0,0,0,0,0,0,0,0},
						{0,0,8,5,3,0,0,0,0},
						{0,0,0,0,0,0,5,0,4},
						{5,0,0,0,0,8,0,0,0},
						{0,4,0,0,0,0,0,0,1},
						{0,0,0,1,6,0,8,0,0},
						{6,0,0,0,0,0,0,0,0},
					};
					


//int inputs1[9][9] = { 
//						{5,3,0,0,7,0,0,0,0},
//						{6,0,0,1,9,5,0,0,0},
//						{0,9,8,0,0,0,0,6,0},
//						{8,0,0,0,6,0,0,0,3},
//						{4,0,0,8,0,3,0,0,1},
//						{7,0,0,0,2,0,0,0,6},
//						{0,6,0,0,0,0,2,8,0},
//						{0,0,0,4,1,9,0,0,5},
//						{0,0,0,0,8,0,0,7,9},
//					};
					
int main(){
	Sudoku sudoku;
	initSudokuWithValues(&sudoku,inputs1);
	printSudoku(sudoku);
	Sudoku result = solveSudoku(sudoku);
	printSudoku(result);
	return 0;
}
