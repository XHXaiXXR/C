#ifndef __SListNode_H__
#define __SListNode_H__
#pragma once  //�ܹ���֤ͷ�ļ�ֻ������һ��
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int DataType;

typedef struct SListNode 
{
	DataType data;
	struct SListNode *_NextNode;
}SListNode,*PSListNode;

// ��ʼ��������(������ͷ��㵥�����ú���û������)
void InitList(PSListNode* pHead);
// ���ٵ�����
void DestroyList(PSListNode* pHead);
// β��
void PushBack(PSListNode* pHead, DataType data);
// β��
void PopBack(PSListNode* pHead);
// ͷ��
void PushFront(PSListNode* pHead, DataType data);
// ͷ��
void PopFront(PSListNode* pHead);
// �������в���Ԫ��data
PSListNode Find(PSListNode* pHead, DataType data);
// ɾ��posλ�õĽ��(ע�ⲻ���������滻��ʽ)
void  Erase(PSListNode* pHead, PSListNode pos);
// �������posλ�ò���Ԫ��data
void  Insert(PSListNode* pHead, PSListNode pos, DataType data);
//��ӡ�����ŵ�����
void PrintList(PSListNode* pHead);
//дһ���������ð������
void BubblingSort(PSListNode* pHead);
//ɾ��һ����ͷ����ķ�β���
void EraseNotHead(PSListNode pos);
//��ת�����ã�����
void ReverseLish(PSListNode* pHead);
//(��ͷ������)�ڵ�ǰ�ڵ�ǰ����һ���ڵ�
void InsertFrontNode(PSListNode pos,DataType data);
//ֻ����һ�飬����������м���
PSListNode FindMidNode(PSListNode* pHead);
//ɾ��������k�����(k>1 && k<�ܳ���)
void DelKNode(PSListNode* pHead,int k);

#endif//__SListNode_H__