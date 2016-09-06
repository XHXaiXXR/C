#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>

//方法一（非递归）
int BinarySearchNonR(int* arr,int size,int key)
{
	assert(arr);
	int left = 0;
	int right = size-1;
	int mid  = 0;

	while (left <= right)
	{
		mid = (left + right)/2;
		if (arr[mid] > key)
		{
			right = mid - 1;
		} 
		else if (arr[mid] < key)
		{
			left = mid + 1;
		}
		else//arr[mid] == key
		{
			return mid;
		}
	}
	//找不到返回-1
	return -1;
}

//方法二（递归）
int BinarySearch(int* arr,int left,int right,int key)
{
	assert(arr);
	int mid = (left + right) / 2;
	//递归先写回溯条件
	if (arr[mid] == key)
	{
		return mid;
	}
	if (arr[mid] > key)
	{
		if (left > right)
		{
			return -1;
		}
		BinarySearch(arr,left,mid-1,key);
	} 
	else if (arr[mid] < key)
	{
		if (left > right)
		{
			return -1;
		}
		BinarySearch(arr,mid+1,right,key);
	}
}

void Test()
{
	//非递归
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	int size = sizeof(arr)/sizeof(arr[0]);
	int key = 0;
	cin>>key;
	int ret = BinarySearchNonR(arr,size,key);
	cout<<ret<<endl;

	//递归
	int arr2[] = {10,20,30,40,50,60,70,80,90,100};
	int size2 = sizeof(arr2)/sizeof(arr2[0]);
	int key2 = 0;
	cin>>key2;
	int ret2 = BinarySearch(arr2,0,size2-1,key2);
	cout<<ret2<<endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}