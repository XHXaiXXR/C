#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>

//方法一(递归)
int Fib(int n)
{
	assert(n >= 0);
	if (n == 1 || n == 0)
	{
		return n;
	}
	return Fib(n-1)+Fib(n-2);
}

//方法二(递归)   当数据很大的时候，int是不满足需求的
long long Fib2(long long n)
{
	assert(n >= 0);
	return n < 2 ? n : Fib2(n-1)+Fib2(n-2);
}

//方法三(非递归 数组)
long long* FibArrayNonR(long long n)
{
	assert(n >= 0);
	long long* array = new long long[n+1];//这里注意一定要加一，因为数组有0下标
	array[0] = 0;
	array[1] = 1;

	for (long long i = 2;i <= n;i++)
	{
		array[i] = array[i-1] + array[i-2];
	}
	return array;
}

//方法四(非递归 使用两个变量)
long long FibNonR(long long n)
{
	assert(n >= 0);
	long long ret = 0;
	long long first = 0;
	long long second = 1;
	for (long long i = 1;i < n;i++)
	{
		ret = first + second;
		first = second;
		second = ret;
	}
	return ret;
}
void Test()
{
	int ret1 = Fib(10);
	cout<<ret1<<endl;

	long long ret2 = Fib2(10);
	cout<<ret2<<endl;

	long long ret3 = Fib2(50);//不断的压栈，计算出结果需要很长的时间
	cout<<ret3<<endl;
}
void Test2()
{
	long long* arr = FibArrayNonR(50);//不需要递归压栈，时间复杂度为O(N),效率高
	cout<<arr[50]<<endl;

	long long ret = FibNonR(50);
	cout<<ret<<endl;
}
int main()
{
	//Test();
	Test2();
	system("pause");
	return 0;
}