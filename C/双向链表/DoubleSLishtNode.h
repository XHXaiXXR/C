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

//��ʼ��˫������
void InitDSList(PDoubleSListNode* pHead);
//��ӡ˫������
void PrintfDSList(PDoubleSListNode* pHead);
//���ٽ���ڴ�
PDoubleSListNode ByeNode(DataType data);
//β�巨
void PushBack(PDoubleSListNode* pHead,DataType data);
//βɾ��
void PopBack(PDoubleSListNode* pHead);
//ͷ�巨
void PushFront(PDoubleSListNode* pHead,DataType data);
//ͷɾ��
void PopFront(PDoubleSListNode* pHead);
//��˫�������в���һ��Ԫ��
PDoubleSListNode Find(PDoubleSListNode* pHead,DataType x);
//ɾ��posλ���ϵĽ��
void Erase(PDoubleSListNode* pHead,PDoubleSListNode pos);
//��˫�������posλ�ò���x
void Insert(PDoubleSListNode* pHead,PDoubleSListNode pos,DataType x);
#endif//__DOUBLESLISTNODE_H__