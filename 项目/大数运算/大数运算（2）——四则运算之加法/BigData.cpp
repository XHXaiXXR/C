#define _CRT_SECURE_NO_WARNINGS 1
#include "BigData.h"
#include <iostream>
using namespace std;

BigData::BigData(const INT64 value)
	:_value(value)
{}

BigData::BigData(const char* str)
{
	//1��������	
	//12452435	5676573

	//2����ͷ�ԷǷ��ַ���ͷ
	//hdf328498	8938293

	//3����ͷ��0��ʼ
	//00002134	0003234

	//4���������ſ�ͷ������
	//+78748923	-897489234

	char symbol = *str;	//��ȡ����ʲô��ͷ��
	char* strtmp = (char*)str;	

	if (symbol == '+' || symbol == '-')
	{
		//����4������͵�1��������ɵ�1�����
		++strtmp;
	}
	else if (symbol >= '0' && symbol <= '9')
	{
		//����Ǵ����֣���ô�ʹ���һ�������ķ��š�+��
		symbol = '+';
	}
	else
	{
		//����ڶ��ַ��ţ��ԷǷ��ַ���ͷ������,�޳�
		_value = UN_INT64;
		return;
	}

	while (*strtmp == '0')
	{
		//����ǰ�õ�0����ɴ���������3������͵�1������ಢ�ɵ�1�����
		++strtmp;
	}

	//Ϊ_strData���ٿռ�
	_strData.resize(strlen(strtmp) + 1);	//+1��Ŀ����Ϊ�˸�_strData[0]��һ������λ
	_strData[0] = symbol;	//��֮ǰ�Ĳ������̵õ��ķ���λ�Ž�ȥ
	_value = 0;	//��_vulue��ʼֵ�������ߵ�����
	int index = 1;	//����_strData[0]���˷���λ��������������Ҫ��1�±꿪ʼ���

	//������ݣ�ͬʱ�������м��ǷǷ��ַ�ʱͬʱ����
	while (*strtmp >= '0' && *strtmp <= '9')
	{
		_value = _value * 10 + *strtmp - '0';
		_strData[index++] = *strtmp;
		++strtmp;
	}

	//�������ϲ�����_value����������ʽ��ŵ�,����һ�²�������������
	if (symbol == '-')
	{
		_value = 0 - _value;	//_value = (-1) * _value
	}

	//��������м��ǷǷ��ַ�����ô�ӵ�һ���Ƿ��ַ��Ժ󶼲���Ҫ��ŵ�_staData���ˣ���ô֮ǰ���ٵĿռ�Ͷ����˷���
	_strData.resize(index);
}

bool BigData::_IsINT64OverFlow()const
{
	std::string str = "+9223372036854775807";// long long �������������������ֵ

	if (_strData[0] == '-')
	{
		str = "-9223372036854775808";//long long �������͸���������Сֵ
	}

	if (_strData.size() < str.size())
	{
		//_strData�ĳ��ȶ�С��str�ĳ��ȣ���ֵһ�����ᳬ��
		return false;
	}
	else if (_strData.size() == str.size()&& _strData <= str)
	{
		return false;
	}

	//������������������㣬��ô�����
	return true;
}

std::ostream& operator<<(std::ostream& _cout,const BigData& bigData)
{
	if (!bigData._IsINT64OverFlow())
	{
		//û������Ļ���_value�������ֵ���������ݵ�ֵ
		_cout<<bigData._value;
	} 
	else
	{
		//����Ļ���_strData�����б���������ݵ�ֵ
		char* strtmp = (char*)bigData._strData.c_str();
		if (*strtmp == '+')
		{
			//�����������������λ����Ҫ���
			++strtmp;
		}

		_cout<<strtmp;
	}

	return _cout;
}

std::string BigData::Add(std::string left,std::string right)
{
	//��ȡ����string�ĳ���
	int LSize = left.size();
	int RSize = right.size();

	//��֤left�ĳ���ʼ�ղ�С��right�ĳ���
	if (LSize < RSize)
	{
		std::swap(left,right);
		std::swap(LSize,RSize);
	}

	//Ϊ������������ӵĽ������һ�����飬��СΪ��������Ĵ�С����1���������һ��λ����Ϊ�˴�����λ����Ƿ��λ�ı�־
	std::string str_result((LSize + 1),'0');
	str_result[0] = left[0];//��һ��λ��ͬ����ŷ���λ
	//int index = RSize;//��ȡ�̵�string������Ϊѭ��������������Ϊ���������±�
	int num = str_result.size() - 1;

	//�Ӻ���ǰ��������ӣ���ӽ�����ڽ��������
	for(int index = 1;index < RSize;++index)
	{
		char l = left[LSize - index] - '0';							//���������ֵ
		char r = right[RSize - index] - '0';						//�Ҳ�������ֵ
		char carry = str_result[num] - '0';							//��λ��ֵ����λ����ڽ�������

		char sum = l + r + carry;							//�����ͽ�λ��ӵ�ֵ
		str_result[num] = (char)((int)sum % 10 + '0');		//ÿ��λ����Ӻ�Ľ��
		str_result[num - 1] = (char)((int)sum / 10 + '0');	//��λ
		--num;
	}

	//�������stringһ��һ�̣���ô�����������Ժ���������û����ӵģ�Ҫ��ʣ�µĸ�λ���ڽ��������
	for (int index = num;index > 1;--index)
	{
		//��Ҫ���Լ���Ŀ�����Զ̳��ȵ����ݼ����Ժ��п����н�λ����λ����ڽ��������
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
	//������������û�г�����Χ
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		if (_strData[0] != bigData._strData[0])
		{
			//������������ţ���ӵĽ��һ�����ᳬ������
			return BigData(_value + bigData._value);
		} 
		else
		{
			//��������ͬ�ţ�����п������
			//һ�´�����ǲ�����������
			if ((_strData[0] == '+' && MAX_INT64 - _value >= bigData._value) ||
				(_strData[0] == '-' && MIN_INT64 - _value <= bigData._value))
			{
				return BigData(_value + bigData._value);
			}
		}
	}

	//�ߵ�����ֻ�п������������
	//һ����������һ�����������
	//����һ��������û������Ĳ��������������
	if (_strData[0] == bigData._strData[0])
	{
		//ͬ�����
		return BigData((char*)Add(_strData,bigData._strData).c_str());
	} 
	else
	{
		//������ == ͬ�����
		return BigData((char*)Sub(_strData,bigData._strData).c_str());
	}
}

