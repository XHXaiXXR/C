#define _CRT_SECURE_NO_WARNINGS 1
#include "DoubleSLishtNode.h"

void Test1()//InitDSList  PushBack PrintfDSList  PopBack
{
	PDoubleSListNode pHead = NULL;

	InitDSList(&pHead);
	PushBack(&pHead,0);
	PushBack(&pHead,1);
	PushBack(&pHead,2);
	PushBack(&pHead,3);
	PrintfDSList(&pHead);

	PopBack(&pHead);
	PopBack(&pHead);
	//PopBack(&pHead);
	//PopBack(&pHead);
	//PopBack(&pHead);

	PrintfDSList(&pHead);
}

void Test2()//PushFront  PopFront
{
	PDoubleSListNode pHead = NULL;
	InitDSList(&pHead);
	PushFront(&pHead,0);
	PushFront(&pHead,1);
	PushFront(&pHead,2);
	PushFront(&pHead,3);
	PrintfDSList(&pHead);

	PopFront(&pHead);
	PopFront(&pHead);
	//PopFront(&pHead);
	//PopFront(&pHead);
	//PopFront(&pHead);

	PrintfDSList(&pHead);
}

void Test3()//Find   Erase
{
	PDoubleSListNode pHead = NULL;

	InitDSList(&pHead);
	PushBack(&pHead,0);
	PushBack(&pHead,1);
	PushBack(&pHead,2);
	PushBack(&pHead,3);
	PrintfDSList(&pHead);

	//Erase(&pHead,Find(&pHead,0));
	//Erase(&pHead,Find(&pHead,2));
	//PrintfDSList(&pHead);

	Insert(&pHead,Find(&pHead,2),10);
	//Insert(&pHead,Find(&pHead,3),11);
	//Insert(&pHead,Find(&pHead,3),12);


	PrintfDSList(&pHead);

}
int main()
{
	//Test1();
	//Test2();
	Test3();
	system("pause");
	return 0;
}