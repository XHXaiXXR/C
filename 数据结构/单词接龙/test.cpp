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
		//将每个单词的首字母和尾字母入栈
		string str;
		cin>>str;
		s.push(str[0]);
		s.push(str[str.size()-1]);
	}

	//末单词的尾字母不参与判断
	s.pop();

	//while里面的条件：首单词的首字母也不参与判断
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