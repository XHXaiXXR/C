#include<iostream>
using namespace std;

void CountSort(int* arr,int size)
{
	int min = arr[0];
	int max = arr[0];

	for(int i = 1;i < size;++i)
	{
		if(arr[i] < min)
			min = arr[i];
		if(arr[i] > max)
			max = arr[i];
	}

	int range = max - min + 1;
	int* count = new int[range];

	for(int i = 0;i < size;++i)
	{
		count[arr[i] - min]++;
	}

	int index = 0;
	for(int i = 0;i < range;i++)
	{
		while(count[i] != 0)
		{
			arr[index++] = i + min;
			count[i]--;
		}
	}
}

void test()
{
	int arr[] = {5,2,9,6,1,8,7,0,4,3};
	//int arr[] = {5,2,9};
	int size = sizeof(arr)/sizeof(arr[0]);

	CountSort(arr,size);

	for(int i = 0;i < size;++i)
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