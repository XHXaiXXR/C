#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<stdio.h>
#include<stack>

#define N 11
#define M 10

struct Pos
{
	int _row;
	int _col;

	//	Pos(int row = 0;int col = 0)
	//		:_row(row)
	//		,_col(col)
	//	{}
};

bool CheckAccess(int* maze,int row,int col,Pos pos)
{
	if(pos._row >= 0\
		&& pos._row < row\
		&& pos._col >= 0\
		&& pos._col < col\
		&& maze[pos._row*col+pos._col] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool GetPath(int* maze,int row,int col,stack<Pos> s,Pos pos)
{
	s.push(pos);
	maze[pos._row*M+pos._col] = 2;

	while(!s.empty())
	{
		Pos cur = s.top();
		if(cur._row == 0\
			|| cur._row  == row-1\
			|| cur._col == col-1)
		{
			return true;
		}

		Pos next = cur;
		//shang
		next._row--;
		if(CheckAccess(maze,row,col,next))
		{
			maze[next._row*col + next._col] = 2;
			s.push(next);
			continue;
		}
		//you
		next = cur;
		next._col++;
		if(CheckAccess(maze,row,col,next))
		{
			maze[next._row*col + next._col] = 2;
			s.push(next);
			continue;
		}
		//xia
		next = cur;
		next._row++;
		if(CheckAccess(maze,row,col,next))
		{
			maze[next._row*col + next._col] = 2;
			s.push(next);
			continue;
		}
		//zuo
		next._col--;
		if(CheckAccess(maze,row,col,next))
		{
			maze[next._row*col + next._col] = 2;
			s.push(next);
			continue;
		}
		s.pop();
	}
	return false;
}
void PrintMaze(int* maze,int n,int m)
{
	for(int i = 0;i < n;++i)
	{
		for(int j = 0;j < m;++j)
		{
			cout<<maze[i*m+j]<<" ";
		}
		cout<<endl;
	}
}
void InitMaze(int* maze,int n,int m)
{
	FILE* fout = fopen("Maze.txt","r");
	for(int i = 0;i < n;++i)
	{
		for(int j = 0;j < m;)
		{
			char fchar = fgetc(fout);
			if(fchar == '0' || fchar == '1')
			{
				maze[i*m+j] = fchar - '0';
				++j;
			}
		}
	}
	fclose(fout);
}
void testmaze()
{
	int maze[N][M] = {0};

	InitMaze((int*)maze,N,M);
	PrintMaze((int*)maze,N,M);
	cout<<endl;

	Pos pos = {2,0};
	stack<Pos> s;

	GetPath((int*)maze,N,M,s,pos);
	PrintMaze((int*)maze,N,M);
	cout<<endl;
}
int main()
{
	testmaze();
	system("pause");
	return 0;
}