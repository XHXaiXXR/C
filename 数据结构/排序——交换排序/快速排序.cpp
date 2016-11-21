#include<iostream>
using namespace std;
#include<stack>

//ǰ��ָ�뷨
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

	swap(arr[++prev],arr[end]);//��סÿ�ν���ǰprev��Ҫ++
	return prev;
}

//����ȡ�з��������ʱ�临�Ӷ���������O(N^2)��
int GetMidNum(int* arr,int begin,int end)
{
	int mid = begin + (end - begin)/2;

	if(arr[begin] > arr[mid])
	{
		if(arr[end] < arr[mid])//arr[mid]���м�ֵ
			return mid;
		else//arr[end] > arr[mid]
		{
			//��ʱ��arr[mid]����С��ֵ���м�ֵ��arr[begin],arr[end]��ѡ��
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

//�ڿӷ�
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

//��������
int ParkSort1(int* arr,int begin,int end)
{
	int left = begin;
	int right = end - 1;

	int tmp = GetMidNum(arr,begin,end);
	swap(arr[end],arr[tmp]);
	int key = arr[end];

	while(left < right)
	{
		//left��ָ��ֵҪ��arr[end]��keyֵ����
		while(left < right && arr[left] <= key)
			++left;

		//right��ָ��ֵҪ��arr[end]��keyֵ��С
		while(left < right && arr[right] >= key)
			--right;
		
		if(left < right)
			swap(arr[left],arr[right]);
	}

	//����ѭ���Ժ󣬴�ʱleft��rightָ��ͬһ��λ�ã���ʱ
	//��arr[left](arr[right])��ֵ��arr[end](keyֵ)����
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

//�ǵݹ�ʵ�ֿ�������
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