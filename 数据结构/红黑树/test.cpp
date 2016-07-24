#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "RBTree.h"

void Test()
{
	RBTree<int,int> rbt;
	//int arr[] = {16,3,7,11,9,26,18,14,15};
	int arr[] = {48,12,56,32,99,11,10,78,22};
	int size = sizeof(arr)/sizeof(arr[0]);

	for (int i = 0;i < size;i++)
	{
		rbt.Insert(arr[i],i);
		cout<<"IsBlance? "<<rbt.IsBlance()<<endl;
	}
	rbt.InOrder();
	cout<<"IsBlance? "<<rbt.IsBlance()<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}