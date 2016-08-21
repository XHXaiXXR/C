#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "CountCpy.h"

void test1()
{
	String s1("hello");
	String s2(s1);
	String s3(s1);
	String s4("world");
	s2 = s4;
	s4[3] = 'd';
}
int main()
{
	test1();
	system("pause");
	return 0;
}