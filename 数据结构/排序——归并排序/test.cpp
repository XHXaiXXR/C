#include<iostream>
using namespace std;
void Sort(int* arr,int* tmp,int begin,int mid,int end)
{
	int index = 0;
	int left = begin;
	int right = mid + 1;

	while(left <= mid && right <= end)
	{
		if(arr[left] < arr[right])
			tmp[index++] = arr[left++];
		else
			tmp[index++] = arr[right++];
	}

	while(left <= mid)
		tmp[index++] = arr[left++];
	while(right <= end)
		tmp[index++] = arr[right++];
	
	index = 0;
	for(int i = begin;i <= end;++i)
	{
		arr[i] = tmp[index++];
	}
}

void _MergeSort(int* arr,int* tmp,int begin,int end)
{
	if(begin >= end)
		return;
	
	int mid = begin + (end - begin)/2;

	_MergeSort(arr,tmp,begin,mid);
	_MergeSort(arr,tmp,mid+1,end);

	Sort(arr,tmp,begin,mid,end);
}

void MergeSort(int* arr,size_t size)
{
	int* tmp = new int[size];

	_MergeSort(arr,tmp,0,size-1);

	delete[] tmp;
}

void test()
{
	int arr[] = {3,8,2,0,7,6,1,5,9,4};
	//int arr[] = {3,8,2};
	int size = sizeof(arr)/sizeof(arr[0]);

	
	MergeSort(arr,size);

	for(size_t i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	return 0;
}