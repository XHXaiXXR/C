#ifndef __SListNode_H__
#define __SListNode_H__
#pragma once  //能够保证头文件只被编译一次
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int DataType;

typedef struct SListNode 
{
	DataType data;
	struct SListNode *_NextNode;
}SListNode,*PSListNode;

// 初始化单链表(对于无头结点单链表，该函数没有意义)
void InitList(PSListNode* pHead);
// 销毁单链表
void DestroyList(PSListNode* pHead);
// 尾插
void PushBack(PSListNode* pHead, DataType data);
// 尾出
void PopBack(PSListNode* pHead);
// 头插
void PushFront(PSListNode* pHead, DataType data);
// 头出
void PopFront(PSListNode* pHead);
// 在链表中查找元素data
PSListNode Find(PSListNode* pHead, DataType data);
// 删除pos位置的结点(注意不能用那种替换形式)
void  Erase(PSListNode* pHead, PSListNode pos);
// 在链表的pos位置插入元素data
void  Insert(PSListNode* pHead, PSListNode pos, DataType data);
//打印链表存放的数据
void PrintList(PSListNode* pHead);
//写一个单链表的冒泡排序
void BubblingSort(PSListNode* pHead);
//删除一个无头链表的非尾结点
void EraseNotHead(PSListNode pos);
//反转（逆置）链表
void ReverseLish(PSListNode* pHead);
//(无头单链表)在当前节点前插入一个节点
void InsertFrontNode(PSListNode pos,DataType data);
//只遍历一遍，查找链表的中间结点
PSListNode FindMidNode(PSListNode* pHead);
//删除倒数第k个结点(k>1 && k<总长度)
void DelKNode(PSListNode* pHead,int k);

#endif//__SListNode_H__