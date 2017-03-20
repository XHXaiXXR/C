#include<iostream>
using namespace std;
#include <string>

void test()
{
	string str1;
	cin>>str1;
	string str2(str1);

	int left = 0;
	int right = str1.size()-1;

	int count = 1;
	int len = right - left + 1;
	char num = str1[left];
	while (len--)
	{
		str2[len] = num;
	}
	if (str1 == str2)
	{
		cout<<count<<endl;
		return;
	}

	while (left < right)
	{
		++count;
		int tmp = str1[left];
		while (str1[left] == str1[left+1] && left <= right)
		{
			++left;
		}
		num = str1[++left];
		while (str1[right] == str1[right-1] && left <= right)
		{
			--right;
		}

		int newright = 0;
		int newleft = left;
		if (tmp == str1[right])
		{
			newright = --right;
		} 
		else
		{
			newright = right-1;
		}
		while (newleft <= newright)
		{
			str2[newleft] = num;
			str2[newright] = num;
			newleft++;
			newright--;
		}
		if (str1 == str2)
		{
			break;
		}
	}
	cout<<count<<endl;
}


int main()
{
	test();
	system("pause");
	return 0;
}