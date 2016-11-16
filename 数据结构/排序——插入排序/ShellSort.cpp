#include<iostream>
using namespace std;
#include<assert.h>

void ShellSort(int* arr,size_t size)
{
	assert(arr);
	int gap = size;

	while(gap > 1)
	{
		gap = gap / 3 + 1;
		for(int i = 0;i < size - gap;i++)
		{
			int j = i;
			int tmp = arr[i+gap];

			while(j >= 0 && arr[j] > tmp)
			{
				arr[j + gap] = arr[j];
				j -= gap;
			}

			arr[j + gap] = tmp;
		}
	}
}

void test()
{
	int arr[] = {3,4,1,2,8,9,5,6,0,7};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	ShellSort(arr,size);

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