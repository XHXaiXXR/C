#include <iostream>
using namespace std;
#include <stack>

bool Match(char c1,char c2)
{
	if ((c1 == '{') && (c2 == '}'))
	{
		return true;
	} 
	else if ((c1 == '[') && (c2 == ']'))
	{
		return true;
	}
	else if ((c1 == '(') && (c2 == ')'))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void test()
{
	stack<char> s;
	char c = '0';
	while ((c = getchar()) != EOF)
	{
		switch(c)
		{
		case '{':
		case '[':
		case '(':
			{
				s.push(c);
			}
			break;

		case '}':
		case ']':
		case ')':
			{
				if (s.empty())
				{
					cout<<"���������Ų�ƥ��"<<endl;
					return;
				}				
				if (Match(s.top(),c))
				{
					s.pop();
				}
			}
			break;
		default:
			break;
		}
	}
	if (s.empty() == false)
	{
		cout<<"�����Ŷ���"<<endl;
	}
	else
	{
		cout<<"����ƥ��"<<endl;
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}