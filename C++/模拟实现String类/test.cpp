#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "Sring.h"

void Test1()
{
	String str1("hello");
	cout<<str1<<endl;
	String str2("haha");
	cout<<str2<<endl;
	String str3(str1);
	cout<<str3<<endl;
}

void Test2()
{
	String str1("hello");
	cout<<str1<<endl;
	String str2;
	str2 = str1;
	cout<<str2<<endl;
}

void Test3()
{
	String str1("hallo");
	cout<<str1<<endl;
	cout<<strlen(str1.c_str())<<endl;
	str1[1] = 'e';
	cout<<str1<<endl;
}

void Test4()
{
	String str1("hello");
	str1.PushBack('a');
	cout<<str1<<endl;
	String str2("hello");
	str2.PushBack(" world");
	cout<<str2<<endl;
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	system("pause");
	return 0;
}