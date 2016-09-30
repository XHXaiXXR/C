#include<iostream>
using namespace std;
#include<string>
#include<queue>

void LongestSubString(string str)
{
	int maxlength = 1;
	queue<char> q;
	queue<char> qm;
	qm.push(str[0]);

	for(int i = 0;i < str.size()-1;i++)
	{
		q.push(str[i]);
		int j = i + 1;
		int length = 1;
		
		while (j <= str.size()-1 && str[i] != str[j])
		{
			bool flag = true;
			for (int t = i;t < j;t++)
			{
				if (str[t] == str[j])
				{
					flag = false;
					break;
				}
			}

			if (flag == true)
			{
				q.push(str[j]);
				j++;
				length++;
			}
			else
			{
				break;
			}
		}

		if(maxlength < length)
		{
			maxlength = length;

			while(!qm.empty())
			{
				qm.pop();
			}

			while(!q.empty())
			{
				qm.push(q.front());
				q.pop();
			}
		}
		while(!q.empty())
		{
			q.pop();
		}

	}

	while(!qm.empty())
	{
		cout<<qm.front();
		qm.pop();
	}
	cout<<endl<<"length = "<<maxlength<<endl;
}

void test()
{
	string str("abcabcbb");
	string str1("bbb");

	cout<<"str: "<<str<<endl<<"sub:";
	LongestSubString(str);
	cout<<endl<<"str1: "<<str1<<endl<<"sub:";
	LongestSubString(str1);
}
int main()
{
	test();
	system("pause");
	return 0;
}