#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include<string>
#include <vector>
#include<algorithm>


//��n����ת��Ϊ2����
void nTotwo(vector<int>& v)
{
	//�������ֵ��n���Ƶ�
	int n = 0;
	cin>>n;
	//�������ֵ�Ƕ���
	string num;
	cin>>num;

	int i = num.size()-1;//��ȡ����ֵ�����һλ
	int index = 0;//��¼0-x�η�
	int sum = 0;//����ת����ʮ������
	double newN = n;//pow�ĵ�һ����������Ҫ��double����

	while (i >= 0)
	{
		if (num[i] >= 'A' && num[i] <= 'Z')
		{
			int newnum = num[i] - 'A' + 10;
			sum += newnum * pow(newN,index);
		} 
		else
		{
			sum += (num[i]-'0') * pow(newN,index);
		}
		
		++index;
		--i;
	}
	//�鿴ʮ���Ƶ�ֵ
	//cout<<"sum = "<<sum<<endl;

	//��10����ת��Ϊ2����
	while (sum > 0)
	{
		v.push_back(sum % 2);
		sum /= 2;
	}
	reverse(v.begin(),v.end());//��ʱv�������ľ�����ֵ��2����
}

//��2����ת����m����
void twoTom(const vector<int>& v,string& num)
{
	double m = 0.0;
	cin>>m;

	int b = 0;
	if (m == 8)
	{
		b = 3;
	} 
	else
	{
		b = sqrt(m);
	}
	char c = '\0';

	for (int i = v.size()-1; i >= 0;)
	{
		int newb = b;
		int j = 0;//�ݷ�
		int sum = 0;
		while (newb-- && i >= 0)
		{
			sum += v[i] * pow(2.0, j++);
			i--;
		}

		if (sum < 10)
		{
			c = sum + '0';
			num.push_back(c);
		} 
		else
		{
			c = sum - 10 + 'A';
			num.push_back(c);
		}
	}

	reverse(num.begin(),num.end());
}

void PrintTwo(const vector<int>& v)
{
	for (int i = 0;i < v.size();i++)
	{
		cout<<v[i];
	}
	cout<<endl;
}

int main()
{
	vector<int> v;
	nTotwo(v);

	string num;
	twoTom(v, num);

	cout<<num<<endl;
	system("pause");
	return 0;
}