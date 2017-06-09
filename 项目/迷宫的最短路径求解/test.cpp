#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include<stack>

#define N 11 //行
#define M 10 //列

void InitMaze(int* maze, int n, int m)
{
	FILE* f = fopen("maze.txt", "r");//打开文件，以只读的形式打开

	for (int i = 0;i < n; ++i)
	{
		for (int j = 0;j < m; )
		{
			char c = fgetc(f);//读取文件当前位置的字符

			if (c == '0' || c == '1' || c == '2')
			{
				maze[i * m + j] = c - '0';
				++j;//只有获取到相关字符的时候j才偏移
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
	int _row; //行
	int _col; //列
};

//检查下一个节点的位置是否可以走？
//（1）如果下一个节点的值是0，就说明可以走。
//（2）如果下一个节点的值比当前节点值大，说明此路可以通
bool CheckPath(int* maze, int n, int m, Pos cur, Pos next)
{
	if ((next._row >= 0) && (next._row < n)
		&& (next._col >= 0) && (next._col < m) 
		&& ((maze[next._row * m + next._col] == 0) || (maze[next._row * m + next._col] > maze[cur._row * m + cur._col])))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//递归的方式去寻找通路
void FindAccess(int* maze, int n, int m, Pos pos, stack<Pos>& s, stack<Pos>& short_s)
{
	if ((pos._row == 0) 
		|| (pos._row == n-1) 
		|| (pos._col == m-1))
	{
		//每次需要判断当前栈中的数目是不是小于存放最短路径的栈，如果小于，则将存放最短路径的栈重置
		if ((short_s.size() == 0) || (short_s.size() > s.size()))
		{
			short_s = s;//将当前栈中的值赋给存放最短路径的栈
		}
		//给递归一个返回条件
		return;
	}

	Pos next = pos;
	//上（上->右->下->左）
	next._row--;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//右（上->右->下->左）
	next = pos;
	next._col++;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//下（上->右->下->左）
	next = pos;
	next._row++;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//左（上->右->下->左）
	next = pos;
	next._col--;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	s.pop();
}

void test()
{
	int maze[N][M] = {0};
	InitMaze((int *)maze, N, M);
	PrintMaze((int *)maze, N, M);

	Pos pos = {2, 0};//Pos类型的一个数据结构，里面包含着坐标（y，x）,这里初始化给了一个迷宫的入口点
	stack<Pos> s;
	maze[pos._row][pos._col] = 2;
	s.push(pos);
	stack<Pos> short_s;

	FindAccess((int *)maze, N, M, pos, s, short_s);
	PrintMaze((int *)maze, N, M);
	
	cout<<"打印最短路径(逆序打印)"<<endl;
	while (!short_s.empty())
	{
		cout<<"["<<short_s.top()._row<<","<<short_s.top()._col<<"]"<<endl;
		short_s.pop();
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}