#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

int MidNode(int* arr,int left,int right)
{
	int tmp = arr[left];

	while(left < right)
	{
		while(left < right && arr[right] >= tmp)
		{
			right--;
		}
		swap(arr[left],arr[right]);

		while(left < right && arr[left] <= tmp)
		{
			left++;
		}
		swap(arr[left],arr[right]);
	}

	return left;
}
void QuickSort(int* arr,int left,int right)
{
	if(left < right)
	{
		int mid = MidNode(arr,left,right);

		QuickSort(arr,left,mid-1);
		QuickSort(arr,mid+1,right);
	}
}
void test()
{
	int arr[] = {5,2,3,9,4,7,0,6,1,8};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	QuickSort(arr,0,size-1);

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