#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

int main()
{
	int arr[] = {6,3,8,1,4,9,5,0,2,7};
	int size = sizeof(arr)/sizeof(arr[0]);
	BubbingSort(arr,size);
	//SelectSort(arr,size);
	//InsertSort(arr,size);
	PrintSort(arr,size);
	system("pause");
	return 0;
}