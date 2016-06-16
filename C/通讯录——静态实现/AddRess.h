#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define  MAX 10     //这里我为了调试方便取了一个较小的数值
enum OP
{
	EXIT = 0,//退出
	ADD,     //增加联系人
	DEL,     //删除联系人
	SEEK,    //查找联系人
	REVISE,  //修改联系人
	SHOW,    //显示所有联系人
	EMPTY,   //清空所有联系人
	SORT,    //以名字排序所有联系人
};
//姓名、性别、年龄、电话、住址
typedef struct PesonMessage
{
	char name[20];
	char sex[5];
	int age;
	char tel[15];
	char address[20];
}PesonMessage;

//通讯录成员结构体；
typedef struct Peson
{
	PesonMessage people[MAX];
	int size;//通讯录当前人数
	int capacity;//电话本容量
}Peson,*pPeson;

void Print_AddRess();
void Add_AddRess(pPeson peson);
void Show_AddRess(pPeson peson);
void Empty_AddRess(pPeson peson);
void Del_AddRess(pPeson peson);
void Seek_AddRess(pPeson peson);
void Revise_AddRess(pPeson peson);
void Sort_AddRess(pPeson peson);
void Cheak(pPeson peson);
#endif//__ADDRESS_H__