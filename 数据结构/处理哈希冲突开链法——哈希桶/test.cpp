#include<iostream>
using namespace std;
#include"HashList.h"
#include<string>
void test()
{
	HashList<string,int> hl;
	string str[] = {"hash","table","xiao","hai","xia"};
	
	size_t size = sizeof(str)/sizeof(str[0]);
	for(int i = 0;i < size;i++)
	{
		hl.Insert(str[i],i);
	}
	hl.Display();

	cout<<endl;
	hl.Remove("xiao");
	hl.Display();

}

int main()
{
	test();
	system("pause");
	return 0;
}