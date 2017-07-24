#include <assert.h>

void* Memcpy(void* dect, const void* src, size_t size)
{
	assert(dect && src && size > 0);
	int* i_dect = (int*)dect;
	int* i_src = (int*)src;
	int count = size / sizeof(int);

	int* ret = i_dect;
	while (count--)
	{
		*i_dect = *i_src;
		i_dect++;
		i_src++;
	}
	return ret;
}

void* Memmove(void* dect, const void* src, size_t size)
{
	assert(dect && src && size > 0);

	int* i_dect = (int*)dect;
	int* i_src = (int*)src;
	int count = size / sizeof(int);

	int* ret = i_dect;
	if ((i_src+count) > i_dect)
	{
		int newcount = count;
		//从后向前拷贝，解决了内存覆盖的问题
		while (count--)
		{
			newcount--;
			*(i_dect + newcount) = *(i_src + newcount);
		}
	} 
	else
	{
		//从前向后拷贝，不存在内存覆盖的问题
		while (count--)
		{
			*i_dect = *i_src;
			i_dect++;
			i_src++;
		}
	}

	return ret;
}

void test()
{
	int arr[] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	
	Memmove(&arr[4], arr, sizeof(int)*6);	
	
	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
}