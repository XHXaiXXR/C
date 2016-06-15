#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

int OneCount(int num)
{
	if (num <= 0)
	{
		return 0;
	}

	int count = 0;
	if (num % 10 == 1)
	{
		count++;
	}
	return count+OneCount(num/10);
}

int SectionOneCount(int begin,int end)
{
	size_t count = 0;

	for (int i = begin;i <= end;i++)
	{
		count += OneCount(i);
	}
	return count;
}

void test1()
{
		int begin = 0;
		int end = 0;
		cout<<"ÇëÊäÈëÇø¼ä£º"<<endl;
		cin>>begin;
		cin>>end;
		if (begin > 0 && begin < end)
		{
			int count = SectionOneCount(begin,end);
			cout<<count<<endl;
		}
}
int main()
{
	test1();
	system("pause");
	return 0;
}