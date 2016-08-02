#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "BTree.h"

void Test1()
{
	BTree<int,3> bt;
	bt.Insert(20);
	bt.Insert(30);
	bt.Insert(10);
}
void Teat2()
{
	BTree<int,3> bt;
	int arr[] = {53,75,139,49,145,36,101};
	int size = sizeof(arr)/sizeof(arr[0]);
	for (size_t i = 0;i < size;i++)
	{
		bt.Insert(arr[i]);
	}
	bt.InOrder();
}
int main()
{
	//Test1();
	Teat2();
	system("pause");
	return 0;
}