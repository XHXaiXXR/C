#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void Test1()//PushBack
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);
	PushBack(&seq,4);
	PushBack(&seq,5);
	PushBack(&seq,8);

	PrintSeqList(&seq);
}
void Test2()//PopBack	
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);
	PushBack(&seq,4);
	PushBack(&seq,5);

	PrintSeqList(&seq);

	PopBack(&seq);
	PopBack(&seq);
	PopBack(&seq);
	//PopBack(&seq);
	//PopBack(&seq);
	//PopBack(&seq);

	PrintSeqList(&seq);
}
void Test3()//PushFront
{
	SeqList seq;
	InitSeqList(&seq);
	PushFront(&seq,1);
	PushFront(&seq,2);
	PushFront(&seq,3);
	//PushFront(&seq,4);
	//PushFront(&seq,5);
	//PushFront(&seq,8);

	PrintSeqList(&seq);
}
void Test4()//PopFront
{
	SeqList seq;
	InitSeqList(&seq);
	PushFront(&seq,1);
	PushFront(&seq,2);
	PushFront(&seq,3);
	PushFront(&seq,4);
	//PushFront(&seq,5);
	//PushFront(&seq,5);


	PrintSeqList(&seq);

	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	//PopFront(&seq);

	PrintSeqList(&seq);
}
void Test5()//Insert
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);

	PrintSeqList(&seq);

	Insert(&seq,2,5);

	PrintSeqList(&seq);
}
void Test6()//Remove
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,2);
	PushBack(&seq,4);

	PrintSeqList(&seq);

	Remove(&seq,2);

	PrintSeqList(&seq);
}
void Test7()//RemoveAll
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);
	PushBack(&seq,2);
	PushBack(&seq,4);

	PrintSeqList(&seq);

	RemoveAll(&seq,2);

	PrintSeqList(&seq);
}
void Test8()//Sort
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,5);
	PushBack(&seq,3);
	PushBack(&seq,4);
	PushBack(&seq,2);

	PrintSeqList(&seq);
	Sort(&seq);
	PrintSeqList(&seq);
}
void Test9()//BinarySearch
{
	int ret = 0;
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,5);
	PushBack(&seq,3);
	PushBack(&seq,4);
	PushBack(&seq,2);

	PrintSeqList(&seq);

	ret = BinarySearch(&seq,2);
    PrintSeqList(&seq);
	
	if (ret < 0)
	{
		printf("sorry, no find x\n");
	} 
	else
	{
		printf("%d\n",ret);
	}
}
void Test10()//Find
{
	int ret = 0;
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);
	PushBack(&seq,4);
	PushBack(&seq,5);

	PrintSeqList(&seq);

	ret = Find(&seq,4);
	if (ret < 0)
	{
		printf("no find x\n");
		return;
	} 
	else
	{
		printf("find x\n");
		printf("%d\n",ret);
	}
}
void Test11()//Erase
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq,1);
	PushBack(&seq,2);
	PushBack(&seq,3);
	PushBack(&seq,4);

	PrintSeqList(&seq);
	Erase(&seq,2);
	PrintSeqList(&seq);
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	system("pause");
	return 0;
}