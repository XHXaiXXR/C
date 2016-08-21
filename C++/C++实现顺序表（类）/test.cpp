#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "SeqList.h"

void Test1()
{
	SeqList seq;
	for (int i = 0;i < 5;i++)
	{
		seq.PushBack(i);
	}
	cout<<seq<<endl;
	cout<<seq.Capacity()<<endl;

	seq.PushFront(5);
	seq.PushFront(6);
	cout<<seq<<endl;
	cout<<seq.Capacity()<<endl;

	seq.PopBack();
	seq.PopBack();
	seq.PopBack();
	cout<<seq<<endl;

	seq.PopFront();
	seq.PopFront();
	cout<<seq<<endl;
}
void Test2()
{
	SeqList seq;
	for (int i = 0;i < 5;i++)
	{
		seq.PushBack(i);
	}
	cout<<seq<<endl;
	cout<<seq.Find(5)<<endl;
	seq.Insert(seq.Find(2),10);
	cout<<seq<<endl;

	seq.Remove(seq.Find(3));
	cout<<seq<<endl;
	cout<<seq.Size()<<endl;
	seq.Remove(seq.Find(10));
	cout<<seq<<endl;
	cout<<seq.Size()<<endl;
}
void Test3()
{
	SeqList seq;
	for (int i = 0;i < 5;i++)
	{
		seq.PushBack(i);
	}
	cout<<seq<<endl;

	seq.Insert(seq.Find(2),10);
	seq.Insert(seq.Find(0),10);	
	seq.Insert(seq.Find(4),10);
	cout<<seq<<endl;
	seq.RemoveAll(seq.FindData(10));
	cout<<seq<<endl;

	SeqList seq2;
	for (int i = 6;i >0;i--)
	{
		seq2.PushBack(i);
	}
	seq2.Sort(seq2);
	cout<<seq2<<endl;
}
int main()
{
	//Test1();
	//Test2();
	Test3();
	system("pause");
	return 0;
}