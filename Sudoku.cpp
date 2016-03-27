#include"Sudoku.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>



int BlockIndex[81];//use in solve() and transform()
int RowIndex[81];//use in solve() and transform()
int ColIndex[81];//use in solve() and transform()

int Entry[81];//use in solve() and transform()
int Posible_Row[9]; //use in solve()
int Posible_Col[9]; //use in solve()
int Posible_Block[9]; //use in solve()

int QuestionRow[9]; //use in transform()
int QuestionCol[9]; //use in transform()
int QuestionBlock[9]; //use in transform()

const int CON=0x3fe;
const int ZERO=0;
int Sort[81];
int sort_counter=0;

int i,j,k; //loop


Sudoku::Sudoku(){}

void Sudoku::giveQuestion()
{
	srand(time(NULL));
	int a;
	
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
		Posible_Row[i]=Posible_Col[i]=Posible_Block[i]=CON; //solve question
		QuestionBlock[i]=QuestionRow[i]=QuestionCol[i]=ZERO; // transform question
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

	printf("\n\n");
}

void Print_arry()
{
	printf("%c\n",'1');
	int Cell_Ans_bit;
	int Value;

	for(i = 0;i < 81; i++)
	{
		Cell_Ans_bit = Entry[i];

		if(Entry[i]==0)
		{
			printf("0 ");
		}
		else
		{
			for(Value = 0; Value <= 9; Value++)
			{
				if(Cell_Ans_bit==(1<<Value))
					printf("%d ",Value);
			}
		}

		if((i % 9) == 8)
			printf("\n");
	}

	return;
}

void succesed()
	{
		Print_arry();
		return;
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
	printf("changeNum a=%d b=%d\n",a,b);

	i=0;
	while(i!=81)
	{

			if(Entry[i]==(1<<a))
			{
				printf("change a to b\n");
				Entry[i]=(1<<b);
				i=i+1;

			}

			if(Entry[i]==(1<<b))
			{
				Entry[i]=(1<<a);
				i=i+1;
			}

			i=i+1;
	}

	Print_arry();
}
	
void Sudoku::changeRow(int a , int b)
{
	int tmp,tmp2,c;
	
	if(b<a)
	{
		tmp = a;
		a =b;
		b = tmp;
	}

	printf("changeRow: a=%d b=%d \n",a ,b );

	if(a==0 && b==1)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[0+i];
			QuestionBlock[0+i]=QuestionBlock[3+i];
			QuestionBlock[3+i]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionRow[0+i];
			QuestionRow[0+i]=QuestionRow[3+i];
			QuestionRow[3+i]=tmp;
		}
		printf("a=0 b=1\n");
	}

	if(a==0 && b==2)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[0+i];
			QuestionBlock[0+i]=QuestionBlock[6+i];
			QuestionBlock[6+i]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionRow[0+i];
			QuestionRow[0+i]=QuestionRow[6+i];
			QuestionRow[6+i]=tmp;
		}
	}

	if(a==1 && b==2)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[3+i];
			QuestionBlock[3+i]=QuestionBlock[6+i];
			QuestionBlock[6+i]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionRow[3+i];
			QuestionRow[3+i]=QuestionRow[6+i];
			QuestionRow[6+i]=tmp;
		}
	}

	

	int CIndex;
	int RIndex;
	int BIndex;

	for(i = 0; i < 81; i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		Entry[i]=QuestionRow[RIndex] & QuestionBlock[BIndex] & QuestionCol[CIndex];
	}

	return;
}
	
