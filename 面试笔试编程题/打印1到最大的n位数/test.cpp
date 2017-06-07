#include<iostream>
using namespace std;
#include<vector>

bool Increment(vector<int>& v)
{
	for (int i = v.size()-1; i >= 0; --i)
	{
		++v[i];

		if (v[i] >= 10)
		{
			v[i] -= 10;
		} 
		else
		{
			break;
		}
	}

	//�����һλ��Ϊ0����ô˵������nλ���Ѿ�ȫ���ҳ�����
	if (v[0] != 0)
	{
		return true;
	}
	return false;
}

void PrintNum(const vector<int>& v)
{
	int i = 0;
	while(v[i] == 0)
	{
		++i;
	}

	for (;i < v.size();i++)
	{
		cout<<v[i];
	}

	printf("\t");
}

void test()
{
	int num = 0;
	cin>> num;
	vector<int> v;
	v.resize(num+1);

	while (!Increment(v))
	{
		PrintNum(v);
	}
}

int main()
{
	test();
	system("pause");	
	return 0;
}