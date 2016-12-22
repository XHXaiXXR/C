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