void Sudoku::changeCol(int a , int b)
{
	int tmp,tmp2,c;
	
	if(b<a)
	{
		tmp = a;
		a =b;
		b = tmp;
	}

	printf("changeCol: a=%d b=%d \n",a ,b );

	if(a==0 && b==1)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[3*i];
			QuestionBlock[3*i]=QuestionBlock[3*i+1];
			QuestionBlock[3*i+1]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionCol[0+i];
			QuestionCol[0+i]=QuestionCol[3+i];
			QuestionCol[3+i]=tmp;
		}
		printf("a=0 b=1\n");
	}

	if(a==0 && b==2)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[3*i];
			QuestionBlock[3*i]=QuestionBlock[3*i+2];
			QuestionBlock[3*i+2]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionCol[0+i];
			QuestionCol[0+i]=QuestionCol[6+i];
			QuestionCol[6+i]=tmp;
		}
	}

	if(a==1 && b==2)
	{
		for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[1+i*3];
			QuestionBlock[1+i*3]=QuestionBlock[2+i*3];
			QuestionBlock[2+i*3]=tmp2;
		}

		for(i = 0; i < 3; i++)
		{
			tmp=QuestionCol[3+i];
			QuestionCol[3+i]=QuestionCol[6+i];
			QuestionCol[6+i]=tmp;
		}
	}

	

	int CIndex;
	int RIndex;
	int BIndex;

	for(i = 0; i < 81; i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		Entry[i]=QuestionRow[RIndex] & QuestionBlock[BIndex] & QuestionCol[CIndex];
	}

	return;
}

void Sudoku::rotate(int n)
{

}

void vertical()
{
	int tmp,tmp2;
	j=8;
	int CIndex;
	int RIndex;
	int BIndex;

	for(i=0;i<3;i++)
	{
		tmp2=QuestionBlock[0+i];
		QuestionBlock[0+i]=QuestionBlock[6+i];
		QuestionBlock[6+i]=tmp2;
	}

	for(i = 8 ; i > 1; i = i-2)
	{

		tmp=QuestionRow[j];
		QuestionRow[j]=QuestionRow[j-i];
		QuestionRow[j-i]=tmp;
		j=j-1;
	}

	for(i = 0; i < 81; i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		Entry[i]=QuestionRow[RIndex] & QuestionBlock[BIndex] & QuestionCol[CIndex];
	}


}

void horizoltal()
{
	int tmp,tmp2;
	j=8;
	int CIndex;
	int RIndex;
	int BIndex;


	for(i = 8 ; i > 1; i = i-2)
	{

		tmp=QuestionCol[j];
		QuestionCol[j]=QuestionCol[j-i];
		QuestionCol[j-i]=tmp;
		j=j-1;
	}

	for(i=0;i<3;i++)
		{
			tmp2=QuestionBlock[3*i];
			QuestionBlock[3*i]=QuestionBlock[3*i+2];
			QuestionBlock[3*i+2]=tmp2;
		}

	for(i = 0; i < 81; i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		Entry[i]=QuestionRow[RIndex] & QuestionBlock[BIndex] & QuestionCol[CIndex];
	}
}

void Sudoku::flip(int n)
{
	if(n==0)
		{
			vertical();
		}
	else
		{
			horizoltal();
		}
}

void Sudoku::transform()
{
	srand(time(NULL));
	Print_arry();
	int a=0,b=0;//random number
	

	//printf("a=%d b=%d\n",a,b );
	while(a==b)
	{	
		a=rand()%10;
		b=rand()%10;
	}
	printf("a=%d b=%d\n",a,b);
	printf("haha\n");
	changeNum(a,b);

	int CIndex;
	int RIndex;
	int BIndex;

	for(i=0;i<81;i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		QuestionCol[CIndex] |= Entry[i];
		QuestionBlock[BIndex] |= Entry[i];
		QuestionRow[RIndex] |= Entry[i];

	}


	for(i=0;i<9;i++)
		//printf("QuestionRow[%d]=%d\n",i,QuestionCol[i]);

	a=0;
	b=0;
	while(a==b)
	{	
		a=rand()%3;
		b=rand()%3;
	}

	changeRow(a,b);
	printf("haha\n");
	for(i=0;i<9;i++)
		//printf("QuestionRow[%d]=%d\n",i,QuestionCol[i]);

	for(i=0;i<81;i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		QuestionCol[CIndex] |= Entry[i];
		QuestionBlock[BIndex] |= Entry[i];
		QuestionRow[RIndex] |= Entry[i];

	}

	a=0;
	b=0;
	while(a==b)
	{	
		a=rand()%3;
		b=rand()%3;
	}



	changeCol(a,b);

	for(i=0;i<81;i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		QuestionCol[CIndex] |= Entry[i];
		QuestionBlock[BIndex] |= Entry[i];
		QuestionRow[RIndex] |= Entry[i];

	}

	a=rand()%2;



	flip(a);


	Print_arry();

	return;

}
