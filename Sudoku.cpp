#include"Sudoku.h"
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<algorithm>

using namespace std;

int i,j,k;
int theQuestion[81]; //readin()

int BlockIndex[81];
int RowIndex[81];
int ColIndex[81];

const int ZERO=0;
const int ALL=0x3fe;   // 1111111110

int Entry[81];
int Posible_Block[9];
int Posible_Row[9];
int Posible_Col[9];

int RQuestion[9];
int BQuestion[9];
int CQuestion[9];
int RCheck[9];
int CCheck[9];
int BCheck[9];

int sort_counter=0;
int Sort[81];

int succed_counter;
int Multiple_ans;

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
	
void Sudoku::readIn()
{
	int tmp;
	i=0;

	for(i=0;i<81;i++)
	{
		scanf("%1d",&tmp);
		theQuestion[i]=tmp;
	}

	for(i=0;i<81;i++) //check theQuestion[]
	{
		//printf("%d ",theQuestion[i]);
		//if((i%9)==8)
			//printf("\n");
	}
	return;

}

void InitEntry(int Index,int value)
{
 
	int Bit= 1<<value;
	int sort_counter2;
	int BIndex=BlockIndex[Index];
	int RIndex=RowIndex[Index];
	int CIndex=ColIndex[Index];

	Entry[Index] = Bit;
	Posible_Block[BIndex] &= ~Bit;
	Posible_Col[CIndex] &= ~Bit; 
	Posible_Row[RIndex] &= ~Bit;

	BQuestion[BIndex] |= Bit; 
	CQuestion[CIndex] |= Bit;
	RQuestion[RIndex] |= Bit;

	if(BQuestion[BIndex]==BCheck[BIndex] || CQuestion[CIndex]==CCheck[CIndex] || RQuestion[RIndex]==RCheck[RIndex])
	{
		printf("0\n");
		exit(0);
	}
	else
	{
		BCheck[BIndex]=BQuestion[BIndex];
		CCheck[CIndex]=CQuestion[CIndex];
		RCheck[RIndex]=RQuestion[RIndex];
	}





	sort_counter2=sort_counter;
	while(sort_counter2<81 && Sort[sort_counter2]!=Index)
		sort_counter2++ ;
	
	swap(Sort[sort_counter],Sort[sort_counter2]);
	sort_counter++;
}


void ConvetArrytoNumber()
{
     int value;
     for(i=0;i<81;i++)
     {
     	if(Entry[i]==0)
     		theQuestion[i]=0;
     	else
     	{
     		for(value=0;value<=9;value++)
     			if(Entry[i]==(1<<value))
     				theQuestion[i]=value;
     	}
     }  
    
}


void SolveReadIn()
{
	for(i=0;i<81;i++)
	{
		if(theQuestion[i]!=0)
		{
			InitEntry(i,theQuestion[i]);
		}
	}
}


void Succeed()
{
     ConvetArrytoNumber();
}


int IndexOfMinimunPosible(int S)
{
    int S2;
    int Index;
    int posible;
    int minimun_posible=0;
    int Total_posible=10;
    int test;

    int BIndex;
	int RIndex;
	int CIndex;

    for (test=S;test<81;test++)
    {
        Index=Sort[test];
        BIndex=BlockIndex[Index];
		RIndex=RowIndex[Index];
		CIndex=ColIndex[Index];

        posible=Posible_Block[BIndex] & Posible_Row[RIndex] & Posible_Col[CIndex];
        minimun_posible=0;

        while(posible)
        {
           posible &= ~(posible & -posible);
           minimun_posible++;
        }

        if (minimun_posible<Total_posible)
        {
           Total_posible=minimun_posible;
           S2=test;
        }
    }

    return S2;
}


void SolveNow(int S)
{
    if(S>=81)
    {
    	Succeed();
    	succed_counter++;

    	if(succed_counter>1)
    	{
    		Multiple_ans=2;
    	}
    	return;
    }

    int S2=IndexOfMinimunPosible(S);
    swap(Sort[S],Sort[S2]);

    int Index=Sort[S];

    int BIndex=BlockIndex[Index];
    int RIndex=RowIndex[Index];
    int CIndex=ColIndex[Index];

    int posible=Posible_Block[BIndex] & Posible_Row[RIndex] & Posible_Col[CIndex];

    while(posible)
    {
        int Bit=posible & (-posible); //take one posible
         
        posible &= ~Bit;

        Entry[Index]=Bit;
        Posible_Block[BIndex] &= ~Bit;
        Posible_Row[RIndex] &= ~Bit;
        Posible_Col[CIndex] &= ~Bit;
        
        SolveNow(S+1);

        Entry[Index]=ZERO;
        Posible_Block[BIndex] |= Bit;
        Posible_Row[RIndex] |= Bit;
        Posible_Col[CIndex] |= Bit;
	}

    swap(Sort[S],Sort[S2]);
}


