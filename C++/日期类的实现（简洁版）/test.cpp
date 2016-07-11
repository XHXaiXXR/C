#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "date.h"

void Test1()//operator=  operator+
{
	Date d(2016,7,8);
	d.Display();
	Date d1;
	d1.Display();
	d1 = d;//operator=
	d1.Display();
	//d = d + 10;  //operator+
	//d.Display();
	d = d + 100;  //operator+
	d.Display();
}

void Test2()//operator-  operator++
{
	Date d(2016,7,8);
	d.Display();
	//d = d-10; // operator-
	//d.Display();
	d = d-100; // operator-
	d.Display();
	++d;//operator++
	d.Display();
	++d;//operator++
	d.Display();

	Date d1(2012,12,31);
	d1.Display();
	++d1;//operator++
	d1.Display();
}

void Test3()//operator--
{
	Date d(2016,7,11);
	d.Display();
	--d;//operator--
	d.Display();
	Date d1(2000,1,1);
	d1.Display();
	--d1;
	d1.Display();
}

void Test4()//operator==  operator!=  operator>   operator<
{
	Date d(2001,1,1);
	Date d1(2001,2,1);
	Date d2(2001,1,1);
	cout<<(d==d2)<<endl;//operator==
	cout<<(d==d1)<<endl;//operator==
	cout<<(d!=d2)<<endl;//operator!=
	cout<<(d!=d1)<<endl;//operator!=
	cout<<(d>d1)<<endl;//operator>
	cout<<(d1>d2)<<endl;//operator>
	cout<<(d<d1)<<endl;//operator<
	cout<<(d1<d2)<<endl;//operator<
}

void Test5()//operator-
{
	Date d(2016,7,11);
	Date d1(2014,8,18);
	int ret = d-d1;
	cout<<ret<<endl;
	int tmp = d1-d;
	cout<<tmp<<endl;
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