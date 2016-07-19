#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void InitSeqList(pSeqList pSeq)
{
	pSeq->size = 0;
	//memset(pSeq->Data,0,sizeof(DataType)*MAX);   //初始化结构体中Data的值
	memset(pSeq, 0, sizeof(pSeq)*MAX);             //初始化整个结构体
	
}
// 1、参数合法性检测
// 边界条件
// 实现逻辑
void PrintSeqList(pSeqList pSeq)
{
	int i = 0;
	for (i = 0; i < pSeq->size;i++)
	{
		printf("%d  ",pSeq->Data[i]);
	}
	printf("\n");
}
void PushBack(pSeqList pSeq,DataType x)//尾插法
{
	assert(pSeq);
	if (pSeq->size >= MAX)
	{
		printf("SeqList is full\n");
		return;
	}
	pSeq->Data[pSeq->size] = x;
	pSeq->size++;
}
void PopBack(pSeqList pSeq)//尾删法
{
	assert(pSeq);
	if (pSeq->size == 0)
	{
		printf("SeqList is empty\n");
		return;
	}
	pSeq->size--;
}
void PushFront(pSeqList pSeq,DataType x)
{
	int i = 0;
	assert(pSeq);
	if (pSeq->size >= MAX)
	{
		printf("SeqList is full\n");
		return;
	}
	else if(pSeq->size == 0)
	{
		pSeq->Data[0] = x;
		pSeq->size++;
	} 
	else
	{
		//for (i = 0;i<pSeq->size;i++)    //这是一个严重的错误，会把原来的值覆盖掉
		//{
		//	pSeq->Data[i+1] = pSeq->Data[i];
		//}

		//搬移元素
		for (i = pSeq->size;i>=0;i--)
		{
			pSeq->Data[i] = pSeq->Data[i - 1];
		}

		pSeq->Data[0] = x;
		pSeq->size++;
	}
}
void PopFront(pSeqList pSeq)
{
	int i = 0;
	assert(pSeq);
	if (pSeq->size == 0)
	{
		printf("SeqList is empty\n");
	}

	for (i = 0;i < pSeq->size;i++)
	{
		pSeq->Data[i] = pSeq->Data[i+1];
	}
	pSeq->size--;
}
int Find(pSeqList pSeq,DataType x)
{
	int i = 0;
	assert(pSeq);

	if (pSeq->size == 0)
	{
		printf("SeqList is empty\n");
		return;
	}

	for (i = 0;i < pSeq->size; i++)
	{
		if (x == pSeq->Data[i])
		{
			return i;//如果找得到x，则返回x所在下标的值
		}
	}

	return -1;//如果没有找到x，则返回一个负数
}
void Insert(pSeqList pSeq,int pos,DataType x)
{
	int i = 0;
	assert(pSeq);
	if (pSeq->size >= MAX)
	{
		printf("SeqList is full\n");
		return;
	}

	if (pos <= pSeq->size)
	{
		for (i = pSeq->size;i>pos;i--)
		{
			pSeq->Data[i] = pSeq->Data[i - 1];
		}

		pSeq->Data[pos] = x;
		pSeq->size++;
	} 
	else
	{
		printf("pos is error\n");
	}
}
void Erase(pSeqList pSeq,size_t pos)
{
	int i = 0;
	if (pSeq->size == 0 || pos > pSeq->size - 1)
	{
		return;
	}

	for (i = pos;i<pSeq->size;i++)
	{
		pSeq->Data[i] = pSeq->Data[i + 1];
	}
	pSeq->size--;
}
void Remove(pSeqList pSeq,DataType x)
{
	//调用函数方法
	int pos = 0;
	assert(pSeq);

	if (pSeq->size == 0)
	{
		printf("Seqlist is empty\n");
		return;
	}

	pos = Find(pSeq,x);
	if (pos <0)
	{
		printf("no find x\n");
		return;
	} 
	else
	{
		Erase(pSeq,pos);
	}

	//非函数调用方法
	//int i = 0;
	//assert(pSeq);
	//if (pSeq->size == 0)
	//{
	//	printf("SeqList is empty\n");
	//}

	//for (i = 0;i < pSeq->size;i++)
	//{
	//	if (pSeq->Data[i] == x)
	//	{
	//		for (;i<pSeq->size;i++)
	//		{
	//			pSeq->Data[i] = pSeq->Data[i+1];
	//		}
	//		pSeq->size--;
	//		return;
	//	}
	//} 

	//if (i == pSeq->size)
	//{
	//	printf("no find x\n");
	//	return;
	//}
}
void RemoveAll(pSeqList pSeq,DataType x)
{
	int i = 0;
	//int j = 0;
	int count = 0;
	assert(pSeq);
	if (pSeq->size == 0)
	{
		printf("SeqList is empty\n");
	}

	//方法一
	//do 
	//{
	//	j = i;
	//	if (pSeq->Data[j] == x)
	//	{
	//		for (;j<pSeq->size;j++)
	//		{
	//			pSeq->Data[j] = pSeq->Data[j+1];
	//		}
	//		pSeq->size--;
	//	} 
	//	else
	//	{
	//		i++;
	//	}
	//} while (i<pSeq->size);

	//方法二
	for (i = 0;i < pSeq->size;i++)
	{
		if (x == pSeq->Data[i])
		{
			count++;
		} 
		else
		{
			pSeq->Data[i-count] = pSeq->Data[i];
		}
	}
	pSeq->size -= count;  //有效size随着count的增加而减少
}

