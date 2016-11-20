#include<iostream>
using namespace std;

//向下调整
void AdjustDown(int* arr,size_t size,int parent)
{
	int child = 2 * parent + 1;

	while(child < size)
	{
		if(child + 1 < size && arr[child + 1] > arr[child])
			++child;

		if(arr[child] > arr[parent])
			swap(arr[child],arr[parent]);
		else
			break;

		parent = child;
		child = 2 * parent + 1;
	}
}

void HeapSort(int* arr,size_t size)
{
	//建堆，从第一个非叶子节点开始向下调整
	for(int i = (size-2) / 2;i >= 0; --i)
	{
		AdjustDown(arr,size,i);
	}

	//升序，每次取堆顶的数据和最后一个数据进行交换
	//再对堆顶进行向下调整
	int end = size - 1;
	while(end > 0)
	{
		swap(arr[0],arr[end]);
		
		//size的范围逐渐缩小，用end来控制size的大小
		AdjustDown(arr,end,0);

		--end;
	}
}

void test()
{
	int arr[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(arr)/sizeof(arr[0]);

	HeapSort(arr,size);

	for(int i = 0;i < size;++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	return 0;
}