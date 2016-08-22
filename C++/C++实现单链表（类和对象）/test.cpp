#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "LinkList.h"

void Test()
{
	LinkList list;
	for (int i = 1;i < 6;i++)
	{
		list.PushBack(i);
	}
	cout<<list<<endl;

	list.PushFrond(10);
	list.PushFrond(9);
	list.PushFrond(8);
	cout<<list<<endl;

	list.PopBack();
	list.PopBack();
	cout<<list<<endl;
	list.PopFrond();
	list.PopFrond();
	cout<<list<<endl;

	LinkListNode* cur = list.Find(9);
	if (cur != NULL)
	{
		cout<<*cur<<endl;
	}
	
	list.Insert(list.Find(3),4);
	cout<<list<<endl;
	list.Insert(list.Find(1),100);
	cout<<list<<endl;
	list.Insert(list.Find(10),11);
	cout<<list<<endl;

	list.Remove(list.Find(4));
	cout<<list<<endl;
	list.Remove(list.Find(10));
	cout<<list<<endl;
	list.Remove(list.Find(100));
	cout<<list<<endl;

}
int main()
{
	Test();
	system("pause");
	return 0;
}