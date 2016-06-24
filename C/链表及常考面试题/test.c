#define _CRT_SECURE_NO_WARNINGS 1
#include "SListNode.h"

void Test1()//PushBack   PopBack
{
	PSListNode pHead = NULL;
	InitList(&pHead);
	PushBack(&pHead,0);
	PushBack(&pHead,1);
	PushBack(&pHead,2);
	PushBack(&pHead,3);
	PushBack(&pHead,4);

	PrintList(&pHead);

	PopBack(&pHead);
	PopBack(&pHead);

	PrintList(&pHead);
}

void Test2()//PushFront   PopFront   Find
{ 
	PSListNode ret = NULL;
	PSListNode pHead = NULL;
	InitList(&pHead);
	PushFront(&pHead,0);
	PushFront(&pHead,1);
	PushFront(&pHead,2);
	PushFront(&pHead,3);
	PushFront(&pHead,4);

	PrintList(&pHead);

	PopFront(&pHead);
	PopFront(&pHead);
	//PopFront(&pHead);
	//PopFront(&pHead);
	//PopFront(&pHead);
	//PopFront(&pHead);

	PrintList(&pHead);

	ret = Find(&pHead,2);
	if (ret == NULL)
	{
		printf("no find\n");
	} 
	else
	{
		printf("%d \n",ret->data);
	}
}

void Test3()//Erase
{
	PSListNode pHead = NULL;
	InitList(&pHead);
	PushBack(&pHead,0);
	PushBack(&pHead,1);
	PushBack(&pHead,2);
	PushBack(&pHead,3);
	PushBack(&pHead,4);
	PrintList(&pHead);

	//Erase(&pHead,Find(&pHead,2));
	Erase(&pHead,Find(&pHead,4));
	//Erase(&pHead,Find(&pHead,0));
	PrintList(&pHead);

	Insert(&pHead,Find(&pHead,2),8);
	Insert(&pHead,Find(&pHead,0),9);
	PrintList(&pHead);

	DestroyList(&pHead);
	PrintList(&pHead);
}

void Test4()//BubblingSort   EraseNotHead  ReverseLish  InsertFrontNode
{
	PSListNode ret = NULL;
	PSListNode pHead = NULL;
	InitList(&pHead);
	PushBack(&pHead,9);
	PushBack(&pHead,1);
	PushBack(&pHead,8);
	PushBack(&pHead,3);
	PushBack(&pHead,6);
	PrintList(&pHead);

	BubblingSort(&pHead);
	PrintList(&pHead);

	EraseNotHead(Find(&pHead,8));
	PrintList(&pHead);

	ReverseLish(&pHead);
	PrintList(&pHead);

	InsertFrontNode(Find(&pHead,3),15);
	PrintList(&pHead);

	ret = FindMidNode(&pHead);
	printf("%d\n",ret->data);

	DelKNode(&pHead,3);
	PrintList(&pHead);

	DestroyList(&pHead);
	PrintList(&pHead);
}

void Test5()//MergeSList
{
	PSListNode pHead1 = NULL;
	PSListNode pHead2 = NULL;
	PSListNode ret = NULL;
	InitList(&pHead1);
	PushBack(&pHead1,1);
	PushBack(&pHead1,3);
	PushBack(&pHead1,5);
	PushBack(&pHead1,7);
	PushBack(&pHead1,9);
	PrintList(&pHead1);

	InitList(&pHead2);
	PushBack(&pHead2,2);
	PushBack(&pHead2,4);
	PushBack(&pHead2,6);
	PushBack(&pHead2,8);
	PushBack(&pHead2,10);
	PrintList(&pHead2);
	ret = MergeSList(&pHead1,&pHead2);
	PrintList(&ret);
}

void Test6()//JosephCycle
{
	PSListNode pHead = NULL;
	PSListNode ret1 = NULL;
	PSListNode ret2 = NULL;
	PSListNode ptmp = NULL;
	InitList(&pHead);
	PushBack(&pHead,1);
	PushBack(&pHead,3);
	PushBack(&pHead,5);
	PushBack(&pHead,7);
	PushBack(&pHead,9);
	PrintList(&pHead);

	ret1 = Find(&pHead,9);
	ret2 = Find(&pHead,1);
	ret1->_NextNode = ret2;

	ptmp = JosephCycle(&pHead,3);
	printf("%d\n",ptmp->data);
}

void Test7()//CheckCycle  GetCircleLength   GetCycleEntryNode
{
	PSListNode pHead = NULL;
	PSListNode ret1 = NULL;
	PSListNode ret2 = NULL;
	PSListNode ptmp = NULL;
	PSListNode Entrance = NULL;
	int num = 0;

	InitList(&pHead);
	PushBack(&pHead,1);
	PushBack(&pHead,3);
	PushBack(&pHead,5);
	PushBack(&pHead,7);
	PushBack(&pHead,9);
	PrintList(&pHead);

	ret1 = Find(&pHead,9);
	ret2 = Find(&pHead,3);
	ret1->_NextNode = ret2;

	ptmp = CheckCycle(&pHead);
	if (ptmp != NULL)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	num = GetCircleLength(ptmp);
	printf("num = %d\n",num);

	Entrance = GetCycleEntryNode(&pHead,&ptmp);
	printf("Entrance = %d\n",Entrance->data);
}

void Test8()//CheckCross
{
	PSListNode pHead1 = NULL;
	PSListNode pHead2 = NULL;
	PSListNode ret1 = NULL;
	PSListNode ret2 = NULL;
	int tmp = 0;

	InitList(&pHead1);
	PushBack(&pHead1,1);
	PushBack(&pHead1,3);
	PushBack(&pHead1,5);
	PushBack(&pHead1,7);
	PushBack(&pHead1,9);
	PrintList(&pHead1);

	InitList(&pHead2);
	PushBack(&pHead2,2);
	PushBack(&pHead2,4);
	PushBack(&pHead2,6);
	ret1 = Find(&pHead2,6);
	ret2 = Find(&pHead1,7);
	ret1->_NextNode = ret2;
	PrintList(&pHead2);

	tmp = CheckCross(&pHead1,&pHead2);
	if (tmp == 1)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
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
	Test8();
	system("pause");
	return 0;
}