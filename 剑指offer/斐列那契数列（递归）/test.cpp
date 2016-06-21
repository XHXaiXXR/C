#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

int Fibonacci(int n)
{
	if (n > 1)
	{
		return Fibonacci(n-1)+Fibonacci(n-2);
	} 
	else if (n == 1)
	{
		return 1;
	}
	else//n == 0
	{
		return 0;
	}
}

void test()
{
	int n = 0;
	cin>>n;
	int total = 0;

	for (int i = 0;i <= n;i++)
	{
		total += Fibonacci(i);
		cout<<"Fibonacci("<<i<<") = "<<Fibonacci(i)<<endl;
	}
	cout<<"total = "<<total<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}