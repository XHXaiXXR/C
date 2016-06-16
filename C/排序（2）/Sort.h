#pragma once
#include <iostream>
using namespace std;
#include <assert.h>
#include <stack>

void InsertSort(int* arr,size_t size)//ֱ�Ӳ�������
{
	assert(arr);
	for (int i = 1;i < size;i++)
	{
		int j = i-1;
		int tmp = arr[i];
		while (arr[j] > tmp && j >= 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}
}

void SellSort(int* arr,size_t size)//ϣ������
{
	assert(arr);
	int k = size;

	while (k > 1)
	{
		k = k / 3 + 1;
		for (int i = k; i < size;i ++)
		{
			int tmp = arr[i];
			int j = i - k;

			while (arr[j] > tmp && j >= 0)
			{
				arr[j + k] = arr[j];
				j -= k;
			}
			arr[j + k] = tmp;
		}
	}
}

void SelectSort(int* arr,size_t size)//ѡ������
{
	assert(arr);
	for (int i = 0;i < size;i++)
	{
		int min = i;
		for (int j = i+1;j < size;j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		//arr[i] = arr[min];//ע�⣬�����ǽ��������Ǹ�ֵ������������һ��д��д���˳���ͻ���ִ����
		swap(arr[i],arr[min]);
	}
}


void SelectSort_OP(int* arr,size_t size)//ѡ��������Ż�
{
	assert(arr);
	int left = 0;
	int right = size - 1;

	while (left < right)
	{
		int MinIndex = left;
		int MaxIndex = right;

		for (int i = left;i <= right;i++)
		{
			if (arr[i] < arr[MinIndex])
			{
				MinIndex = i;
			}
			if (arr[i] > arr[MaxIndex])
			{
				MaxIndex = i;
			}
		}

		swap(arr[left],arr[MinIndex]);
		if (MaxIndex == left)//�����������9 1 2 3 4 0�����
		{
			MaxIndex = MinIndex;
		}
		swap(arr[right],arr[MaxIndex]);
		left++;
		right--;
	}
}

int PartSort(int* arr,int left,int right)//��������
{
	assert(arr);
	int k = arr[right];
	int begin = left;
	int end = right;

	while (begin < end)
	{
		while (begin < end && arr[begin] <= k)//����Ҵ�
		{
			begin++;
		}
		while (begin < end && arr[end] >= k)//�ұ���С
		{
			end--;
		}
		if (begin < end)
		{
			swap(arr[begin],arr[end]);
		}
	}
	swap(arr[begin],arr[right]);
	return begin;
}

void QuickSort(int* arr,int left,int right)//�������򣨵ݹ�ʵ�֣�
{
	assert(arr);
	if (left >= right)
	{
		return;
	}
	int div = PartSort(arr,left,right);
	QuickSort(arr,left,div-1);
	QuickSort(arr,div+1,right);
}

void QuickSort_NonR(int* arr,int left,int right)//�������򣨷ǵݹ�ʵ�֣�
{
	assert(arr);
	stack<int> _stack;

	_stack.push(right);
	_stack.push(left);

	while (_stack.empty() == false)
	{
		int begin = _stack.top();
		_stack.pop();
		int end = _stack.top();
		_stack.pop();

		int div = PartSort(arr,begin,end);

		if (begin < div-1)
		{
			_stack.push(div-1);
			_stack.push(begin);
		}
		if (div+1 < end)
		{
			_stack.push(end);
			_stack.push(div+1);
		}
	}
}