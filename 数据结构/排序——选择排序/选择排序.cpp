#include<iostream>
using namespace std;

void SelectSort(int* arr,int size)
{
	//最小的放在左边，最大的放在右边
	int left = 0;
	int right = size - 1;

	while(left < right)
	{
		int min = left;
		int max = left;

		for(int i = left;i <= right;i++)
		{
			if(arr[i] < arr[min])
				min = i;
			if(arr[i] > arr[max])
				max = i;
		}

		swap(arr[left],arr[min]);

		//处理最大的数字在最左边，最小的数字在最右边的情况（图解）
		if(max == left)
		{
			max = min;
		}

		swap(arr[right],arr[max]);
		left++;
		right--;
	}
}
void test()
{
	//int arr[] = {2,5,4,9,3,6,8,7,1,0};
	int arr[] = {9,5,4,2,3,6,8,7,1,0};
	int size = sizeof(arr)/sizeof(arr[0]);

	SelectSort(arr,size);

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