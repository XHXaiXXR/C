#include<iostream>
using namespace std;
#include<assert.h>

void InsertSort(int* arr,size_t size)
{
	assert(arr);

	for(int i = 0;i < size-1;i++)
	{
		int j = i;
		int tmp = arr[i+1];

		while(j >= 0 && arr[j] > tmp)
		{
			arr[j+1] = arr[j];
			j--;
		}

		arr[j+1] = tmp;
	}
}

void test()
{
	int arr[] = {3,7,1,0,2,6,8,5,9,4};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	InsertSort(arr,size);

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