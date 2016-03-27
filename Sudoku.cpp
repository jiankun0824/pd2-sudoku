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


void Swap_sort(int s1,int s2)
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
		Swap_sort(sort_counter,Index);
	}
	sort_counter++;

	//printf("BitTransform done");
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

	/*printf("sort_counter=%d\n",sort_counter);
	for(i=0;i<81;i++)
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

	//printf("readin done\n");
}

void Printf_Ans()
{
	printf("%c\n",'1');
	int Cell_Ans_bit;
	int Value;

	for(i = 0;i < 81; i++)
	{
		Cell_Ans_bit = Entry[i];

		for(Value = 0; Value <= 9; Value++)
		{
			if(Cell_Ans_bit==(1<<Value))
				printf("%d ",Value);
		}


		if((i % 9) == 8)
			printf("\n");
	}

	return;
}

void succesed()
	{
		Printf_Ans();
	}

int IndexOfMinimunPosible(int s)
{
	int test;
	int minimun_posible = 0;
	int Total_posible = 10;
	int Index;
	int Posible;
	int s2;

	for(test = s; test < 81; test++)
	{
		Index = Sort[test];
		Posible = Posible_Row[RowIndex[Index]] & Posible_Block[BlockIndex[Index]] & Posible_Col[ColIndex[Index]] ;
		//printf("Posible=%d\n",Posible);
		minimun_posible=0;

		while(Posible)
		{
			Posible &= ~ (Posible & -Posible);
			minimun_posible++;
		}

		if(minimun_posible<Total_posible)
		{
			s2=test;
			Total_posible = minimun_posible;
		}
		//printf("IndexOfMinimunPosible done\n");

	}
	
	return s2;
}
void Recursive(int s)
{
	//printf("s=%d\n",s );
	if(s>=81)
	{
		succesed();
		return;
	}

	int s2=IndexOfMinimunPosible(s); //sort[s]=index 
	//printf("s2=%d\n",s2);
	Swap_sort(s,s2);

	//printf("%d\n",s );

	int Index=Sort[s];

	int BIndex=BlockIndex[Index];
	int RIndex=RowIndex[Index];
	int CIndex=ColIndex[Index];

	int Posible = Posible_Row[RIndex] & Posible_Block[BIndex] & Posible_Col[CIndex];
	while(Posible)
	{
		//printf("haha\n");
		int TakeOnePosible = Posible & (-Posible);
		Posible &= ~TakeOnePosible;

		Entry[Index] = TakeOnePosible;
		Posible_Col[CIndex] &= ~TakeOnePosible;
		Posible_Row[RIndex] &= ~TakeOnePosible;
		Posible_Block[BIndex] &= ~TakeOnePosible;

		Recursive(s+1);
		//printf("2.haha\n");

		Entry[Index] = 0;
		Posible_Col[CIndex] |= TakeOnePosible;
		Posible_Row[RIndex] |= TakeOnePosible;
		Posible_Block[BIndex] |= TakeOnePosible;

		//printf("3.haha\n");
	}

	Swap_sort(s,s2);
	//printf("done\n");

}

void Sudoku::solve()
{
	Recursive(sort_counter);
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
