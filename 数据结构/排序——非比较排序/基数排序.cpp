#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//求数中最大数的位数
int GetMaxDigit(int* arr,int size)
{
	int base = 10;
	int digit = 1;
	for(int i = 0;i < size;++i)
	{
		while(arr[i] >= base)
		{
			base *= 10;
			++digit;
		}
	}

	return digit;
}

void NewCountSort(int* arr,int size)
{
	int digit = GetMaxDigit(arr,size);
	int base = 1;
	int* tmp = new int[size];

	while(digit--)
	{
		vector<int> count(10);//0-9
		for(int i = 0;i < size;++i)
		{
			int num = (arr[i] / base) % 10;
			count[num]++;
		}

		vector<int> start(10);
		for(int i = 1;i < 10;++i)
			start[i] = start[i-1] + count[i-1];
		
		for(int i = 0;i < size;++i)
		{
			int num = (arr[i] / base) % 10;
			//对各个数字进行排序（快速转置的方法）
			tmp[start[num]++] = arr[i];
		}
		//拷贝数值回数组里
		for(int i = 0;i < size;++i)
		{
			arr[i] = tmp[i];
		}
		//由低位向高位排序
		base *= 10;
	}
	delete[] tmp;
}
void test()
{
	int arr[] = {4,7,2,0,9,3,6,1,8,5};
	int size = sizeof(arr)/sizeof(arr[0]);

	NewCountSort(arr,size);

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