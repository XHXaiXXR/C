#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"

void test1()//InsertSort
{
	int arr[] = {1,4,3,8,2,9,8,4,6};
	int size = sizeof(arr)/sizeof(arr[0]);
	InsertSort(arr,size);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
void test2()//SellSort
{
	int arr[] = {6,7,8,9,0,1,2,6,4,5};
	int size = sizeof(arr)/sizeof(arr[0]);
	SellSort(arr,size);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void test3()//SelectSort
{
	int arr[] = {6,5,1,7,2,9,1,4,6};
	//int arr[] = {6,5,1,7,2,9,3,4,8};	
	int size = sizeof(arr)/sizeof(arr[0]);
	//SelectSort(arr,size);
	SelectSort_OP(arr,size);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void test4()//QuickSort  QuickSort_NonR
{
	int arr[] = {1,4,3,8,2,2,8,2,6};
	//int arr[] = {4,1};
	int size = sizeof(arr)/sizeof(arr[0]);
	//QuickSort(arr,0,8);
	//QuickSort(arr,0,1);

	QuickSort_NonR(arr,0,8);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	system("pause");
	return 0;
}


