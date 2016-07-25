#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "BinaryTreeThd.h"

void Test()
{
	int arr1[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size1 = sizeof(arr1)/sizeof(arr1[0]);
	BinaryTreeThd<int> t1(arr1,size1,'#');

	cout<<"前序遍历： ";
	t1.PrevOrder();
	cout<<"中序遍历： ";
	t1.InOrder();
	cout<<"后序遍历： ";
	t1.PostOrder();

	t1.PrevOrderThreading();
	cout<<"（线索化）前序遍历： ";
	t1.PrevOrderThd();


	int arr2[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size2 = sizeof(arr2)/sizeof(arr2[0]);
	BinaryTreeThd<int> t2(arr2,size2,'#');

	cout<<endl;
	cout<<"前序遍历： ";
	t2.PrevOrder();
	cout<<"中序遍历： ";
	t2.InOrder();
	cout<<"后序遍历： ";
	t2.PostOrder();

	t2.InOrderThreading();
	cout<<"（线索化）中序遍历： ";
	t2.InOrderThd();
}

int main()
{
	Test();
	system("pause");
	return 0;
}