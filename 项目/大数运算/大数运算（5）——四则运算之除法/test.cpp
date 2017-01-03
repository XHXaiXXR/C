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
					count;
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
		{
			return BigData((INT64)1);
		}
		else
		{
			return BigData((INT64)-1);
		}
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
	{
		strtmp[0] = '+';
	} 
	else
	{
		strtmp[0] = '-';
	}
	return BigData((char*)strtmp.c_str());
}