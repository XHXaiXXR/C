#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

int OneCount(unsigned int num)
{
	size_t count = 0;
	int ret = 0;
	for (int i = 0;i < 32;i++)
	{
		ret = num % 2;
		if (ret == 1)
		{
			count++;
		}
		num = num>>1;
	}
	return count;
}

void test()
{
	//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。 
	unsigned int num = 0;
	cin>>num;
	size_t count = OneCount(num);
	cout<<num<<endl<<count<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}