void SelectSort(pSeqList pSeq)   //选择排序
{
	int i = 0, j = 0;
	int iMaxPos = 0;
	int iMinPos = 0;

	DataType temp;
	for (; i < pSeq->size/2; ++i)
	{
		iMaxPos = i;
		iMinPos = i;
		for (j = 1; j < pSeq->size - i; j++)
		{
			if (pSeq->Data[iMaxPos] < pSeq->Data[j])
			{
				iMaxPos = j;
			}

			if (pSeq->Data[iMinPos] > pSeq->Data[j])
			{
				iMinPos = j;
			}
		}

		if (iMaxPos != i)
		{
			temp = pSeq->Data[iMaxPos];
			pSeq->Data[iMaxPos] = pSeq->Data[pSeq->size - i - 1];
			pSeq->Data[pSeq->size - i - 1] = temp;
		}

		if (iMinPos != i)
		{
			temp = pSeq->Data[iMinPos];
			pSeq->Data[iMinPos] = pSeq->Data[i];
			pSeq->Data[i] = temp;
		}
	}
}
void Sort(pSeqList pSeq)
{
	int tmp = 0; 
	int i = 0;
	int j = 0;
	assert(pSeq);

	for (i = 0;i < pSeq->size-1;i++)//做n-1趟排序
	{
		for (j = 0;j < pSeq->size - i -1;j++)//每次比较的个数越来越少
		{
			if (pSeq->Data[j]>pSeq->Data[j+1])
			{
				tmp = pSeq->Data[j];
				pSeq->Data[j] = pSeq->Data[j+1];
				pSeq->Data[j+1] = tmp;
			}
		}
	}
}
int BinarySearch(pSeqList pSeq,DataType x)    //二分查找
{
	int left = 0;
	int right = 0;
	int mid = 0;
	assert(pSeq);
	Sort(pSeq);

	left = 0;
	right = pSeq->size-1;

	while(left <= right)
	{
		//mid = (left+right)>>1;              //求中间值，用这两种方法写出来的代码会比较高端一些
		mid = left + (right - left)/2;    //如果mid=(left+right)/2的话，有些情况下会溢出

		if (pSeq->Data[mid] < x)
		{
			left = mid + 1;
		}
		else if (pSeq->Data[mid] > x)
		{
			right = mid - 1;
		} 
		else
		{
			return mid;
		}
	}

	return -1;
}