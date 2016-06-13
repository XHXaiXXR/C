#ifndef __6_12_h__
#define  __6_12_h__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void Replace(char* arr,int length,int size)//从后往前赋值
{
	int i = 0;
	int count = 0;
	int newlength = 0;
	int cur = 0;
	int prev = 0;
	assert(arr);
	assert(length);

	while (arr[i] != '\0')
	{
		if (arr[i] == ' ')
		{
			count++;
		}
		i++;
	}

	newlength = length + count*2;
	if (newlength > size)
	{
		return;
	}
	cur = length;
	prev = newlength;
	
	while (prev >= 0 && prev > cur)
	{
		if (arr[cur] == ' ')
		{
			arr[prev--] = '0';
			arr[prev--] = '2';
			arr[prev--] = '%';
		} 
		else
		{
			arr[prev--] = arr[cur];
		}
		cur--;
	}
}

void TwoOrderArrSort(int* arr1,int* arr2,int size1,int size2)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int NewSize1 = 0;
	int NewLength1 = 0;
	assert(arr1);
	assert(arr2);
	assert(size1);
	assert(size2);
	while (arr1[k])
	{
		NewSize1++;
		k++;
	}

	NewLength1 = NewSize1 + size2 - 1;
	i = NewSize1-1;
	j = size2-1;

	if (NewLength1 > size1-1)
	{
		return;
	}
	while (NewLength1 >= 0 && i >= 0 && j >= 0)
	{
		if (arr1[i] >= arr2[j])
		{
			arr1[NewLength1--] = arr1[i];
			i--;
		} 
		else//arr1[i] < arr2[j]
		{
			arr1[NewLength1--] = arr2[j];
			j--;
		}
	}

	while (i>0)
	{
		arr1[NewLength1--] = arr1[i--];
	} 
	while(j>0)
	{
		arr2[NewLength1--] = arr2[j--];
	}
}

#endif// __6_12_h__