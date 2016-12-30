#include<iostream>
using namespace std;
#include <string>

void test()
{
	string num = "";
	cin>>num;

	string::iterator begin = num.begin();
	string::iterator end = --num.end();

	while (begin < end)
	{
		swap(*begin,*end);
		begin++;
		end--;
	}

	while (num[0] == '0')
	{
		num = num.substr(1,num.size() - 1);
	}

	cout<<num<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}