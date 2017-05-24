#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include<string>
#include <vector>
#include<algorithm>


//将n进制转换为2进制
void Test()
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
	cout<<"sum = "<<sum<<endl;

	//将10进制转换为2进制
	vector<int> v;
	while (sum > 0)
	{
		v.push_back(sum % 2);
		sum /= 2;
	}
	reverse(v.begin(),v.end());//此时v容器里存的就是数值的2进制


}

int main()
{
	Test();
	system("pause");
	return 0;
}