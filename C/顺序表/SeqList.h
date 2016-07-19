#ifndef __SEQLIST_H__//��ֹ�ض���
#define __SEQLIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define  MAX 5
typedef int DataType;//typedef������Ҫ��һ���ֺţ�

typedef struct SeqList
{
	DataType Data[MAX];
	int size;
}SeqList,*pSeqList;

//��ʼ��
void InitSeqList(pSeqList pSeq);
//��ӡ
void PrintSeqList(pSeqList pSeq);
//β�巨
void PushBack(pSeqList pSeq,DataType x);
//βɾ��
void PopBack(pSeqList pSeq);
//ͷ�巨
void PushFront(pSeqList pSeq,DataType x);
//ͷɾ��
void PopFront(pSeqList pSeq);
//����ĳ��������˳����е�λ��
int Find(pSeqList pSeq,DataType x);
//��ĳ���±��в���һ������
void Insert(pSeqList pSeq,int pos,DataType x);
//ɾ��x������
void Remove(pSeqList pSeq,DataType x);
//ɾ������x������
void RemoveAll(pSeqList pSeq,DataType x);
//��������˳���
void Sort(pSeqList pSeq);
//���ֲ���
int BinarySearch(pSeqList pSeq,DataType x);
//ɾ���±�Ϊpos������
void Erase(pSeqList pSeq,size_t pos);
//ѡ������
void SelectSort(pSeqList pSeq);
#endif  //__SEQLIST_H__