#include<iostream>
using namespace std;
#include<assert.h>

void AdjustDown(int* arr,size_t size,size_t root)
{
	size_t parent = root;
	size_t child = 2*parent+1;

	while(child < size)
	{
		if(child+1 < size && arr[child+1] > arr[child])
		{
			++child;
		}

		if(arr[child] > arr[parent])
		{
			swap(arr[child],arr[parent]);
			parent = child;
			child = 2*parent+1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* arr,int size)
{
	assert(arr);

	for(int i = (size-2)/2;i >= 0;i--)
	{
		AdjustDown(arr,size,i);
	}

	for(int i = size-1;i > 0;i--)
	{
		swap(arr[0],arr[i]);
		AdjustDown(arr,i,0);
	}

	for(int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
void test()
{
	int arr[] = {5,9,3,1,8,6,2,7,0,4};
	int size = sizeof(arr)/sizeof(arr[0]);

	HeapSort(arr,size);
}
int main()
{
	test();
	return 0;
}