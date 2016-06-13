#define _CRT_SECURE_NO_WARNINGS 1

#include "stack.h"

void test1()//Push  PrintStack  Pop  GetTop  GetElem   MackEmpty
{
	Stack<int> stack;
	stack.Push(1);
	stack.Push(8);
	stack.Push(10);
	stack.Push(5);
	stack.Push(9);
	stack.Push(2);
	stack.PrintStack();

	stack.Pop();
	stack.Pop();
	stack.PrintStack();

	int ret = stack.GetTop();
	printf("%d \n",ret);

	int tmp = stack.GetElem(3);
	printf("%d \n",tmp);

	stack.MackEmpty();
	stack.PrintStack();

}
int main()
{
	test1();
	system("pause");
	return 0;
}