void Sudoku::solve()
{
	int Index;

	sort_counter=0;
	Multiple_ans=0;
	succed_counter=0;

	for(i=0;i<9;i++)//iniliatiation
	{
	   	for(j=0;j<9;j++)
	   	{
	     	Index=9*i+j;
	    	RowIndex[Index]=i;
		   	ColIndex[Index]=j;
	    	BlockIndex[Index]=(i/3)*3+(j/3);
	    }
	    Posible_Block[i]=Posible_Row[i]=Posible_Col[i]=ALL;
	    RQuestion[i]=CQuestion[i]=BQuestion[i]=ZERO;
	    RCheck[i]=BCheck[i]=CCheck[i]=ZERO;
    }


	for (Index=0;Index<81;Index++)//iniliatiation
	{
	  	Sort[Index]=Index;
	   	Entry[Index]=ZERO;
	}

	SolveReadIn(); 

	//check two row or col all in 0
	int row=0;
	int col=0;
	for(i=0;i<9;i++)
	{
		if(Posible_Col[i]==1022)
			col=1;

		if(Posible_Row[i]==1022)
			row=1;

		if(col)
		{
			if((i%3)==0)
			{
				if(Posible_Col[i+1]==1022 || Posible_Col[i+2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
			else if((i%3)==1)
			{
				if(Posible_Col[i-1]==1022 || Posible_Col[i+2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
			else if((i%3)==2)
			{
				if(Posible_Col[i-1]==1022 || Posible_Col[i-2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
		}

		if(row)
		{
			if((i%3)==0)
			{
				if(Posible_Row[i+1]==1022 || Posible_Row[i+2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
			else if((i%3)==1)
			{
				if(Posible_Row[i-1]==1022 || Posible_Row[i+2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
			else if((i%3)==2)
			{
				if(Posible_Row[i-1]==1022 || Posible_Row[i-2]==1022)
				{
					printf("2\n");
					exit(0);
				}
			}
		}

		row=0;
		col=0;
	}

    SolveNow(sort_counter);
	       
    for(i=0;i<81;i++)
    {
    	if(theQuestion[i]==0)
    	{
    		Multiple_ans=3;
    		break;
    	}
    }

    

    if(Multiple_ans==3)
    {
    	printf("0\n");
    }
    else if(Multiple_ans==2)
    {
    	printf("2\n");
    }
    else if(Multiple_ans==0)
    {
    	printf("1\n");
    	for(i=0;i<81;i++)
		{
			printf("%d ",theQuestion[i]);

			if((i%9)==8)
				printf("\n");
		}
	}



  return ;

}
	
void Sudoku::changeNum(int a , int b)
{

	for(i=0;i<81;i++)
	{		
		if(theQuestion[i]==a)
		{

			theQuestion[i]=b;
		}

		else if(theQuestion[i]==b)
		{
			theQuestion[i]=a;			
		}
	}

	return;
}
	
void Sudoku::changeRow(int a , int b)
{
	if(a>b)
		swap(a,b);

	for(i=0;i<27;i++)
		swap(theQuestion[a*27+i], theQuestion[b*27+i]);

	return;
}
	
void Sudoku::changeCol(int a , int b)
{
	if(a>b)
		swap(a,b);

	for(j=0;j<3;j++)
	{	
		for(i=0;i<9;i++)
			swap(theQuestion[(a*3+j)+(9*i)],theQuestion[(b*3+j)+(9*i)]);
	}
	return;
}

void Sudoku::rotate(int n)
{
	int a=n%5;
	int Array[81];

	if(a==0)
		return;

	while(a--)
	{
		k=0;
		for(i=8;i>=0;i--)
		{
			for(j=0;j<9;j++)
			{
				Array[i+9*j]=theQuestion[k];
				k=k+1;
			}
		}

		for(i=0;i<81;i++)
		{

			theQuestion[i]=Array[i];
		}

	}

	return;
}

void horizontal()
{
	for(i=0;i<4;i++)
	{
		for(j=0;j<9;j++)
			swap(theQuestion[i*9+j],theQuestion[(8-i)*9+j]);
	}

	return;
}	

void vertical()
{
	for(i=0;i<4;i++)
	{
		for(j=0;j<9;j++)
			swap(theQuestion[(j*9)+i], theQuestion[(8-i)+9*j]);
	}
	return;
}

void Sudoku::flip(int n)
{
	if(n==0)
	{
		vertical();
	}
	else if(n==1)
	{
		horizontal();
	}
}
	
void Sudoku::transform()
{
	int a,b;
	srand(time(NULL));

	while(a==b || a==0 || b==0) //random a,b for changeNum()
	{
		a=rand()%10;
		b=rand()%10;
	}
	changeNum(5,9);

	a=0;
	b=0;
	while(a==b) //random a,b for changeRow()
	{
		a=rand()%3;
	
		b=rand()%3;
	}
	changeRow(1,2);

	a=0;
	b=0;
	while(a==b) //random a,b for changeCol()
	{
		a=rand()%3;
		b=rand()%3;
	}
	changeCol(0,2);

	a=rand()%100;//random a for rotate()
	rotate(41);

	a=rand()%2; //random a for flip;
	flip(1);

	for(i=0;i<81;i++)
	{
		printf("%d ",theQuestion[i]);

		if((i%9)==8)
			printf("\n");
	}

	return;
}