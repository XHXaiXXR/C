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
int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	system("pause");
	return 0;
}