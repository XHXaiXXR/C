#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

//void BubbingSort(int* arr,int size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	assert(arr);
//
//	for (i = 0;i < size-1; i++)  //���������
//	{
//		for (j = 0;j < size-1-i;j++)//ÿ������ĸ���
//		{
//			if (arr[j] > arr[j+1])//����
//			{
//				tmp = arr[j];
//				arr[j] = arr[j+1];
//				arr[j+1] = tmp;
//			}
//		}
//	}
//}

//�Ż�һ�κ��ð������  �Ż�����  �Ż���������㷨���Ѿ�����Ĳ�������ֵ�����ٽ������򣬼��ٸ��Ӷ� 
//void BubbingSort(int* arr,int size)
//{
//	int i = 0;
//	int j = 0;
//	int tmp = 0;
//	int flag = 0;//���
//	assert(arr);
//
//	for (i = 0;i < size-1; i++)  //���������
//	{
//		flag = 0;
//		for (j = 0;j < size-1-i;j++)//ÿ������ĸ���
//		{
//			if (arr[j] > arr[j+1])//����
//			{
//				tmp = arr[j];
//				arr[j] = arr[j+1];
//				arr[j+1] = tmp;
//				flag = 1;//�������������ô�ͽ���Ǳ任
//			}
//		}
//		if (flag == 0)//�������һ�˵�����û���κ�һ�������ֵ��������ô�����������Ѿ�����
//		{
//			break;
//		}
//	}
//}

//�Ż����κ��ð������     �Ż�����������ıȽ�
void BubbingSort(int* arr,int size)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int flag = 0;//���
	int m = size-i-1;//��ʼ��Ϊð������Ƚϴ�������������
	int n = 0;
	assert(arr);

	for (i = 0;i < size-1; i++)  //���������
	{
		flag = 0;
		for (j = 0;j < m;j++)//ÿ������ĸ���
		{
			if (arr[j] > arr[j+1])//����
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
				flag = 1;//�������������ô�ͽ���Ǳ任
				n = j;   //��¼��ǰ��������ֵ���±�
			}
		}

		m = n; //����¼�������±�ֵ��ֵ��jѭ������������
		if (flag == 0)//�������һ�˵�����û���κ�һ�������ֵ��������ô�����������Ѿ�����
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
				min = j;//��ס��ǰ��Сֵ���±�ֵ
			}
		}
		tmp = arr[min];//�ҳ���С��ֵ���±��0��ʼ����
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

	for (i = 1;i < size;i++)//i=1��Ϊֻ��һ�������������
	{
		if(arr[i-1] > arr[i])
		{
			tmp = arr[i];  //���浱ǰ��Ҫ�����ֵ
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