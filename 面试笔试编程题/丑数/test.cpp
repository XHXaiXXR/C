#include <iostream>
using namespace std;
#include <vector>
#include <stack>

bool _UglyNum1(int n)
{
	while (n % 2 == 0)
	{
		n /= 2;
	}
	while (n % 3 == 0)
	{
		n /= 3;
	}
	while (n % 5 == 0)
	{
		n /= 5;
	}

	if (n == 1)
	{
		return true;
	} 
	else
	{
		return false;
	}
}
//第一种方法：全部遍历一遍
int UglyNum1(int n)
{
	int num = 2;
	int count = 1;//默认1为第一个丑数
	while (1)
	{
		if (_UglyNum1(num))
		{
			++count;
			if (count == n)
			{
				break;
			}
		}
		num++;
	}

	return num;
}

//第二种方法：以空间换时间
int UglyNum2(int n)
{
	int* arr = new int[n];
	memset(arr, '\0', sizeof(int)*n);
	arr[0] = 1;
	int* p2 = arr;
	int* p3 = arr;
	int* p5 = arr;

	for (int i = 1;i < n;i++)
	{
		int _min = min((*p2) * 2, min((*p3) * 3, (*p5) * 5));
		arr[i] = _min;
		while (_min >= ((*p2) * 2))
		{
			p2++;
		}
		while (_min >= ((*p3) * 3))
		{
			p3++;
		}
		while (_min >= ((*p5) * 5))
		{
			p5++;
		}
	}
	return arr[n-1];
}

void test()
{
	int n = 0;
	cin>>n;
	cout<<"第"<<n<<"个丑数 = "<<UglyNum2(n)<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}
