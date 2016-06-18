#ifndef __DOUBLESLISTNODE_H__
#define __DOUBLESLISTNODE_H__
#pragma once;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int DataType;

typedef struct DoubleSListNode
{
	DataType data;
	struct DoubleSListNode *_LeftNode;
	struct DoubleSListNode *_RightNode;
}DoubleSListNode,*PDoubleSListNode;

//初始化双向链表
void InitDSList(PDoubleSListNode* pHead);
//打印双向链表
void PrintfDSList(PDoubleSListNode* pHead);
//开辟结点内存
PDoubleSListNode ByeNode(DataType data);
//尾插法
void PushBack(PDoubleSListNode* pHead,DataType data);
//尾删法
void PopBack(PDoubleSListNode* pHead);
//头插法
void PushFront(PDoubleSListNode* pHead,DataType data);
//头删法
void PopFront(PDoubleSListNode* pHead);
//在双向链表中查找一个元素
PDoubleSListNode Find(PDoubleSListNode* pHead,DataType x);
//删除pos位置上的结点
void Erase(PDoubleSListNode* pHead,PDoubleSListNode pos);
//在双向链表的pos位置插入x
void Insert(PDoubleSListNode* pHead,PDoubleSListNode pos,DataType x);
#endif//__DOUBLESLISTNODE_H__