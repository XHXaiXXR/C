#define _CRT_SECURE_NO_WARNINGS 1
#include "BigData.h"
#include <iostream>
using namespace std;
#include <assert.h>
#include <sstream>

BigData::BigData(const INT64 value)
	:_value(value)
{}
BigData::BigData(const char* str)
{
	//1、纯数字	12452435	5676573
	//2、开头以非法字符开头 hdf328498	8938293
	//3、开头是0开始  00002134	0003234
	//4、正负符号开头的数字  +78748923	-897489234

	char symbol = *str;	//获取是以什么开头的
	char* strtmp = (char*)str;	

	if (symbol == '+' || symbol == '-')
	{
		//将第四种情况归并为第一种情况
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

	//如果数据中间是非法字符，那么从第一个非法字符以后都不需要存放到_staData中了，那么之前开辟的空间就多余浪费了，我们需要处理这样的情况
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
//同号相加的加法（带符号）
std::string BigData::_Add(std::string left,std::string right)
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
//同号相减的减法（带符号）
std::string BigData::_Sub(std::string left,std::string right)
{
	char symbol = '+';
	//确定结果的正负
	//左操作数和右操作数比较大小，无论正负，都是左操作数大于有操作数相减得到的结果都为正
	//（正-正）有两种情况,((10)-(8) --> l > r --> "+")	((8)-(10) --> l < r --> '-')
	//（负-负）也有两种情况，((-8)-(-10) --> l > r --> '+')	((-10)-(-8) --> l < r --> '-')
	//所以无论同正还是同负，只要l > r，那么结果的符号确定为 ‘+’，反之，为‘-’
	if (_Compare(left,right) < 0)
	{
		symbol = '-';
	} 

	//确定减法的左右操作数
	if (left[0] == '+')
	{
		//确保当两个操作数都是正数时：较大的数为左操作数
		if (_Compare(left,right) < 0)
		{
			std::swap(left,right);
		}
	}
	else	//left[0] == '-'
	{
		//确保当两个操作数都是负数时：较小的数为右操作数
		if (_Compare(left,right) > 0)
		{
			std::swap(left,right);
		}
	}

	std::string str_result(left.size(),'0');//左操作数的长度开开辟一块新的空间

	//用较小操作数的长度作为循环的条件
	int index = left.size() - 1;
	for (size_t i = 1;i < right.size();++i)
	{
		int lnum = (left[left.size() - i] - '0') + 10;	//考虑到不够减的情况，所以都首先向上一位借位
		str_result[index - 1] = '1';			//由于上一条语句的借位，结果的上一位必须要有标记
		int rnum = right[right.size() - i] - '0';			//肯定是一个不大于10的数字

		int result = lnum - rnum - (str_result[index] - '0');			//做减法,记得也要把借位给减去
		str_result[index] = (result % 10) + '0';//把数据放在结果里

		//说明没有借位，需要将前面str_result[i - 1]修改为没有借位
		if (result / 10 != 0)
		{
			str_result[index - 1] = '0';
		}
		--index;
	}
	//左右操作数长度不同时，出以后循环以后剩下的位要依次放进string当中
	for (int i = left.size() - right.size();i > 0;--i)
	{
		str_result[i] = (left[i] - '0') - (str_result[i] - '0') + '0';
	}

	str_result[0] = symbol;		//在前面先求出的结果符号先赋值过去

	return str_result;
}
//带符号的字符串比较大小
//整数比较大小  left > right (返回1)  left < right （返回-1） left == right （返回0）
int BigData::_Compare(std::string left,std::string right)
{
	//异号
	if (left[0] != right[0])
	{
		//如果两个操作数的符号不同，那么正数肯定大于负数
		if (left[0] == '+')
		{
			return 1;
		} 
		else	//left[0] == '-'
		{
			return -1;
		}
	} 
	//同号
	else
	{
		int leftSize = left.size();
		int rightSize = right.size();

		if (leftSize != rightSize)
		{
			//用长度来比较大小
			if (left[0] == '+')
			{
				if (leftSize > rightSize)
				{
					return 1;
				} 
				else
				{
					return -1;
				}
			}
			else	//left[0] == '-'
			{
				if (leftSize > rightSize)
				{
					return -1;
				} 
				else
				{
					return 1;
				}
			}
		} 
		else	//leftSize == rightSize
		{
			char symbol = left[0];

			//除去符号位，剩下的子字符串
			std::string Lstr = left.substr(1,(leftSize - 1));	//第一个参数代表着开始的位置，第二个参数代表着长度
			std::string Rstr = right.substr(1,(rightSize - 1));	//第一个参数代表着开始的位置，第二个参数代表着长度

			if (symbol == '+')
			{
				return Lstr.compare(Rstr);
			} 
			else	//symbol == '+'
			{
				return -(Lstr.compare(Rstr));
			}
		}
	}
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
			//以下处理的是不会溢出的情况
			if ((_strData[0] == '+' && (MAX_INT64 - _value) >= bigData._value) ||
				(_strData[0] == '-' && (MIN_INT64 - _value) <= bigData._value))
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
		return BigData((char*)_Add(_strData,bigData._strData).c_str());
	} 
	else	//异号
	{
		//异号相加 == 同号相减
		if (_strData[0] == '+')
		{
			//正 + 负 = 正 - 正 -------- 将右操作数符号由负变成正
			(char) bigData._strData[0] = '+';
		} 
		else	//_strData[0] == '-'
		{
			//负 + 正 = 负 - 负 ----------- 将右操作数符号由正变成负
			(char)bigData._strData[0] = '-';
		}
		return BigData((char*)_Sub(_strData,bigData._strData).c_str());
	}
}
BigData BigData::operator-(const BigData& bigData)
{
	//左右操作数都没有溢出
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		//同号相减一定不会溢出
		if (_strData[0] == bigData._strData[0])
		{
			return BigData(_value - bigData._value);
		} 
		//异号相减有可能溢出或者不溢出
		else
		{
			//以下是异号不溢出的情况
			//正 - 负	负 - 正
			if ((_strData[0] == '+' && (MAX_INT64 + bigData._value) >= _value) || 
				(_strData[0] == '-' && (MIN_INT64 + bigData._value) <= _value))
			{
				return BigData(_value - bigData._value);
			}
		}
	}

	//当走到这里时，一定是这两种情况：
	//（1）操作数至少有一个已经溢出
	//（2）两个没有溢出的操作数结果相减结果溢出
	if (_strData[0] != bigData._strData[0])
	{
		//两个操作数异号，有可能是（正 - 负），也有可能是（负 - 正）的情况
		if (_strData[0] == '+')
		{
			//左操作数是正数，右操作数是负数
			//正 - 负 = 正 + 正 ------将右操作数转成正整数，调用_Add()函数
			(char)bigData._strData[0] = '+';//因为bigData是const对象，所以要强转成（char）才可以修改它的符号位
		}
		else	//_strData[0] == '-'
		{
			//左操作数是负数，右操作数是正数
			//负 - 正 = 负 + 负 -------- 将右操作数转成负数
			(char)bigData._strData[0] = '-';			
		}
		return BigData((char*)_Add(_strData,bigData._strData).c_str());
	}

	//同号相减调用_Sub函数
	return BigData((char*)_Sub(_strData,bigData._strData).c_str());
}
std::string BigData::_Mul(std::string left,std::string right)
{
	int LSize = left.size();
	int RSize = right.size();
	int longth = LSize + RSize + 1;

	std::string str_result(longth,'0');

	//用右操作数作为循环的条件
	for (int i = 1;i <= RSize;++i)
	{
		//进位标志
		int carry = 0;
		std::string sum(longth,'0');

		int index = 1;
		int sumindex = i;
		while(index <= LSize)
		{
			int lnum = left[LSize - index] - '0';
			int rnum = right[RSize - i] - '0';
			int num = lnum * rnum + carry;

			carry = num / 10;
			sum[longth - sumindex] = (num % 10) + '0';
			++index;
			++sumindex;
		}

		//循环出来以后还有一个进位没有写进结果里
		sum[longth - sumindex] = carry + '0';

		//将每次得到新的值与上次的总结果相加
		str_result = _Add(sum,str_result);
	}
	return str_result;
}
BigData BigData::operator*(const BigData& bigData)
{
	int LSize = _strData.size();
	int RSize = bigData._strData.size();

	//不考虑符号位，获取左右操作数的子字符串
	std::string leftstr = _strData.substr(1,(LSize - 1));
	std::string rightstr = bigData._strData.substr(1,(RSize - 1));
	
	std::string str_result = _Mul(leftstr,rightstr);
	if (_strData[0] == bigData._strData[0])
	{
		//同号相乘为正数
		str_result[0] = '+';
	} 
	else
	{
		//异号相乘为负数
		str_result[0] = '-';
	}
	return BigData((char*)str_result.c_str());
}
//纯数字减法，无符号，且左操作数大于右操作数
std::string BigData::_UnsignSub(std::string left,std::string right)
{
	std::string str_result(left.size() + 1,'0');//左操作数的长度开开辟一块新的空间
	int index = left.size();

	//用较小操作数的长度作为循环的条件
	for (size_t i = 0;i < right.size();++i)
	{
		int lnum = (left[left.size() - 1 - i] - '0') + 10;	//考虑到不够减的情况，所以都首先向上一位借位
		str_result[index - 1] = '1';			//由于上一条语句的借位，结果的上一位必须要有标记
		int rnum = right[right.size() - 1 - i] - '0';			//肯定是一个不大于10的数字

		int result = lnum - rnum - (str_result[index] - '0');			//做减法,记得也要把借位给减去
		str_result[index] = (result % 10) + '0';//把数据放在结果里

		//说明没有借位，需要将前面str_result[i - 1]修改为没有借位
		if (result / 10 != 0)
		{
			str_result[index - 1] = '0';
		}
		--index;
	}
	//左右操作数长度不同时，出以后循环以后剩下的位要依次放进string当中
	for (int i = left.size() - right.size() - 1;i >= 0;--i)
	{
		str_result[index] = (left[i] - '0') - (str_result[index] - '0') + '0';
		--index;
	}

	return str_result;
}
std::string BigData::_Div(std::string left,std::string right)
{
	int longht = left.size() > right.size() ? left.size() : right.size();
	std::string str_result(longht,'0');

	//跳过符号位取新的左右操作数
	std::string Left = left.substr(1,right.size() - 1);
	std::string Right = right.substr(1,right.size() - 1);
	//结果从第几位开始写入
	int i = right.size() - 1;

	//取相同长度的左操作数和右操作数，如果左操作数小于右操作数（不够除），那么左操作数需要多一位
	if (strcmp(Left.c_str(),Right.c_str()) == -1)
	{
		Right = right.substr(1,right.size());
		i = left.size();
	}

	while(i < longht)
	{
		int num = 10;
		while (num--)
		{
			stringstream ss;
			//将数字转成字符串，便于两存放数字的字符串相乘的计算
			ss<<num;
			int count = 0;//记录sum前置0的个数

			//sum = num * Right 的结果
			std::string sum = _Mul(Right,ss.str());
			for (int j = 0;j < sum.size();++j)
			{
				if (sum[j] == '0')
					count++;
				else
					break;
			}
			sum = sum.substr(count,sum.size() - count);//跳过sum前置的0
			//num是要放进结果数组的值，每次让num*右操作数，如果它相乘出来的结果小于左操作数了，那么这时候的num就是正确的值
			if ((sum.size() < Left.size())||
				(sum.size() == Left.size()) &&
				(strcmp(sum.c_str(),Left.c_str()) == -1) ||
				(sum.size() == Left.size()) &&
				(strcmp(sum.c_str(),Left.c_str()) == 0))
			{
				break;
			}
		}
		//计算出num的数值，并保存起来
		str_result[i] = num + '0';
		stringstream ss1;
		//将数字转成字符串，便于两数相乘的计算
		ss1<<num;
		int count = 0;//记录sum前置0的个数
		std::string sum = _Mul(Right,ss1.str());
		for (int j = 0;j < sum.size();++j)
		{
			if (sum[j] == '0')
				count++;
			else
				break;
		}
		sum = sum.substr(count,sum.size() - count);//跳过sum前置的0
		//计算并保存num * 右操作数的值与左操作数的差值，新的左操作数 = 差值*10 + 原左操作数【i+1】
		Left = _UnsignSub(Left,sum);
		//防止越界访问
		if (i + 1 < left.size())
		{
			Left.push_back(left[i+1]);
		}
		count = 0;
		for (int j = 0;j < Left.size();++j)
		{
			if (Left[j] == '0')
				count++;
			else
				break;
		}
		Left = Left.substr(count,Left.size() - count);
		++i;
	}
	return str_result;
}
BigData BigData::operator/(const BigData& bigData)
{
	//除数不能为0（右操作数不能为0）
	if (!bigData._IsINT64OverFlow() && bigData._value == 0)
	{
		// 除数为0就直接崩溃报错，这里其实抛出异常更好
		assert(false);
	}
	//左操作数为0，结果就为0
	if (!_IsINT64OverFlow() && _value == 0)
	{
		//return BigData(0);不能直接传0，类型不匹配，需要强制类型转换
		return BigData((INT64)0);
	}
	//左操作数小于右操作数，结果也为0
	//(1)左操作数的位数比右操作数位数少	(2)左右操作数位数相同，但是左操作数比右操作数小（考虑用strcmp()）
	if ((_strData.size() < bigData._strData.size()) ||
		(_strData.size() == bigData._strData.size() &&
		std::strcmp(_strData.c_str() + 1,bigData._strData.c_str() + 1) == -1))
	{
		return BigData((INT64)0);
	}
	//(不必判断左右操作数是否溢出)左右操作数相等时（不包括符号位），返回（正负1）
	if (_strData.size() == bigData._strData.size() && 
		std::strcmp(_strData.c_str() + 1,bigData._strData.c_str() + 1) == 0)
	{
		if (_strData[0] == bigData._strData[0])
			return BigData((INT64)1);
		else
			return BigData((INT64)-1);
	}
	//如果右操作数为(正负1)，结果为（正负左操作数）
	if (!bigData._IsINT64OverFlow())
	{
		if (bigData._value == 1)
		{
			return *this;
		} 
		else if (bigData._value == -1)//记住这里千万不能用else，要用else if（）
		{
			std::string tmp = _strData;
			if (tmp[0] == '+')
			{
				tmp[0] = '-';
			}
			else
			{
				tmp[0] = '+';
			}

			return BigData((char*)tmp.c_str());
		}
	}
	//如果两个操作数都没有溢出并且不满足上面的任意条件，那么则走到这里
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		//两个操作数相除，是不存在溢出的问题的
		return BigData(_value / bigData._value);
	}
	//至少有一个操作数溢出
	std::string strtmp = _Div(_strData,bigData._strData);
	if (_strData[0] == bigData._strData[0])
		strtmp[0] = '+';
	else
		strtmp[0] = '-';
	return BigData((char*)strtmp.c_str());
}