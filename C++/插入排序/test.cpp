#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

void InsertSort(int* arr,size_t size)
{
	assert(arr);
	int i = 1;

	while(i < size)
	{
		int j = 0;
		int tmp = arr[i];
		for(j = i-1;j >= 0 && arr[j] < tmp;j--)
		{
			arr[j+1] = arr[j];
		}
		arr[j+1] = tmp;
		i++;
	}
}
void test()
{
	int arr[] = {9,3,4,6,1,5,5,6,8,0,2,7,5};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	InsertSort(arr,size);

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