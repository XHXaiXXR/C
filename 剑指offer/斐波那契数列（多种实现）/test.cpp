#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>

//����һ(�ݹ�)
int Fib(int n)
{
	assert(n >= 0);
	if (n == 1 || n == 0)
	{
		return n;
	}
	return Fib(n-1)+Fib(n-2);
}

//������(�ݹ�)   �����ݺܴ��ʱ��int�ǲ����������
long long Fib2(long long n)
{
	assert(n >= 0);
	return n < 2 ? n : Fib2(n-1)+Fib2(n-2);
}

//������(�ǵݹ� ����)
long long* FibArrayNonR(long long n)
{
	assert(n >= 0);
	long long* array = new long long[n+1];//����ע��һ��Ҫ��һ����Ϊ������0�±�
	array[0] = 0;
	array[1] = 1;

	for (long long i = 2;i <= n;i++)
	{
		array[i] = array[i-1] + array[i-2];
	}
	return array;
}

//������(�ǵݹ� ʹ����������)
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

	long long ret3 = Fib2(50);//���ϵ�ѹջ������������Ҫ�ܳ���ʱ��
	cout<<ret3<<endl;
}
void Test2()
{
	long long* arr = FibArrayNonR(50);//����Ҫ�ݹ�ѹջ��ʱ�临�Ӷ�ΪO(N),Ч�ʸ�
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