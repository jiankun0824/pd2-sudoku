#include"Sudoku.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>



int BlockIndex[81];
int RowIndex[81];
int ColIndex[81];

int Entry[81];
int Posible_Row[9];
int Posible_Col[9];
int Posible_Block[9];

int Sort[81];
int sort_counter=0;

int i,j,k; //loop

Sudoku::Sudoku(){}

void Sudoku::giveQuestion()
{
	int a;
	srand(time(NULL));
	a=rand()%1;
	switch(a)
	{
		case 0:
		printf("7 0 0 8 0 0 0 1 0\n0 2 0 0 0 9 3 0 0\n0 0 4 0 0 0 0 0 5\n8 0 0 0 0 4 0 9 0\n0 5 0 1 0 0 0 0 7\n0 0 6 0 3 0 2 0 0\n9 0 0 0 7 0 8 0 0\n0 0 1 5 0 0 0 0 0\n0 3 0 0 0 0 0 6 0");
		break;
	};
}


void Swap(int s1,int s2)
{
	int tmp=Sort[s1];
	Sort[s1]=Sort[s2];
	Sort[s2]=tmp;
}

void BitTransform(int Index,int tmp)
{
	int Bit=1<<tmp;

	Entry[Index]=Bit;
	Posible_Block[BlockIndex[Index]] &= (~Bit);
	Posible_Col[ColIndex[Index]]&=(~Bit);
	Posible_Row[RowIndex[Index]]&=(~Bit);
//printf("%d %d\n", Bit, Posible_Block[BlockIndex[Index]]);exit(1);
	//printf("fuck1=%d\n",sort_counter);
	if(sort_counter!=Index)
	{ 
	//	printf("fuck2\n");
		Swap(sort_counter,Index);
	}
	sort_counter++;

}

void Sudoku::readIn()
{	
	int tmp;
	int Index;

	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			Index=i*9+j;
			RowIndex[Index]=i;
			ColIndex[Index]=j;
			BlockIndex[Index]=(j/3)+(i/3)*3;

		}
		Posible_Row[i]=Posible_Col[i]=Posible_Block[i]=0x3fe;
	}



	for(i=0;i<81;i++)
	{
		Sort[i]=i;
		scanf("%d",&tmp);

		if(tmp!=0)	
			BitTransform(i,tmp);
	}

	printf("sort_counter=%d\n",sort_counter);
	/*for(i=0;i<81;i++)
		printf("Sort[%d]:%d\n",i,Sort[i]);
	printf("\n");

	for(i=0;i<9;i++)
		printf("Block[%d]:%d\n",i,Posible_Block[i]);
	printf("\n");

	for(i=0;i<9;i++)
		printf("Col[%d]:%d\n",i,Posible_Col[i]);
	printf("\n");

	for(i=0;i<9;i++)
		printf("Row[%d]:%d\n",i,Posible_Row[i]);
	printf("\n");*/
}

void Sudoku::solve()
{

}

void Sudoku::changeNum(int a , int b)
{

}
	
void Sudoku::changeRow(int a , int b)
{

}
	
void Sudoku::changeCol(int a , int b)
{

}

void Sudoku::rotate(int n)
{

}
	
void Sudoku::flip(int n)
{

}

void Sudoku::transform()
{

}
