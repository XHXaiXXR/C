#pragma once
#include <vector>

//冒泡排序的时间复杂度：1+2+3+...+(n-1)=n(n-1)/2=n^2
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

//选择排序算法时间复杂度：n^2
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

//直接插入排序时间复杂度：最好的情况是已经有序（0），最坏的情况是逆序（n(n-1)/2）,所以时间复杂度还是n^2
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

//希尔排序的时间复杂度：n^（3/2）
void ShellSort(vector<int>& arr,int size)
{
	int key = size;

	while (key > 1)
	{
		key = key/3 + 1;//增量

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

//向下调整
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
//堆排序的时间消耗主要是在初始建堆和重建堆时的反复筛选上，时间复杂度为nlogn
void HeapSort(vector<int>& arr,int size)
{
	//建堆(从第一个非叶子节点开始向下调整)
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

		//先使每段区间有序
		_MSort(arr, tmp, left, mid);
		_MSort(arr, tmp, mid + 1, right);

		//将两段有序的区间合并排序
		_Merge(arr, tmp, left, mid, right);
	}
}

//归并排序需要将待排序序列中所有的记录扫描一次，因此消耗n时间
//又由完全二叉树的深度可知，整个归并排序需要进行logn次
//所以归并排序的时间复杂度为nlogn
void MergeSort(vector<int>& arr,int size)
{
	vector<int> tmp(size);
	_MSort(arr, tmp,0, size-1);
}

//三数取中法
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
		//右边找比key值小的数
		while (left < right && arr[right] >= key)
		{
			right--;
		}

		//左边找比key值大的数
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

//快速排序
void QuickSort(vector<int>& arr, int size)
{
	_QSort(arr, 0, size-1);
}












