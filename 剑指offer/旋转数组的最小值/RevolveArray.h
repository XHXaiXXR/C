#pragma once
#include <iostream>
using namespace std;
#include <assert.h>

template<class T>
T& RevolveArray(T* arr,size_t size,size_t k)
{
	assert(arr);

	T min = arr[0];
	T tmp = 0;
	while (k--)
	{
		tmp = arr[0];
		for (int index = 1;index < size;++index)
		{
			if (min > arr[index])
			{
				min = arr[index];
			}
			arr[index - 1] = arr[index];
		}
		arr[size-1] = tmp;
	}
	return min;
}