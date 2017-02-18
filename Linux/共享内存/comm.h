#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."//当前路径
#define PROJID 0X6666
#define NUM 1
#define SIZE (4096 * (NUM))

//创建共享内存
int CreateShm();
//获取共享内存
int GetShm();
//将共享内存挂接到指定内存
void* AtShm(int shm_id);
//去关联
int DtShm(const void* shmaddr);
//销毁共享内存
int DestoryShm(int shm_id);


#endif //__COMM_H__
