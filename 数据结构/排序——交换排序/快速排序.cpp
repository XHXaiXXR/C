#include<iostream>
using namespace std;
#include<stack>

//前后指针法
int ParkSort3(int* arr,int begin,int end)
{
	int key = arr[end];
	int cur = begin;
	int prev = begin - 1;

	while(cur < end)
	{
		if((arr[cur] < key) && (++prev != cur))
			swap(arr[cur],arr[prev]);

		++cur;
	}

	swap(arr[++prev],arr[end]);//记住每次交换前prev都要++
	return prev;
}

//三数取中法——解决时间复杂度最坏的情况（O(N^2)）
int GetMidNum(int* arr,int begin,int end)
{
	int mid = begin + (end - begin)/2;

	if(arr[begin] > arr[mid])
	{
		if(arr[end] < arr[mid])//arr[mid]是中间值
			return mid;
		else//arr[end] > arr[mid]
		{
			//此时，arr[mid]是最小的值，中间值在arr[begin],arr[end]中选择
			if(arr[end] > arr[begin])
				return begin;
			else//arr[end] < arr[begin]
				return end;
		}
	}
	else//arr[begin] < arr[mid]
	{
		if(arr[end] > arr[mid])
			return mid;
		else//arr[end] < arr[mid]
		{
			if(arr[end] > arr[begin])
				return end;
			else //arr[end] < arr[begin]
				return begin;
		}
	}
}

//挖坑法
int ParkSort2(int* arr,int begin,int end)
{

	int tmp = GetMidNum(arr,begin,end);
	swap(arr[end],arr[tmp]);
	int key = arr[end];
	
	int left = begin;
	int right = end;

	while(left < right)
	{
		while(left < right && arr[left] <= key)
			++left;

		arr[right] = arr[left];

		while(left < right && arr[right] >= key)
			--right;

		arr[left] = arr[right];
	}
	arr[left] = key;
	return left;

}

//单趟排序
int ParkSort1(int* arr,int begin,int end)
{
	int left = begin;
	int right = end - 1;

	int tmp = GetMidNum(arr,begin,end);
	swap(arr[end],arr[tmp]);
	int key = arr[end];

	while(left < right)
	{
		//left所指的值要比arr[end]（key值）大
		while(left < right && arr[left] <= key)
			++left;

		//right所指的值要比arr[end]（key值）小
		while(left < right && arr[right] >= key)
			--right;
		
		if(left < right)
			swap(arr[left],arr[right]);
	}

	//出了循环以后，此时left和right指向同一个位置，此时
	//将arr[left](arr[right])的值和arr[end](key值)交换
	if(arr[left] > key)
	{
		swap(arr[left],arr[end]);
		return left;
	}
	else 
		return end;
}
void QuickSort(int* arr,int begin,int end)
{
	if(begin >= end)
		return;

	//int div = ParkSort1(arr,begin,end);
	//int div = ParkSort2(arr,begin,end);
	int div = ParkSort3(arr,begin,end);
	
	QuickSort(arr,begin,div-1);
	QuickSort(arr,div+1,end);
}

//非递归实现快速排序
void QuickSortNonR(int* arr,int begin,int end)
{
	stack<int> s;
	s.push(end);
	s.push(begin);

	while(!s.empty())
	{
		int left = s.top();
		s.pop();

		int right = s.top();
		s.pop();

		int div = ParkSort1(arr,left,right);

		if(left < div - 1)
		{
			s.push(div-1);
			s.push(left);
		}

		if(div + 1 < right)
		{
			s.push(right);
			s.push(div+1);
		}
	}
}

void test()
{
	int arr[] = {5,2,9,0,1,8,3,6,4,7};
	//int arr[] = {5,2,9};
	int size = sizeof(arr)/sizeof(arr[0]);

	//QuickSort(arr,0,size-1);
	QuickSortNonR(arr,0,size-1);

	for(int i = 0;i < size;i++)
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