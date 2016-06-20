#pragma once

#include <iostream>
using namespace std;
#include <stack>
#include<assert.h>

void InitMaze(int* maze,size_t n)
{
	assert(maze);
	FILE* fout = fopen("MazeMap.txt","r");

	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;)
		{
			char c = fgetc(fout);
			if (c == '0' || c == '1')
			{
				maze[i * n + j] = c - '0';
				j++;
			}
		}
	}
	fclose(fout);
}

void PrintMaze(int* maze,size_t n)
{
	assert(maze);

	for (int i = 0; i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			cout<<maze[i * n +j]<<" ";
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

bool CheckIsAccess(int* maze,size_t n,Pos entry)//数组边界条件的检查  是否允许探测
{
	if (entry._row >= 0 && entry._col >= 0
		&& entry._row < n && entry._col < n
		&& maze[entry._row * n + entry._col] == 0)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

bool GetMazePath(int* maze,size_t n,Pos entry,stack<Pos>& path)//探测
{
	assert(maze);

	path.push(entry);
	maze[entry._row * n + entry._col] = 2;

	while (!path.empty())
	{
		Pos cur = path.top();
		if (cur._row == n-1 || cur._col == n-1)
		{
			return true;
		}

		//上
		Pos next = cur;
		next._row--;
		if (CheckIsAccess(maze,n,next))
		{
			maze[next._row * n + next._col] = 2;
			path.push(next);
			continue;
		}

		//右
		next = cur;
		next._col++;
		if (CheckIsAccess(maze,n,next))
		{
			maze[next._row * n + next._col] = 2;
			path.push(next);
			continue;
		}

		//下
		next = cur;
		next._row++;
		if (CheckIsAccess(maze,n,next))
		{
			maze[next._row * n + next._col] = 2;
			path.push(next);
			continue;
		}

		//左
		next = cur;
		next._col--;
		if (CheckIsAccess(maze,n,next))
		{
			maze[next._row * n + next._col] = 2;
			path.push(next);
			continue;
		}

		path.pop();
	}
	return false;
}