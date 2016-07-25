#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "BinaryTreeThd.h"

void Test()
{
	int arr1[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size1 = sizeof(arr1)/sizeof(arr1[0]);
	BinaryTreeThd<int> t1(arr1,size1,'#');

	cout<<"ǰ������� ";
	t1.PrevOrder();
	cout<<"��������� ";
	t1.InOrder();
	cout<<"��������� ";
	t1.PostOrder();

	t1.PrevOrderThreading();
	cout<<"����������ǰ������� ";
	t1.PrevOrderThd();


	int arr2[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size2 = sizeof(arr2)/sizeof(arr2[0]);
	BinaryTreeThd<int> t2(arr2,size2,'#');

	cout<<endl;
	cout<<"ǰ������� ";
	t2.PrevOrder();
	cout<<"��������� ";
	t2.InOrder();
	cout<<"��������� ";
	t2.PostOrder();

	t2.InOrderThreading();
	cout<<"������������������� ";
	t2.InOrderThd();
}

int main()
{
	Test();
	system("pause");
	return 0;
}