#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "Sort.h"
#include <vector>

void PrintArr(vector<int> arr,size_t size)
{
	for (size_t i = 0;i < size;++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void test1()
{
	//int arr[] = {2,1,8,5,0,4,6,5};
	vector<int> arr;
	arr.push_back(2);
	arr.push_back(9);
	arr.push_back(3);
	arr.push_back(6);
	arr.push_back(1);
	arr.push_back(7);
	arr.push_back(4);
	arr.push_back(5);
	arr.push_back(0);
	arr.push_back(8);
	//int size = sizeof(arr)/sizeof(arr[0]);

	PrintArr(arr,arr.size());
	//BubbingSort(arr, size);
	//BubbingSortOp(arr,size);
	//SelectSort(arr,arr.size());
	//InsertSort(arr,arr.size());
	//ShellSort(arr,arr.size());
	//HeapSort(arr,arr.size());
	//MergeSort(arr,arr.size());
	QuickSort(arr,arr.size());
	PrintArr(arr,arr.size());
}

int main()
{
	test1();
	system("pause");
	return 0;
}