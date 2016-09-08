#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
#include <stack>
#include<string>

bool  ChineseStringUpPuzzle(int n)
{
	assert(n >= 2);
	assert(n <= 200);

	stack<char> s;

	while (n--)
	{
		//��ÿ�����ʵ�����ĸ��β��ĸ��ջ
		string str;
		cin>>str;
		s.push(str[0]);
		s.push(str[str.size()-1]);
	}

	//ĩ���ʵ�β��ĸ�������ж�
	s.pop();

	//while������������׵��ʵ�����ĸҲ�������ж�
	while (s.size() != 1)
	{
		char first = s.top();
		s.pop();
		char second = s.top();
		s.pop();

		if (first != second)
		{
			return false;
		}
	}
	return true;
}
void test()
{
	int n = 0;
	cin>>n;
	if (ChineseStringUpPuzzle(n))
	{
		cout<<"yes"<<endl;
	} 
	else
	{
		cout<<"no"<<endl;
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}