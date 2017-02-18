#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define PATHNAME "."//当前路径
#define PROJID 0X6666

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

//创建信号量集
int CreateSemSet(int nums);
//初始化信号量集
int InitSemSet();
//获取信号量集
int GetSemSet();
//P操作
int P(int sem_id, int which);
//V操作
int V(int sem_id,int which);
//销毁信号量集
int DestorySemSet(int sem_id);


#endif //__COMM_H__
