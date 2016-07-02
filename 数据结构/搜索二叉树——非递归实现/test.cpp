#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "BSTree.h"

void TestBSTree()
{
	BSTree<int,int> bs;
	int arr[] = {5,9,3,6,7,0,4,2,8,1};
	int size = sizeof(arr)/sizeof(arr[0]);

	for (int i = 0;i <size;i++)
	{
		bs.Insert(arr[i],i+1);
	}

	cout<<bs.Find(0)->_key<<endl;
	cout<<bs.Find(0)->_value<<endl;

	bs.InOrder();
	cout<<endl;

	bs.ReMove(0);
	bs.ReMove(3);
	bs.ReMove(4);
	bs.ReMove(7);
	bs.ReMove(8);
	//bs.ReMove(55);

	bs.InOrder();
	cout<<endl;
}

int main()
{
	TestBSTree();
	system("pause");
	return 0;
}