#include<iostream>
using namespace std;
#include "ListNode.h"

//≤‚ ‘‘ˆ…æ≤È∏ƒ
void test1()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.PushFront(5);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.PopFront();
	l.PopFront();
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.Erase(l.FindNode(2));
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.Insert(l.FindNode(1),5);
	l.Insert(l.FindNode(5),4);
	l.Insert(l.FindNode(3),10);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.Destroy();
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;
}

void test2()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(5);
	l.PushFront(9);
	l.PushFront(2);
	l.PushFront(4);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.BubbingSortList(l);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.EraseNotHead(l.FindNode(1));
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.ReverseList();
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.InsertFrontNode(l.FindNode(4),6);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	l.InsertFrontNode(l.FindNode(5),10);
	l.PrintList();
	cout<<l.FindMidNode()->_data<<endl;
	cout<<"size = "<<l.SizeNode()<<endl;

	l.DelKNode(4);
	l.PrintList();
	cout<<"size = "<<l.SizeNode()<<endl;

	//l.FindNode(2)->_next = l.FindNode(9);
	////cout<<l.JosephCycle(3)->_data<<endl;
	//cout<<l.CheckCycle()->_data<<endl;
	//cout<<l.GetCycleLenght()<<endl;

	l.FindNode(2)->_next = l.FindNode(10);
	cout<<l.GetCycleEntryNode(l.CheckCycle())->_data<<endl;
	cout<<l.GetCycleLenght(l.CheckCycle())<<endl;
}

void test3()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);

	List<int> l2;
	l2.PushBack(5);
	l2.PushBack(6);
	l2.PushBack(7);

	l1.FindNode(4)->_next = l2.FindNode(6);
	cout<<l1.CheckCroo(l2)<<endl;
}
int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}