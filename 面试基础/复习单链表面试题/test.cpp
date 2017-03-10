#include<iostream>
using namespace std;
#include "ListNode.h"

void test()
{
	List<int> l;
	l.PushFrond(1);
	l.PushFrond(2);
	l.PushFrond(3);
	l.PushFrond(4);
	l.PushFrond(5);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.PopFrond();
	l.PopFrond();
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.Erase(l.FindNode(2));
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.Destroy();
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;


}

int main()
{
	test();
	system("pause");
	return 0;
}