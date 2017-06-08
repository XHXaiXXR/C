#include<iostream>
using namespace std;
#include<stack>
#include <stdio.h>

#define N 11//行
#define M 10//列

void InitMaze(int* maze, int n, int m)
{
	FILE* f = fopen("maze.txt", "r");//只读形式打开文件“maze.txt”

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; )
		{
			char c = fgetc(f);//逐个读取

			if (c == '0' || c == '1')
			{
				maze[i * m + j] = c - '0';//将读到的字符按照文件的顺序依次存储到二维数组中
				j++;
			}
		}
	}
}

void PrintMaze(int* maze, int n, int m)
{
	for (int i = 0;i < n; ++i)
	{
		for (int j = 0;j < m; ++j)
		{
			cout<<maze[i * m + j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl;
}

struct Pos
{
	int _row;//行
	int _col;//列
};

bool CheckAccess(int* maze, Pos cur, int n, int m)
{
	if ((cur._col >= 0) && (cur._col < m) 
		&& (cur._row >= 0) && (cur._row < n) 
		&& (maze[cur._row * m + cur._col] == 0))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

bool GetPath(int* maze, int n, int m, stack<Pos> s, Pos pos)
{
	s.push(pos);
	maze[pos._row * m + pos._col] = 2;

	while (!s.empty())
	{
		Pos cur = s.top();

		if ((cur._row == 0) || (cur._row == n-1) || (cur._col == m-1))
		{
			return true;
		}

		Pos next = cur;
		//上
		next._row--;
		if (CheckAccess(maze, next, n, m))
		{
			s.push(next);
			maze[next._row * m +next._col] = 2;
			continue;
		}

		next = cur;
		//右
		next._col++;
		if (CheckAccess(maze, next, n, m))
		{
			s.push(next);
			maze[next._row * m +next._col] = 2;
			continue;
		}

		next = cur;
		//下
		next._row++;
		if (CheckAccess(maze, next, n, m))
		{
			s.push(next);
			maze[next._row * m +next._col] = 2;
			continue;
		}

		next = cur;
		//左
		next._col--;
		if (CheckAccess(maze, next, n, m))
		{
			s.push(next);
			maze[next._row * m +next._col] = 2;
			continue;
		}

		s.pop();
	}

	return false;
}

void test()
{
	int maze[N][M] = {0};

	InitMaze((int *)maze, N, M);//初始化二维数组
	PrintMaze((int *)maze, N, M);//打印二维数组

	Pos pos = {2, 0};//{行，列}，给一个入口位置
	stack<Pos> s;

	GetPath((int *)maze, N, M, s, pos);//获取迷宫路径
	PrintMaze((int *)maze, N, M);
}

int main()
{
	test();
	system("pause");
	return 0;
}