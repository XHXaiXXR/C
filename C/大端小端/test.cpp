#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

int CheckSys()
{
	int num = 1;
	char* p = (char*)&num;//num��int���ͣ�p�ǲ������ͣ�������Ҫǿ������ת�����ܸ�ֵ��ȥ

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
		cout<<"С�˴洢"<<endl;
	} 
	else
	{
		cout<<"��˴洢"<<endl;
	}

	if (CheckSys_union() == 1)
	{
		cout<<"С�˴洢"<<endl;
	} 
	else
	{
		cout<<"��˴洢"<<endl;
	}
	system("pause");
	return 0;
}