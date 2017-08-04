#include <iostream>
using namespace std;
#include <vector>
#include <stack>

//第一种方法：利用单趟排序，每次确定一段区间的中间值
int FindMid1(int* v, int left, int right)
{
	int key = v[left];//找一个基准值
	int newleft = left;

	while (left < right)
	{
		//升序：右边找小
		while (left < right && v[right] >= key)
		{
			right--;
		}
		//升序：左边找大
		while (left < right &&  v[left] <= key)
		{
			left++;
		}
		swap(v[left], v[right]);
	}

	swap(v[newleft], v[left]);
	return left;//left == rhght
}
void QuickSort1(int* v, int left, int right)
{
	if (left < right)
	{
		int mid = FindMid1(v, left, right);
		QuickSort1(v, 0, mid-1);
		QuickSort1(v, mid+1, right);
	}
}

//第二种方法：挖坑法
int FindMid2(int* v, int left, int right)
{
	int key = v[left];
	int newleft = left;

	while (left < right)
	{
		while (left < right && v[right] >= key)
		{
			right--;
		}
		if (left < right)
		{
			v[left] = v[right];
		}
		while (left < right && v[left] <= key)
		{
			left++;
		}
		if (left < right)
		{
			v[right] = v[left];
		}
	}
	v[left] = key;
	return left;
}
void QuickSort2(int* v, int left, int right)
{
	if (left < right)
	{
		int mid = FindMid2(v, left, right);
		QuickSort2(v, 0, mid-1);
		QuickSort2(v, mid+1, right);
	}
}

//第二种方法：前后指针法
int FindMid3(int* v, int left, int right)
{
	int end = right;
	int prev = left-1;
	int cur = left;

	while (cur < end)
	{
		if (v[cur] < v[end])
		{
			++prev;
			if(prev != cur)
			{
				swap(v[prev], v[cur]);
			}
		}
		//cur找比基准值小的数
		++cur;
	}
	swap(v[++prev], v[end]);
	return prev;
}
void QuickSort3(int* v, int left, int right)
{
	if (left < right)
	{
		int mid = FindMid3(v, left, right);
		QuickSort3(v, 0, mid-1);
		QuickSort3(v, mid+1, right);
	}
}
//利用栈来实现快速排序
void QuickSort4(int* v, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	stack<int> s;
	s.push(left);
	s.push(right);

	while (!s.empty())
	{
		int newright = s.top();
		s.pop();
		int newleft = s.top();
		s.pop();
		int mid = FindMid3(v, newleft, newright);

		if (newleft < mid-1)
		{
			s.push(newleft);
			s.push(mid-1);
		}
		if (mid+1 < right)
		{
			s.push(mid+1);
			s.push(newright);
		}
	}
}
void test()
{
	//int arr[] = {5,7,2,9,3,7,6,1,0,8,4};
	int arr[] = {5,7,2,9,3,7,6,1,0,8,4};
	int size = sizeof(arr)/sizeof(arr[0]);
	//QuickSort1(arr, 0, size-1);
	//QuickSort2(arr, 0, size-1);
	//QuickSort3(arr, 0, size-1);
	QuickSort4(arr, 0, size-1);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}