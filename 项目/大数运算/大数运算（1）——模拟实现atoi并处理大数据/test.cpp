#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include "BigData.h"

void TestAtoi()
{
	cout<<atoi("1234567890")<<endl;	//合法，照常输出	
	cout<<atoi("+878923743")<<endl;	//有符号，正符号前面不需要加符号
	cout<<atoi("-328748923")<<endl;	//有符号，负符号前面需要加上符号“-”
	cout<<atoi("aaa3878944")<<endl;	//非法字符在开头，输出0
	cout<<atoi("12238dhhd3")<<endl;	//非法字符在中间，只输出第一个非法字符前面的所有数字
	cout<<atoi("0000323423")<<endl;	//前置的零可忽略不记，第一个非零数字开始
	cout<<atoi("000aa89898")<<endl;	//前置0和非法字符的情况
	cout<<atoi("000387ss33")<<endl;	//前置0和数字和非法字符的情况
}

void TestBigDataLikeAtoi()
{
	BigData b1("1234567890");
	BigData b2("+878923743");
	BigData b3("-328748923");
	BigData b4("aaa3878944");
	BigData b5("12238dhhd3");
	BigData b6("0000323423");
	BigData b7("000aa89898");
	BigData b8("000387ss33");
	BigData b9("+0000323423342345646576678768564564534534234234");
	BigData b10("-0564560087880989890645342343254546546567773423");

	cout<<b1<<endl;
	cout<<b2<<endl;
	cout<<b3<<endl;
	cout<<b4<<endl;
	cout<<b5<<endl;
	cout<<b6<<endl;
	cout<<b7<<endl;
	cout<<b8<<endl;
	cout<<b9<<endl;
	cout<<b10<<endl;
}
int main()
{
	//TestAtoi();
	TestBigDataLikeAtoi();
	system("pause");
	return 0;
}