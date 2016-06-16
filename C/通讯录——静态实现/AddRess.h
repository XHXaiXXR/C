#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define  MAX 10     //������Ϊ�˵��Է���ȡ��һ����С����ֵ
enum OP
{
	EXIT = 0,//�˳�
	ADD,     //������ϵ��
	DEL,     //ɾ����ϵ��
	SEEK,    //������ϵ��
	REVISE,  //�޸���ϵ��
	SHOW,    //��ʾ������ϵ��
	EMPTY,   //���������ϵ��
	SORT,    //����������������ϵ��
};
//�������Ա����䡢�绰��סַ
typedef struct PesonMessage
{
	char name[20];
	char sex[5];
	int age;
	char tel[15];
	char address[20];
}PesonMessage;

//ͨѶ¼��Ա�ṹ�壻
typedef struct Peson
{
	PesonMessage people[MAX];
	int size;//ͨѶ¼��ǰ����
	int capacity;//�绰������
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