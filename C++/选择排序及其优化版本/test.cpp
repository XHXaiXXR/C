#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

void SelectSort_OP(int* arr,size_t size)
{
	assert(arr);
	int min = 0;
	int max = 0;

	for(int i = 0;i < size;i++)
	{
		min = size-1-i;
		max = i;
		for(int j = i;j < size-i;j++)
		{
			if(arr[min] > arr[j])
			{
				min = j;
			}
			if(arr[max] < arr[j])
			{
				max = j;
			}
		}
		if(min != size-1-i)
		{
			if(max == size-1-i)
			{
				int newmax = min;
				swap(arr[min],arr[size-1-i]);
				max = newmax;
			}
			else
			{
				swap(arr[min],arr[size-1-i]);
			}
		}
		if(max != i)
		{
			swap(arr[max],arr[i]);
		}
	}
}
void SelectSort(int* arr,size_t size)
{
	assert(arr);
	int max = 0;
	int j = 0;

	for(int i = 0;i < size;++i)
	{
		max = i;
		for(j = i+1;j < size;++j)
		{
			if(arr[max] < arr[j])
			{
				max = j;
			}
		}
		if(max != i)
		{
			swap(arr[i],arr[max]);
		}
	}
}
void test()
{
	int arr[] = {2,9,3,6,1,7,4,5,0,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	SelectSort(arr,size);

	for(int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;

	int arr2[] = {2,9,3,6,1,7,4,5,0,8};
	//int arr2[] = {0,4,3,2,1,9};
	size_t size2 = sizeof(arr2)/sizeof(arr2[0]);

	SelectSort_OP(arr2,size2);

	for(int i = 0;i < size2;i++)
	{
		cout<<arr2[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}