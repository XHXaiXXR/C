#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>

#define PATHNAME "."//当前路径 
#define PROJID 0x6666//设置权限
#define MYSIZE 128
#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
	long mtype;
	char mtext[MYSIZE];
};


int CreateMsgQueue();
int GetMsgQueue();
int SendMessage(int msg_id, long type,const char *msg);
int RecvMessage(int msg_id, int type, char out[]);
int DestoryMsgQueue(int msg_id);

#endif //__COMM_H__
