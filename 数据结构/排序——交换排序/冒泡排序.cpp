#include<iostream>
using namespace std;

void BubbleSort(int* arr,size_t size)
{
	for(int i = 0;i < size - 1;i++)//趟数
	{
		bool flag = false;
		for(int j = 0;j < size - 1 - i;j++)//比较个数
		{
			if(arr[j + 1] < arr[j])
			{
				swap(arr[j+1],arr[j]);
				flag = true;
			}
		}

		if(flag == false)
			break;
	}
}
void test()
{
	int arr[] = {2,6,4,9,0,1,7,3,8,5};
	int size = sizeof(arr)/sizeof(arr[0]);

	BubbleSort(arr,size);

	for(int i = 0;i < size;i++)
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