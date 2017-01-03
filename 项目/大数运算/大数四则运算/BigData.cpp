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
	//1��������	12452435	5676573
	//2����ͷ�ԷǷ��ַ���ͷ hdf328498	8938293
	//3����ͷ��0��ʼ  00002134	0003234
	//4���������ſ�ͷ������  +78748923	-897489234

	char symbol = *str;	//��ȡ����ʲô��ͷ��
	char* strtmp = (char*)str;	

	if (symbol == '+' || symbol == '-')
	{
		//������������鲢Ϊ��һ�����
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

	//��������м��ǷǷ��ַ�����ô�ӵ�һ���Ƿ��ַ��Ժ󶼲���Ҫ��ŵ�_staData���ˣ���ô֮ǰ���ٵĿռ�Ͷ����˷��ˣ�������Ҫ�������������
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
//ͬ����ӵļӷ��������ţ�
std::string BigData::_Add(std::string left,std::string right)
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
//ͬ������ļ����������ţ�
std::string BigData::_Sub(std::string left,std::string right)
{
	char symbol = '+';
	//ȷ�����������
	//����������Ҳ������Ƚϴ�С����������������������������в���������õ��Ľ����Ϊ��
	//����-�������������,((10)-(8) --> l > r --> "+")	((8)-(10) --> l < r --> '-')
	//����-����Ҳ�����������((-8)-(-10) --> l > r --> '+')	((-10)-(-8) --> l < r --> '-')
	//��������ͬ������ͬ����ֻҪl > r����ô����ķ���ȷ��Ϊ ��+������֮��Ϊ��-��
	if (_Compare(left,right) < 0)
	{
		symbol = '-';
	} 

	//ȷ�����������Ҳ�����
	if (left[0] == '+')
	{
		//ȷ����������������������ʱ���ϴ����Ϊ�������
		if (_Compare(left,right) < 0)
		{
			std::swap(left,right);
		}
	}
	else	//left[0] == '-'
	{
		//ȷ�����������������Ǹ���ʱ����С����Ϊ�Ҳ�����
		if (_Compare(left,right) > 0)
		{
			std::swap(left,right);
		}
	}

	std::string str_result(left.size(),'0');//��������ĳ��ȿ�����һ���µĿռ�

	//�ý�С�������ĳ�����Ϊѭ��������
	int index = left.size() - 1;
	for (size_t i = 1;i < right.size();++i)
	{
		int lnum = (left[left.size() - i] - '0') + 10;	//���ǵ�����������������Զ���������һλ��λ
		str_result[index - 1] = '1';			//������һ�����Ľ�λ���������һλ����Ҫ�б��
		int rnum = right[right.size() - i] - '0';			//�϶���һ��������10������

		int result = lnum - rnum - (str_result[index] - '0');			//������,�ǵ�ҲҪ�ѽ�λ����ȥ
		str_result[index] = (result % 10) + '0';//�����ݷ��ڽ����

		//˵��û�н�λ����Ҫ��ǰ��str_result[i - 1]�޸�Ϊû�н�λ
		if (result / 10 != 0)
		{
			str_result[index - 1] = '0';
		}
		--index;
	}
	//���Ҳ��������Ȳ�ͬʱ�����Ժ�ѭ���Ժ�ʣ�µ�λҪ���ηŽ�string����
	for (int i = left.size() - right.size();i > 0;--i)
	{
		str_result[i] = (left[i] - '0') - (str_result[i] - '0') + '0';
	}

	str_result[0] = symbol;		//��ǰ��������Ľ�������ȸ�ֵ��ȥ

	return str_result;
}
//�����ŵ��ַ����Ƚϴ�С
//�����Ƚϴ�С  left > right (����1)  left < right ������-1�� left == right ������0��
int BigData::_Compare(std::string left,std::string right)
{
	//���
	if (left[0] != right[0])
	{
		//��������������ķ��Ų�ͬ����ô�����϶����ڸ���
		if (left[0] == '+')
		{
			return 1;
		} 
		else	//left[0] == '-'
		{
			return -1;
		}
	} 
	//ͬ��
	else
	{
		int leftSize = left.size();
		int rightSize = right.size();

		if (leftSize != rightSize)
		{
			//�ó������Ƚϴ�С
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

			//��ȥ����λ��ʣ�µ����ַ���
			std::string Lstr = left.substr(1,(leftSize - 1));	//��һ�����������ſ�ʼ��λ�ã��ڶ������������ų���
			std::string Rstr = right.substr(1,(rightSize - 1));	//��һ�����������ſ�ʼ��λ�ã��ڶ������������ų���

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
			//���´�����ǲ�����������
			if ((_strData[0] == '+' && (MAX_INT64 - _value) >= bigData._value) ||
				(_strData[0] == '-' && (MIN_INT64 - _value) <= bigData._value))
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
		return BigData((char*)_Add(_strData,bigData._strData).c_str());
	} 
	else	//���
	{
		//������ == ͬ�����
		if (_strData[0] == '+')
		{
			//�� + �� = �� - �� -------- ���Ҳ����������ɸ������
			(char) bigData._strData[0] = '+';
		} 
		else	//_strData[0] == '-'
		{
			//�� + �� = �� - �� ----------- ���Ҳ���������������ɸ�
			(char)bigData._strData[0] = '-';
		}
		return BigData((char*)_Sub(_strData,bigData._strData).c_str());
	}
}
BigData BigData::operator-(const BigData& bigData)
{
	//���Ҳ�������û�����
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		//ͬ�����һ���������
		if (_strData[0] == bigData._strData[0])
		{
			return BigData(_value - bigData._value);
		} 
		//�������п���������߲����
		else
		{
			//��������Ų���������
			//�� - ��	�� - ��
			if ((_strData[0] == '+' && (MAX_INT64 + bigData._value) >= _value) || 
				(_strData[0] == '-' && (MIN_INT64 + bigData._value) <= _value))
			{
				return BigData(_value - bigData._value);
			}
		}
	}

	//���ߵ�����ʱ��һ���������������
	//��1��������������һ���Ѿ����
	//��2������û������Ĳ�����������������
	if (_strData[0] != bigData._strData[0])
	{
		//������������ţ��п����ǣ��� - ������Ҳ�п����ǣ��� - ���������
		if (_strData[0] == '+')
		{
			//����������������Ҳ������Ǹ���
			//�� - �� = �� + �� ------���Ҳ�����ת��������������_Add()����
			(char)bigData._strData[0] = '+';//��ΪbigData��const��������Ҫǿת�ɣ�char���ſ����޸����ķ���λ
		}
		else	//_strData[0] == '-'
		{
			//��������Ǹ������Ҳ�����������
			//�� - �� = �� + �� -------- ���Ҳ�����ת�ɸ���
			(char)bigData._strData[0] = '-';			
		}
		return BigData((char*)_Add(_strData,bigData._strData).c_str());
	}

	//ͬ���������_Sub����
	return BigData((char*)_Sub(_strData,bigData._strData).c_str());
}
std::string BigData::_Mul(std::string left,std::string right)
{
	int LSize = left.size();
	int RSize = right.size();
	int longth = LSize + RSize + 1;

	std::string str_result(longth,'0');

	//���Ҳ�������Ϊѭ��������
	for (int i = 1;i <= RSize;++i)
	{
		//��λ��־
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

		//ѭ�������Ժ���һ����λû��д�������
		sum[longth - sumindex] = carry + '0';

		//��ÿ�εõ��µ�ֵ���ϴε��ܽ�����
		str_result = _Add(sum,str_result);
	}
	return str_result;
}
BigData BigData::operator*(const BigData& bigData)
{
	int LSize = _strData.size();
	int RSize = bigData._strData.size();

	//�����Ƿ���λ����ȡ���Ҳ����������ַ���
	std::string leftstr = _strData.substr(1,(LSize - 1));
	std::string rightstr = bigData._strData.substr(1,(RSize - 1));
	
	std::string str_result = _Mul(leftstr,rightstr);
	if (_strData[0] == bigData._strData[0])
	{
		//ͬ�����Ϊ����
		str_result[0] = '+';
	} 
	else
	{
		//������Ϊ����
		str_result[0] = '-';
	}
	return BigData((char*)str_result.c_str());
}
//�����ּ������޷��ţ���������������Ҳ�����
std::string BigData::_UnsignSub(std::string left,std::string right)
{
	std::string str_result(left.size() + 1,'0');//��������ĳ��ȿ�����һ���µĿռ�
	int index = left.size();

	//�ý�С�������ĳ�����Ϊѭ��������
	for (size_t i = 0;i < right.size();++i)
	{
		int lnum = (left[left.size() - 1 - i] - '0') + 10;	//���ǵ�����������������Զ���������һλ��λ
		str_result[index - 1] = '1';			//������һ�����Ľ�λ���������һλ����Ҫ�б��
		int rnum = right[right.size() - 1 - i] - '0';			//�϶���һ��������10������

		int result = lnum - rnum - (str_result[index] - '0');			//������,�ǵ�ҲҪ�ѽ�λ����ȥ
		str_result[index] = (result % 10) + '0';//�����ݷ��ڽ����

		//˵��û�н�λ����Ҫ��ǰ��str_result[i - 1]�޸�Ϊû�н�λ
		if (result / 10 != 0)
		{
			str_result[index - 1] = '0';
		}
		--index;
	}
	//���Ҳ��������Ȳ�ͬʱ�����Ժ�ѭ���Ժ�ʣ�µ�λҪ���ηŽ�string����
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

	//��������λȡ�µ����Ҳ�����
	std::string Left = left.substr(1,right.size() - 1);
	std::string Right = right.substr(1,right.size() - 1);
	//����ӵڼ�λ��ʼд��
	int i = right.size() - 1;

	//ȡ��ͬ���ȵ�����������Ҳ�����������������С���Ҳ�������������������ô���������Ҫ��һλ
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
			//������ת���ַ�����������������ֵ��ַ�����˵ļ���
			ss<<num;
			int count = 0;//��¼sumǰ��0�ĸ���

			//sum = num * Right �Ľ��
			std::string sum = _Mul(Right,ss.str());
			for (int j = 0;j < sum.size();++j)
			{
				if (sum[j] == '0')
					count++;
				else
					break;
			}
			sum = sum.substr(count,sum.size() - count);//����sumǰ�õ�0
			//num��Ҫ�Ž���������ֵ��ÿ����num*�Ҳ��������������˳����Ľ��С����������ˣ���ô��ʱ���num������ȷ��ֵ
			if ((sum.size() < Left.size())||
				(sum.size() == Left.size()) &&
				(strcmp(sum.c_str(),Left.c_str()) == -1) ||
				(sum.size() == Left.size()) &&
				(strcmp(sum.c_str(),Left.c_str()) == 0))
			{
				break;
			}
		}
		//�����num����ֵ������������
		str_result[i] = num + '0';
		stringstream ss1;
		//������ת���ַ���������������˵ļ���
		ss1<<num;
		int count = 0;//��¼sumǰ��0�ĸ���
		std::string sum = _Mul(Right,ss1.str());
		for (int j = 0;j < sum.size();++j)
		{
			if (sum[j] == '0')
				count++;
			else
				break;
		}
		sum = sum.substr(count,sum.size() - count);//����sumǰ�õ�0
		//���㲢����num * �Ҳ�������ֵ����������Ĳ�ֵ���µ�������� = ��ֵ*10 + ԭ���������i+1��
		Left = _UnsignSub(Left,sum);
		//��ֹԽ�����
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
	//��������Ϊ0���Ҳ���������Ϊ0��
	if (!bigData._IsINT64OverFlow() && bigData._value == 0)
	{
		// ����Ϊ0��ֱ�ӱ�������������ʵ�׳��쳣����
		assert(false);
	}
	//�������Ϊ0�������Ϊ0
	if (!_IsINT64OverFlow() && _value == 0)
	{
		//return BigData(0);����ֱ�Ӵ�0�����Ͳ�ƥ�䣬��Ҫǿ������ת��
		return BigData((INT64)0);
	}
	//�������С���Ҳ����������ҲΪ0
	//(1)���������λ�����Ҳ�����λ����	(2)���Ҳ�����λ����ͬ����������������Ҳ�����С��������strcmp()��
	if ((_strData.size() < bigData._strData.size()) ||
		(_strData.size() == bigData._strData.size() &&
		std::strcmp(_strData.c_str() + 1,bigData._strData.c_str() + 1) == -1))
	{
		return BigData((INT64)0);
	}
	//(�����ж����Ҳ������Ƿ����)���Ҳ��������ʱ������������λ�������أ�����1��
	if (_strData.size() == bigData._strData.size() && 
		std::strcmp(_strData.c_str() + 1,bigData._strData.c_str() + 1) == 0)
	{
		if (_strData[0] == bigData._strData[0])
			return BigData((INT64)1);
		else
			return BigData((INT64)-1);
	}
	//����Ҳ�����Ϊ(����1)�����Ϊ���������������
	if (!bigData._IsINT64OverFlow())
	{
		if (bigData._value == 1)
		{
			return *this;
		} 
		else if (bigData._value == -1)//��ס����ǧ������else��Ҫ��else if����
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
	//���������������û��������Ҳ����������������������ô���ߵ�����
	if (!_IsINT64OverFlow() && !bigData._IsINT64OverFlow())
	{
		//����������������ǲ���������������
		return BigData(_value / bigData._value);
	}
	//������һ�����������
	std::string strtmp = _Div(_strData,bigData._strData);
	if (_strData[0] == bigData._strData[0])
		strtmp[0] = '+';
	else
		strtmp[0] = '-';
	return BigData((char*)strtmp.c_str());
}