#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include<string>
#include <vector>
#include<algorithm>


//��n����ת��Ϊ2����
void Test()
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
	cout<<"sum = "<<sum<<endl;

	//��10����ת��Ϊ2����
	vector<int> v;
	while (sum > 0)
	{
		v.push_back(sum % 2);
		sum /= 2;
	}
	reverse(v.begin(),v.end());//��ʱv�������ľ�����ֵ��2����


}

int main()
{
	Test();
	system("pause");
	return 0;
}