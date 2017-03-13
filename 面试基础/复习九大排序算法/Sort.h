#pragma once
#include <vector>

//ð�������ʱ�临�Ӷȣ�1+2+3+...+(n-1)=n(n-1)/2=n^2
void BubbingSort(int* arr, int size)
{
	for (int i = 0;i < size - 1; i++)
	{
		for (int j = 0;j < size - 1 - i;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

void BubbingSortOp(int* arr,int size)
{
	bool flag = true;
	for (int i = 0;i < size - 1; i++)
	{
		flag = false;
		for (int j = 0;j < size - 1 - i;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j],arr[j+1]);
				flag = true;
			}
		}

		if (flag == false)
		{
			break;
		}
	}
}

//ѡ�������㷨ʱ�临�Ӷȣ�n^2
void SelectSort(vector<int>& arr,int size)
{
	int start = 0;
	int end = size-1;

	while (start < end)
	{
		int min = start;
		int max = end;
		for (int i = start;i <= end;i++)
		{
			if (arr[min] > arr[i])
			{
				min = i;
			}
			if (arr[max] < arr[i])
			{
				max = i;
			}
		}

		if (start == max)
		{
			swap(arr[start++],arr[min]);
			max = min;
			swap(arr[end--],arr[max]);
		} 
		else
		{
			swap(arr[start++],arr[min]);
			swap(arr[end--],arr[max]);
		}
	}
}

//ֱ�Ӳ�������ʱ�临�Ӷȣ���õ�������Ѿ�����0����������������n(n-1)/2��,����ʱ�临�ӶȻ���n^2
void InsertSort(vector<int>& arr,int size)
{
	for (int i = 1;i < size;++i)
	{
		int tmp = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > tmp)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = tmp;
	}
}

//ϣ�������ʱ�临�Ӷȣ�n^��3/2��
void ShellSort(vector<int>& arr,int size)
{
	int key = size;

	while (key > 1)
	{
		key = key/3 + 1;//����

		for (int i = key;i < size;i++)
		{
			int j = i;
			int tmp = arr[i];
			while (j - key >= 0 && arr[j - key] > tmp)
			{
				arr[j] = arr[j - key];
				j -= key;
			}
			arr[j] = tmp;
		}
	}
}

//���µ���
void HeapAdjust(vector<int>& arr,int parent,int size)
{
	int child = 2 * parent;

	while (child < size)
	{
		if ( child + 1 < size && arr[child + 1] > arr[child])
		{
			++child;
		}
		
		if (arr[parent] < arr[child])
		{
			swap(arr[parent],arr[child]);
			parent = child;
			child = 2 * parent;
		}
		else
		{
			break;
		}
	}
}
//�������ʱ��������Ҫ���ڳ�ʼ���Ѻ��ؽ���ʱ�ķ���ɸѡ�ϣ�ʱ�临�Ӷ�Ϊnlogn
void HeapSort(vector<int>& arr,int size)
{
	//����(�ӵ�һ����Ҷ�ӽڵ㿪ʼ���µ���)
	for (int i = (size - 2)/2; i >= 0;--i)
	{
		HeapAdjust(arr,i,size);
	}

	while (size > 1)
	{
		swap(arr[0],arr[size-1]);
		HeapAdjust(arr,0,--size);
	}
}

void _Merge(vector<int>& arr, vector<int>& tmp, int left, int mid, int right)
{
	int key = mid + 1;

	int index = left;
	while (left <= mid && key <= right)
	{
		if (tmp[left] < tmp[key])
		{
			arr[index++] = tmp[left++];
		} 
		else
		{
			arr[index++] = tmp[key++];
		}
	}

	while (left <= mid)
	{
		arr[index++] = tmp[left++];
	}
	while (key <= right)
	{
		arr[index++] = tmp[key++];
	}

	tmp = arr;
}
void _MSort(vector<int>& arr, vector<int>& tmp, int left, int right)
{
	if (left == right)
	{
		tmp[left] = arr[left];
	} 
	else
	{
		int mid = (left + right) / 2;

		//��ʹÿ����������
		_MSort(arr, tmp, left, mid);
		_MSort(arr, tmp, mid + 1, right);

		//���������������ϲ�����
		_Merge(arr, tmp, left, mid, right);
	}
}

//�鲢������Ҫ�����������������еļ�¼ɨ��һ�Σ��������nʱ��
//������ȫ����������ȿ�֪�������鲢������Ҫ����logn��
//���Թ鲢�����ʱ�临�Ӷ�Ϊnlogn
void MergeSort(vector<int>& arr,int size)
{
	vector<int> tmp(size);
	_MSort(arr, tmp,0, size-1);
}

//����ȡ�з�
void _ThreeNumGetMid(vector<int>& arr,int left, int right)
{
	int midnum = (left + right) / 2;
	int mid = 0;

	if (arr[left] < arr[midnum])
	{
		if (arr[midnum] < arr[right])
		{
			mid = midnum;
		} 
		else
		{
			if (arr[left] < arr[right])
			{
				mid = right;
			} 
			else
			{
				mid = left;
			}
		}
	}
	else
	{
		if (arr[left] < arr[right])
		{
			mid = left;
		} 
		else
		{
			if (arr[midnum] < arr[left])
			{
				mid = left;
			}
			else
			{
				mid = midnum;
			}
		}
	}
	swap(arr[mid],arr[left]);
}

int _GetMid(vector<int>& arr, int left, int right)
{
	_ThreeNumGetMid(arr,left,right);
	int index = left;
	int key = arr[index];

	while (left < right)
	{
		//�ұ��ұ�keyֵС����
		while (left < right && arr[right] >= key)
		{
			right--;
		}

		//����ұ�keyֵ�����
		while (left < right && arr[left] <= key)
		{
			left++;
		}

		swap(arr[left],arr[right]);
	}
	swap(arr[index],arr[left]);

	return left;
}

void _QSort(vector<int>& arr, int left, int right)
{
	if (left >= right)
	{
		return;
	} 
	else
	{
		int mid = _GetMid(arr, left, right);

		_QSort(arr, left, mid-1);
		_QSort(arr, mid+1, right);
	}
}

//��������
void QuickSort(vector<int>& arr, int size)
{
	_QSort(arr, 0, size-1);
}












