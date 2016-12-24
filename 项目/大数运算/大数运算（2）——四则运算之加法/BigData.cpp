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

std::string BigData::Add(std::string left,std::string right)
{
	//获取两个string的长度
	int LSize = left.size();
	int RSize = right.size();

	//保证left的长度始终不小于right的长度
	if (LSize < RSize)
	{
		std::swap(left,right);
		std::swap(LSize,RSize);
	}

	//为两个操作数相加的结果开辟一个数组，大小为最长操作数的大小加上1，多出来的一个位置是为了存放最高位相加是否进位的标志
	std::string str_result((LSize + 1),'0');
	str_result[0] = left[0];//第一个位置同样存放符号位
	//int index = RSize;//获取短的string长度作为循环的条件，并作为结果数组的下标
	int num = str_result.size() - 1;

	//从后往前将数字相加，相加结果放在结果数组里
	for(int index = 1;index < RSize;++index)
	{
		char l = left[LSize - index] - '0';							//左操作数的值
		char r = right[RSize - index] - '0';						//右操作数的值
		char carry = str_result[num] - '0';							//进位的值（进位存放在结果数组里）

		char sum = l + r + carry;							//两数和进位相加的值
		str_result[num] = (char)((int)sum % 10 + '0');		//每个位置相加后的结果
		str_result[num - 1] = (char)((int)sum / 10 + '0');	//进位
		--num;
	}

	//如果两个string一长一短，那么上面操作完成以后还有数据是没有相加的，要加剩下的高位放在结果数组中
	for (int index = num;index > 1;--index)
	{
		//还要加自己的目的是以短长度的数据加完以后，有可能有进位，进位存放在结果数组里
		str_result[index] = (str_result[index] - '0') + (left[index - 1] - '0') + '0';
	}
	return str_result;
}
std::string BigData::Sub(std::string left,std::string right)
{
	return "";
}
BigData BigData::operator+(const BigData& bigData)
{
	//两个操作数都没有超出范围
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		if (_strData[0] != bigData._strData[0])
		{
			//两个操作数异号，相加的结果一定不会超出访问
			return BigData(_value + bigData._value);
		} 
		else
		{
			//两操作数同号，结果有可能溢出
			//一下处理的是不会溢出的情况
			if ((_strData[0] == '+' && MAX_INT64 - _value >= bigData._value) ||
				(_strData[0] == '-' && MIN_INT64 - _value <= bigData._value))
			{
				return BigData(_value + bigData._value);
			}
		}
	}

	//走到这里只有可能是两种情况
	//一种是至少有一个操作数溢出
	//另外一种是两个没有溢出的操作数结果相加溢出
	if (_strData[0] == bigData._strData[0])
	{
		//同号相加
		return BigData((char*)Add(_strData,bigData._strData).c_str());
	} 
	else
	{
		//异号相加 == 同号相减
		return BigData((char*)Sub(_strData,bigData._strData).c_str());
	}
}

