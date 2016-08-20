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
	cout<<str2.Size()<<endl;
	cout<<str2.Capacity()<<endl;
}
void Test5()
{
	String s1("hello");
	String s2("who");
	s1.Insert(3,s2);
	cout<<s1<<endl;
	cout<<s1.Size()<<endl;
	String s3("abcdefghi");
	s3.Erase(2,3);
	cout<<s3<<endl;
	cout<<s3.Size()<<endl;
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	system("pause");
	return 0;
}