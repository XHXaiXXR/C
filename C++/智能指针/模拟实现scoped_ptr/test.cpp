#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "ScopedPtr.h"

void TestScopedPtr()
{
	ScopedPtr<int> p(new int);
	*p = 10;
	cout<<*p<<endl;
	
	ScopedPtr<int> p2(new int);
	//p2 = p; //���ڸ�ֵ�������=�������˱����������ڣ����Ը��������ܵ�����
}

int main()
{
	TestAutoPtr();
	system("pause");
	return 0;
}