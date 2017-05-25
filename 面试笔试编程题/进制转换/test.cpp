#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include<string>
#include <vector>
#include<algorithm>


//将n进制转换为2进制
void nTotwo(vector<int>& v)
{
	//输入的数值是n进制的
	int n = 0;
	cin>>n;
	//输入的数值是多少
	string num;
	cin>>num;

	int i = num.size()-1;//获取到数值的最后一位
	int index = 0;//记录0-x次方
	int sum = 0;//最终转换的十进制数
	double newN = n;//pow的第一个参数必须要是double类型

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
	//查看十进制的值
	//cout<<"sum = "<<sum<<endl;

	//将10进制转换为2进制
	while (sum > 0)
	{
		v.push_back(sum % 2);
		sum /= 2;
	}
	reverse(v.begin(),v.end());//此时v容器里存的就是数值的2进制
}

//将2进制转换成m进制
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
		int j = 0;//幂方
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