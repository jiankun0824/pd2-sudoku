#include"Sudoku.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>



int BlockIndex[81];//use in solve() and transform()
int CorrectAns[81];
int RowIndex[81];//use in solve() and transform()
int ColIndex[81];//use in solve() and transform()

int Entry[81];//use in solve() and transform()
int Posible_Row[9]; //use in solve()
int Posible_Col[9]; //use in solve()
int Posible_Block[9]; //use in solve()

int QuestionRow[9]; //use in transform()
int QuestionCol[9]; //use in transform()
int QuestionBlock[9]; //use in transform()

int ColRotate[9];
int RowRotate[9];
int BlockRotate[9];

int BlockUnsolve[9];
int ColUnsolve[9];
int RowUnsolve[9];
int checkBlock[9];
int checkCol[9];
int checkRow[9];

int MoreThanOne=0;
int succesed_counter=0;
const int POSIBLE=0x3fe;
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
	int sort_tmp;


	int CIndex=ColIndex[Index];
	int BIndex=BlockIndex[Index];
	int RIndex=RowIndex[Index];

	Entry[Index]=Bit;
	Posible_Block[BIndex] &= (~Bit);
	Posible_Col[CIndex]&=(~Bit);
	Posible_Row[RIndex]&=(~Bit);

	BlockUnsolve[BIndex]|=Bit;
	ColUnsolve[CIndex]|=Bit;
	RowUnsolve[RIndex]|=Bit;

	if(BlockUnsolve[BIndex]==checkBlock[BIndex] || ColUnsolve[CIndex]==checkCol[CIndex] || RowUnsolve[RIndex]==checkRow[RIndex])
	{
		printf("0\n");
		exit(0);
	}
	else
	{
		checkBlock[BIndex]=BlockUnsolve[BIndex];
		checkCol[CIndex]=ColUnsolve[CIndex];
		checkRow[RIndex]=RowUnsolve[RIndex];

	}
	sort_tmp=sort_counter;
	while(sort_tmp<81 && Sort[sort_tmp]!=Index)
	{ 
		sort_tmp++;
	}
	Swap_sort(sort_counter,sort_tmp);
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
		Posible_Row[i]=Posible_Col[i]=Posible_Block[i]=POSIBLE; //solve question
		QuestionBlock[i]=QuestionRow[i]=QuestionCol[i]=ZERO; // transform question
		BlockUnsolve[i]=ColUnsolve[i]=RowUnsolve[i]=ZERO;
		checkRow[i]=checkCol[i]=checkBlock[i]=ZERO;
	}



	for(i=0;i<81;i++)
	{
		Sort[i]=i;
		scanf("%d",&tmp);

		if(tmp!=0)	
			BitTransform(i,tmp);
	}
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
			CorrectAns[i]=0;
		}

		else
		{
			for(Value = 0; Value <= 9; Value++)
			{
				if(Cell_Ans_bit==(1<<Value))
					CorrectAns[i]=Value;
			}
		}
	}

	return;
}

void succesed()
	{
		succesed_counter++;
		if(succesed_counter>1)
		{
			printf("2\n");
			exit(0);
		}
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

	}
	
	return s2;
}
void Recursive(int s)
{
	if(s>=81)
	{
		succesed();
		if(MoreThanOne==2)
			Print_arry();

	}

	int s2=IndexOfMinimunPosible(s); //sort[s]=index 
	Swap_sort(s,s2);

	int Index=Sort[s];

	int BIndex=BlockIndex[Index];
	int RIndex=RowIndex[Index];
	int CIndex=ColIndex[Index];

	int Posible = Posible_Row[RIndex] & Posible_Block[BIndex] & Posible_Col[CIndex];
	while(Posible)
	{
		int TakeOnePosible = Posible & (-Posible);
		Posible &= ~TakeOnePosible;

		Entry[Index] = TakeOnePosible;
		Posible_Col[CIndex] &= ~TakeOnePosible;
		Posible_Row[RIndex] &= ~TakeOnePosible;
		Posible_Block[BIndex] &= ~TakeOnePosible;

		Recursive(s+1);

		Entry[Index] = 0;
		Posible_Col[CIndex] |= TakeOnePosible;
		Posible_Row[RIndex] |= TakeOnePosible;
		Posible_Block[BIndex] |= TakeOnePosible;

	}

	Swap_sort(s,s2);

}

void Sudoku::solve()
{
	Recursive(sort_counter);
	MoreThanOne=2;
	succesed_counter=0;
	Recursive(sort_counter);

	for(i=0;i<81;i++)
	{
		printf("%d ",CorrectAns[i]);

		if((i%9)==8)
			printf("\n");
	}

}

void Sudoku::changeNum(int a , int b)
{

	i=0;
	while(i!=81)
	{

		//printf("%d.test\n",i);
			if(Entry[i]==(1<<a))
			{
				Entry[i]=(1<<b);
				i=i+1;
				if(i==81)
					return;

			}

			if(Entry[i]==(1<<b))
			{
				Entry[i]=(1<<a);
				i=i+1;
				if(i==81)
					return;

			}

			i=i+1;
	}
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
	int a=n%4;
	int test=a;
	int Array[81];
	int ArrayAfterRotate[81];


		int Cell_Ans_bit;
		int Value;		

	if (a==0)
	{
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
							printf("%d ",Value );
					}
				}

				if((i % 9) == 8)
					printf("\n");
			}

		return ;
	}
	while(a>0)
	{
		if(a==test)
		{
			for(i = 0;i < 81; i++)
			{
				Cell_Ans_bit = Entry[i];

				if(Entry[i]==0)
				{
					Array[i]=0;

				}
				else
				{
					for(Value = 0; Value <= 9; Value++)
					{
						if(Cell_Ans_bit==(1<<Value))
							Array[i]=Value;
					}
				}

			}
		}
		else
		{
			for(i=0;i<81;i++)
			{
				Array[i]=ArrayAfterRotate[i];
			}
		}

		k=0;
		for(i=8 ; i>=0 ; i--)
		{
			for(j=0;j<9;j++)
			{
				ArrayAfterRotate[i+9*j]=Array[k];
				k=k+1;
			}
		}

		a=a-1;
		if(a==0)
		{
			for(i=0;i<81;i++)
		{
			printf("%d ",ArrayAfterRotate[i]);

			if((i % 9) == 8)
				printf("\n");
		}
		}
	}



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
	int a=0,b=0;//random number

	while(a==b || a==0 || b==0)
	{	
		a=rand()%10;
		b=rand()%10;
	}

	changeNum(a,b);
	//printf("error 4\n");

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

	a=0;
	b=0;
	while(a==b)
	{	
		a=rand()%3;
		b=rand()%3;
	}

	changeRow(a,b);
	//printf("error 3\n");

	for(i=0;i<9;i++)


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
	//printf("error 2\n");

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
	//printf("error 1\n");

	for(i=0;i<81;i++)
	{
		CIndex=ColIndex[i];
		RIndex=RowIndex[i];
		BIndex=BlockIndex[i];

		QuestionCol[CIndex] |= Entry[i];
		QuestionBlock[BIndex] |= Entry[i];
		QuestionRow[RIndex] |= Entry[i];

	}

	a=rand()%100;

	

	rotate(0);

	//printf("error 0\n");

	return;

}
