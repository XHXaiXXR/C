#define _CRT_SECURE_NO_WARNINGS 1

#include "Data.h"

void Test1()// 构造函数   拷贝构造函数
{
	Data d;//调用缺省的构造函数
	d.Display();
	Data d1(2016,6,2);//传参，则不适用缺省值
	d1.Display();
	Data d2;
	d2 = d; //调用拷贝构造函数；
	d2.Display();
}

void Test2()//operator=()
{
	Data d(2005,8,8);
	d.Display();
	Data d1;
	d1 = d;
	d1.Display();
}

void Test3()//operator+()  operator-()
{
	Data d(2016,6,29);
	d.Display();

	//d = d + (-2);
	//d.Display();
	
	d = d - (-3);
	d.Display();
}

void Test4()//operator++()   operator++(int)  operator--()   operator--(int)
{
	Data d(2005,1,1);
	d.Display();
	//++d;
	//d++;
	//--d;
	d--;
	d.Display();
}

void Test5()//operator-()
{
	Data d(2016,6,8);
	d.Display();
	Data d1(2014,8,18);
	d1.Display();
	int day = d-d1;
	cout<<"谢向荣和萧海霞在一起"<<day<<"天了"<<endl;
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