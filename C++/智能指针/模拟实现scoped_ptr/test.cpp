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
	//p2 = p; //由于赋值运算符（=）放在了保护作用域内，所以根本不可能调用它
}

int main()
{
	TestAutoPtr();
	system("pause");
	return 0;
}