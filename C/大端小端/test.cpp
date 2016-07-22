#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

int CheckSys()
{
	int num = 1;
	char* p = (char*)&num;//num是int整型，p是插入类型，所以需要强制类型转换才能赋值过去

	if (*p == 1)
	{
		return 1;
	} 
	else//*p != 1
	{
		return 0;
	}
}

int CheckSys_union()
{
	union UN
	{
		int num;
		char p;
	}un;

	un.num = 1;

	if (un.p == 1)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}



int main()
{
	if (CheckSys() == 1)
	{
		cout<<"小端存储"<<endl;
	} 
	else
	{
		cout<<"大端存储"<<endl;
	}

	if (CheckSys_union() == 1)
	{
		cout<<"小端存储"<<endl;
	} 
	else
	{
		cout<<"大端存储"<<endl;
	}
	system("pause");
	return 0;
}