#include<iostream>
using namespace std;
#include<vector>

void test()
{
	int arr[] = {0,1,2,6,3,5,6,7,8,9,0};
	//int arr[] = {2,3,4,2,3,4,5,0,3};
	int end = 0;
	int mark_end = 0;
	int size = 1;
	int mark_size = -1;

	//[开始位置，长度]	[长度，结束位置]		[开始位置，结束位置]	三者等价
	for(int i = 1;i < sizeof(arr)/sizeof(arr[0]);++i)
	{
		if(arr[i] >= arr[end])
			++size;
		else
		{
			if(size > mark_size)
			{
				mark_end = end;
				mark_size = size;
			}
			//结束后长度重新置1，从新位置开始记录	
			size = 1;
		}

		++end;
	}
	
	//如果arr[i] > arr[end],size++后，并没有和mark_size的值比较
	if(size > mark_size)
	{
		mark_end = end;
		mark_size = size;
	}

	int index = 0;
	vector<int> tmp(mark_size);
	for(int i = mark_end - mark_size + 1;i <= mark_end;++i)
	{
		tmp[index++] = arr[i];
	}

	//打印
	for(int i = 0;i < tmp.size();++i)
	{
		cout<<tmp[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	return 0;
}