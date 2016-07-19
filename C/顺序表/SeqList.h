#ifndef __SEQLIST_H__//防止重定义
#define __SEQLIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define  MAX 5
typedef int DataType;//typedef语句后面要有一个分号；

typedef struct SeqList
{
	DataType Data[MAX];
	int size;
}SeqList,*pSeqList;

//初始化
void InitSeqList(pSeqList pSeq);
//打印
void PrintSeqList(pSeqList pSeq);
//尾插法
void PushBack(pSeqList pSeq,DataType x);
//尾删法
void PopBack(pSeqList pSeq);
//头插法
void PushFront(pSeqList pSeq,DataType x);
//头删法
void PopFront(pSeqList pSeq);
//查找某个数据在顺序表中的位置
int Find(pSeqList pSeq,DataType x);
//在某个下标中插入一个数据
void Insert(pSeqList pSeq,int pos,DataType x);
//删除x的数据
void Remove(pSeqList pSeq,DataType x);
//删除所有x的数据
void RemoveAll(pSeqList pSeq,DataType x);
//升序排序顺序表
void Sort(pSeqList pSeq);
//二分查找
int BinarySearch(pSeqList pSeq,DataType x);
//删除下标为pos的数据
void Erase(pSeqList pSeq,size_t pos);
//选择排序
void SelectSort(pSeqList pSeq);
#endif  //__SEQLIST_H__