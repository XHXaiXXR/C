#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "HashFunc.h"

void Test1()
{
	HashTable<int> ht(10);
	ht.Insert(89);
	ht.Insert(18);
	ht.Insert(49);
	ht.Insert(58);
	ht.Insert(9);
	ht.Print();
	cout<<ht.Find(58)<<endl;

	cout<<endl;
	ht.Remove(49);
	cout<<"9 exist?"<<ht.Find(9)<<endl;
}
void Test2()
{
	HashTable<int> ht(5);
	int j = 4;
	for (int i = 0;i < 10;i++)
	{
		ht.Insert(i*j);
		j++;
	}
	ht.Print();
	cout<<ht.Capacity()<<endl;
}
int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}