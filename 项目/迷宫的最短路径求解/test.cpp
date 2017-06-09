#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include<stack>

#define N 11 //��
#define M 10 //��

void InitMaze(int* maze, int n, int m)
{
	FILE* f = fopen("maze.txt", "r");//���ļ�����ֻ������ʽ��

	for (int i = 0;i < n; ++i)
	{
		for (int j = 0;j < m; )
		{
			char c = fgetc(f);//��ȡ�ļ���ǰλ�õ��ַ�

			if (c == '0' || c == '1' || c == '2')
			{
				maze[i * m + j] = c - '0';
				++j;//ֻ�л�ȡ������ַ���ʱ��j��ƫ��
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
	int _row; //��
	int _col; //��
};

//�����һ���ڵ��λ���Ƿ�����ߣ�
//��1�������һ���ڵ��ֵ��0����˵�������ߡ�
//��2�������һ���ڵ��ֵ�ȵ�ǰ�ڵ�ֵ��˵����·����ͨ
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

//�ݹ�ķ�ʽȥѰ��ͨ·
void FindAccess(int* maze, int n, int m, Pos pos, stack<Pos>& s, stack<Pos>& short_s)
{
	if ((pos._row == 0) 
		|| (pos._row == n-1) 
		|| (pos._col == m-1))
	{
		//ÿ����Ҫ�жϵ�ǰջ�е���Ŀ�ǲ���С�ڴ�����·����ջ�����С�ڣ��򽫴�����·����ջ����
		if ((short_s.size() == 0) || (short_s.size() > s.size()))
		{
			short_s = s;//����ǰջ�е�ֵ����������·����ջ
		}
		//���ݹ�һ����������
		return;
	}

	Pos next = pos;
	//�ϣ���->��->��->��
	next._row--;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//�ң���->��->��->��
	next = pos;
	next._col++;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//�£���->��->��->��
	next = pos;
	next._row++;
	if (CheckPath(maze, n, m, pos, next))
	{
		maze[next._row * m + next._col] = maze[pos._row * m + pos._col] + 1;
		s.push(next);
		FindAccess(maze, n, m, next, s, short_s);
	}

	//����->��->��->��
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

	Pos pos = {2, 0};//Pos���͵�һ�����ݽṹ��������������꣨y��x��,�����ʼ������һ���Թ�����ڵ�
	stack<Pos> s;
	maze[pos._row][pos._col] = 2;
	s.push(pos);
	stack<Pos> short_s;

	FindAccess((int *)maze, N, M, pos, s, short_s);
	PrintMaze((int *)maze, N, M);
	
	cout<<"��ӡ���·��(�����ӡ)"<<endl;
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