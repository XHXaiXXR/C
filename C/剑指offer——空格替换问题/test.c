#define _CRT_SECURE_NO_WARNINGS 1
#include "6_12.h"

void Test1()
{
	//��ʵ��һ�����������ַ����е�ÿ���ո��滻��%20
	//�������롰we are happy���������we%20are%20happy��
	char arr[20] ="we are happy";
	int size = sizeof(arr)/sizeof(arr[0]);
	Replace(arr,strlen(arr),size);
	printf("%s\n",arr);
}

void Test2()
{
	//���������������arr1��arr2���ڴ���arr1��ĩβ���㹻��Ŀ���ռ�����arr2��
	//��ʵ��һ����������arr2�����е����ֲ��뵽arr1�в������е�������Ȼ����
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