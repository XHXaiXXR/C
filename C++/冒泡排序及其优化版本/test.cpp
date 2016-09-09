#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

void BubbleSort_OP2(int* arr ,size_t size)
{
	int n = 0;
	int m = size-1;
	bool flag = true;
	for(int i = 0;i < size-1 && flag;i++)
	{
		flag = false;
		for(int j = 0;j < m;j++)
		{
			if(arr[j] < arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				flag = true;
				n = j;
			}
		}
		m = n;
	}
}
void BubbleSort_OP(int* arr,size_t size)
{
	bool flag = true;
	for(int i = 0;i < size-1 && flag;i++)
	{
		flag = false;
		for(int j = 0;j < size-1-i;j++)
		{
			if(arr[j] < arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				flag = true;
			}
		}
	}
}
void BubbleSort(int* arr,size_t size)
{
	for(int i = 0;i < size-1;i++)
	{
		for(int j = 0;j < size-1-i;j++)
		{
			if(arr[j] < arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}
void test()
{
	int arr[] = {8,5,3,9,1,7,2,4,6,0};
	int arr2[] = {8,9,7,6,5,4,3,2,1};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t size2 = sizeof(arr2)/sizeof(arr2[0]);

	BubbleSort(arr,size);
	BubbleSort_OP(arr2,size2);

	int i = 0;
	for(i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}

	cout<<endl;

	for(i = 0;i < size2;i++)
	{
		cout<<arr2[i]<<" ";
	}
	cout<<endl;

	int arr3[] = {5,1,2,3,4,6,8,0,9,7};
	int size3 = sizeof(arr3)/sizeof(arr3[0]);

	BubbleSort_OP2(arr3,size3);

	for(i = 0;i < size3;i++)
	{
		cout<<arr3[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}