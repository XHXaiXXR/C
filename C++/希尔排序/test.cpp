#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

void ShellSort(int* arr,size_t size)
{
	assert(arr);
	int tmp = 0,i = 0,j = 0,count = size;

	do
	{
		count = count / 3 + 1;

		for(i = count;i < size;i++)
		{
			if(arr[i-count] > arr[i])
			{
				tmp = arr[i];
				for(j = i - count;j >= 0 && arr[j] > tmp;j -= count)
				{
					arr[j+count] = arr[j];
				}
				arr[j+count] = tmp;
			}
		}
	}while(count > 1);
}
void test()
{
	int arr[] = {0,9,1,5,8,3,7,4,6,2};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	ShellSort(arr,size);

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