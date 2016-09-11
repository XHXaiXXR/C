#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <stack>
#define ROW 12
#define COL 10

struct Pos
{
	int _row;
	int _col;
};

void PrintMaze(int* maze,int row,int col)
{
	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;j++)
		{
			cout<<maze[i*col+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void InitMaze(int* maze,int row,int col)
{
	FILE* fout = fopen("Maze2.txt","r");

	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;)
		{
			char c = fgetc(fout);
			if (c == '0' || c == '1')
			{
				maze[i*col+j] = c - '0';
				j++;
			}
		}
	}

	fclose(fout);
}
void InitMinMaze(int* minmaze,int row,int col)
{
	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;j++)
		{
			minmaze[i*col+j] = 1;
		}
	}
}

bool CheckAccess(int* maze,int row,int col,Pos pos)
{
	if(pos._row >= 0
		&& pos._row < row
		&& pos._col >= 0
		&& pos._col < col
		&& maze[pos._row*col+pos._col] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GetPath(int* maze,int* minmaze,int row,int col,stack<Pos>& s,Pos pos,int& min)
{
	s.push(pos);
	maze[pos._row*col+pos._col] = 2;

	while (!s.empty())
	{
		Pos cur = s.top();
		if (cur._row == row - 1
			|| cur._col == col - 1
			|| cur._row == 0)
		{
			if (min > s.size())
			{
				min = s.size();
				stack<Pos> tmp;
				InitMinMaze(minmaze,row,col);
				while (!s.empty())
				{
					tmp.push(s.top());
					minmaze[s.top()._row*col+s.top()._col] = 2;
					s.pop();
				}
				while (!tmp.empty())
				{
					s.push(tmp.top());
					tmp.pop();
				}
				maze[cur._row*col+cur._col] = 2;
				s.pop();
			} 
			else
			{
				maze[cur._row*col+cur._col] = 2;
				s.pop();
			}
		}

		//上
		Pos next = cur; 
		next._row--;
		if (CheckAccess(maze,row,col,next))
		{
			maze[next._row*col+next._col] = 2;
			s.push(next);
			continue;
		}
		//右
	    next = cur; 
		next._col++;
		if (CheckAccess(maze,row,col,next))
		{
			maze[next._row*col+next._col] = 2;
			s.push(next);
			continue;
		}
		//下
		next = cur; 
		next._row++;
		if (CheckAccess(maze,row,col,next))
		{
			maze[next._row*col+next._col] = 2;
			s.push(next);
			continue;
		}
		//左
		next = cur; 
		next._col--;
		if (CheckAccess(maze,row,col,next))
		{
			maze[next._row*col+next._col] = 2;
			s.push(next);
			continue;
		}
		s.pop();
	}

}

void test()
{
	int maze[ROW][COL] = {0};
	int minmaze[ROW][COL] = {0};

	InitMaze((int*)maze,ROW,COL);
	PrintMaze((int*)maze,ROW,COL);

	InitMinMaze((int*)minmaze,ROW,COL);
	//PrintMaze((int*)minmaze,ROW,COL);

	stack<Pos> s;
	Pos pos = {1,0};
	int min = 10000000;
	GetPath((int*)maze,(int*)minmaze,ROW,COL,s,pos,min);
	PrintMaze((int*)minmaze,ROW,COL);
	cout<<"路径长度 = "<<min<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}


