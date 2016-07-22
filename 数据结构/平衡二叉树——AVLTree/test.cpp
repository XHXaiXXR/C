#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "AVLTree.h"

void Test()
{
	int arr[] = {4,2,6,1,3,5,15,7,16,14};
	int size = sizeof(arr)/sizeof(arr[0]);

	AVLTree<int,int> a;
	int i = 0;
	for (;i < size;i++)
	{
		a.Insert(arr[i],i);
	}

	cout<<a.IsBlance()<<endl;
	a.InOrderSort();
}
int main()
{
	Test();
	system("pause");
	return 0;
}