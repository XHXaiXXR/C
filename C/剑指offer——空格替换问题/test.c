#define _CRT_SECURE_NO_WARNINGS 1
#include "6_12.h"

void Test1()
{
	//请实现一个函数，把字符串中的每个空格替换成%20
	//例如输入“we are happy”，输出“we%20are%20happy”
	char arr[20] ="we are happy";
	int size = sizeof(arr)/sizeof(arr[0]);
	Replace(arr,strlen(arr),size);
	printf("%s\n",arr);
}

void Test2()
{
	//有两个排序的数组arr1和arr2，内存在arr1的末尾有足够多的空余空间容纳arr2，
	//请实现一个函数，把arr2中所有的数字插入到arr1中并且所有的数字任然有序
	int i = 0;
	int arr1[20] = {1,2,3,5,7,9};
	int arr2[] = {2,4,6,8,9,10};
	int size1 = sizeof(arr1)/sizeof(arr1[0]);
	int size2 = sizeof(arr2)/sizeof(arr2[0]);
	TwoOrderArrSort(arr1,arr2,size1,size2);

	for (i = 0;i < size1; i++)
	{
		printf("%d ",arr1[i]);
	}
	printf("\n");
}

int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}