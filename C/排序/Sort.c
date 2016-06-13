#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

//void BubbingSort(int* arr,int size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	assert(arr);
//
//	for (i = 0;i < size-1; i++)  //排序的趟数
//	{
//		for (j = 0;j < size-1-i;j++)//每次排序的个数
//		{
//			if (arr[j] > arr[j+1])//升序
//			{
//				tmp = arr[j];
//				arr[j] = arr[j+1];
//				arr[j+1] = tmp;
//			}
//		}
//	}
//}

//优化一次后的冒泡排序  优化趟数  优化后的排序算法对已经有序的部分数组值将不再进行排序，减少复杂度 
//void BubbingSort(int* arr,int size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	int flag = 0;//标记
//	assert(arr);
//
//	for (i = 0;i < size-1; i++)  //排序的趟数
//	{
//		flag = 0;
//		for (j = 0;j < size-1-i;j++)//每次排序的个数
//		{
//			if (arr[j] > arr[j+1])//升序
//			{
//				tmp = arr[j];
//				arr[j] = arr[j+1];
//				arr[j+1] = tmp;
//				flag = 1;//如果交换过了那么就将标记变换
//			}
//		}
//		if (flag == 0)//如果经过一趟的排序，没有任何一个数组的值交换，那么表明数组中已经有序
//		{
//			break;
//		}
//	}
//}

//优化两次后的冒泡排序     优化趟数里次数的比较
void BubbingSort(int* arr,int size)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int flag = 0;//标记
	int m = size-i-1;//初始化为冒泡排序比较次数的限制条件
	int n = 0;
	assert(arr);

	for (i = 0;i < size-1; i++)  //排序的趟数
	{
		flag = 0;
		for (j = 0;j < m;j++)//每次排序的个数
		{
			if (arr[j] > arr[j+1])//升序
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
				flag = 1;//如果交换过了那么就将标记变换
				n = j;   //记录当前交换了数值的下标
			}
		}

		m = n; //将记录下来的下标值赋值给j循环的限制条件
		if (flag == 0)//如果经过一趟的排序，没有任何一个数组的值交换，那么表明数组中已经有序
		{
			break;
		}
	}
}

void SelectSort(int* arr,int size)
{
	int i = 0;
	int j = 0;
	int min = 0;
	int tmp = 0;
	assert(arr);

	for (i = 0;i < size;i++)
	{
		min = i;
		for (j = i+1;j < size;j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;//记住当前最小值的下标值
			}
		}
		tmp = arr[min];//找出最小的值，下标从0开始交换
		arr[min] = arr[i];
		arr[i] = tmp;
	}
}

void InsertSort(int* arr,int size)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	assert(arr);

	for (i = 1;i < size;i++)//i=1认为只有一个数字是有序的
	{
		if(arr[i-1] > arr[i])
		{
			tmp = arr[i];  //保存当前需要排序的值
			for (j = i; j>0 && arr[j-1] > tmp;j--)
			{
				arr[j] = arr[j-1];
			}
			arr[j] = tmp;
		}
	}
}

void PrintSort(int* arr,int size)
{
	int i = 0;
	assert(arr);
	
	for (i = 0;i < size;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}