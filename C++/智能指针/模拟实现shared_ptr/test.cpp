#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "SharedPtr.h"

void TestSharePtr()
{
	SharedPtr<int> sp1(new int);
	SharedPtr<int> sp2(new int);
	SharedPtr<int> sp3(sp2);
	SharedPtr<int> sp4 = sp2;
}

int main()
{
	TestSharePtr();
	system("pause");
	return 0;
}
