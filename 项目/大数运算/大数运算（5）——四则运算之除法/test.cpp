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
					count;
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
		{
			return BigData((INT64)1);
		}
		else
		{
			return BigData((INT64)-1);
		}
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
	{
		strtmp[0] = '+';
	} 
	else
	{
		strtmp[0] = '-';
	}
	return BigData((char*)strtmp.c_str());
}