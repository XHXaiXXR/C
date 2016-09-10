#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

void HeapAdjust(int* arr,int parent,size_t size)
{
	assert(arr);
	int child = 2*parent+1;

	while(child && child < size)
	{
		if((child+1 < size) && (arr[child+1] > arr[child]))
		{
			++child;
		}
		if(arr[parent] < arr[child])
		{
			swap(arr[parent],arr[child]);
		}
		parent = child;
		child = 2*parent+1;
	}
}
void test()
{
	int arr[] = {5,3,9,2,7,1,8,0,4,6};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	//先建立一个大顶堆
	for(int i = (size-2)/2;i >= 0;i--)
	{
		HeapAdjust(arr,i,size);
	}

	for(int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;

	//把根节点的值和最后一个节点的值进行交换，在从根节点开始向下调整
	for(int i = size-1;i >= 0;i--)
	{
		swap(arr[0],arr[i]);
		HeapAdjust(arr,0,i);
	}
	for(int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}