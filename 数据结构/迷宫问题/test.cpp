#define _CRT_SECURE_NO_WARNINGS 1
#include "maze.h"

void test()
{
	int maze[10][10] = {};
	InitMaze((int* )maze,10);
	PrintMaze((int* )maze,10);

	Pos entry = {2,0};//��ڸ���maze[2][0]
	stack<Pos> path;//��Ҫջ��Э��
	GetMazePath((int* )maze,10,entry,path);
	PrintMaze((int* )maze,10);

}
int main()
{
	test();
	system("pause");
	return 0;
}