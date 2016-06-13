#define _CRT_SECURE_NO_WARNINGS 1
#include "queue.h"

void test()
{
	Queue<int> queue;
	queue.Push(1);
	queue.Push(4);
	queue.Push(7);
	queue.Push(9);
	queue.PrintQueue();

	queue.Pop();
	queue.Pop();
	queue.PrintQueue();

	int ret = queue.Back()-queue.Front();
	cout<<ret<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}