#define _CRT_SECURE_NO_WARNINGS 1
#include "BigData.h"
#include <iostream>
using namespace std;

BigData::BigData(const INT64 value)
	:_value(value)
{}

BigData::BigData(const char* str)
{
	//1、纯数字	
	//12452435	5676573

	//2、开头以非法字符开头
	//hdf328498	8938293

	//3、开头是0开始
	//00002134	0003234

	//4、正负符号开头的数字
	//+78748923	-897489234

	char symbol = *str;	//获取是以什么开头的
	char* strtmp = (char*)str;	

	if (symbol == '+' || symbol == '-')
	{
		//将第4种情况和第1种情况并成第1种情况
		++strtmp;
	}
	else if (symbol >= '0' && symbol <= '9')
	{
		//如果是纯数字，那么就带上一个正数的符号‘+’
		symbol = '+';
	}
	else
	{
		//处理第二种符号，以非法字符开头的数字,剔除
		_value = UN_INT64;
		return;
	}

	while (*strtmp == '0')
	{
		//跳过前置的0，变成纯整数，第3种情况和第1种情况相并成第1种情况
		++strtmp;
	}

	//为_strData开辟空间
	_strData.resize(strlen(strtmp) + 1);	//+1的目的是为了给_strData[0]放一个符号位
	_strData[0] = symbol;	//把之前的操作过程得到的符号位放进去
	_value = 0;	//给_vulue初始值，方便后边的运算
	int index = 1;	//由于_strData[0]放了符号位，其他的数字需要从1下标开始存放

	//存放数据，同时当数据中间是非法字符时同时处理
	while (*strtmp >= '0' && *strtmp <= '9')
	{
		_value = _value * 10 + *strtmp - '0';
		_strData[index++] = *strtmp;
		++strtmp;
	}

	//由于以上操作，_value是以整数形式存放的,所以一下操作处理这个情况
	if (symbol == '-')
	{
		_value = 0 - _value;	//_value = (-1) * _value
	}

	//如果数据中间是非法字符，那么从第一个非法字符以后都不需要存放到_staData中了，那么之前开辟的空间就多余浪费了
	_strData.resize(index);
}

bool BigData::_IsINT64OverFlow()const
{
	std::string str = "+9223372036854775807";// long long 数据类型正整数的最大值

	if (_strData[0] == '-')
	{
		str = "-9223372036854775808";//long long 数据类型负整数的最小值
	}

	if (_strData.size() < str.size())
	{
		//_strData的长度都小于str的长度，数值一定不会超过
		return false;
	}
	else if (_strData.size() == str.size()&& _strData <= str)
	{
		return false;
	}

	//以上两种情况都不满足，那么就溢出
	return true;
}

std::ostream& operator<<(std::ostream& _cout,const BigData& bigData)
{
	if (!bigData._IsINT64OverFlow())
	{
		//没有溢出的话，_value保存的数值，就是数据的值
		_cout<<bigData._value;
	} 
	else
	{
		//溢出的话，_strData数组中保存的是数据的值
		char* strtmp = (char*)bigData._strData.c_str();
		if (*strtmp == '+')
		{
			//如果是正整数，符号位不需要输出
			++strtmp;
		}

		_cout<<strtmp;
	}

	return _cout;
}