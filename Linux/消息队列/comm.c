#include"comm.h"

int CommMsgQueue(int type)
{
	key_t _k = ftok(PATHNAME,PROJID);
	if(_k < 0)
	{
		perror("ftok");
		return -1; 
	}

	int msg_id = msgget(_k, type);//获取消息
	if(msg_id < 0)
	{
		perror("msgget");
		return -2;
	}

	return msg_id;
}

int CreateMsgQueue()
{
	return CommMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}

int GetMsgQueue()
{
	return CommMsgQueue(IPC_CREAT);
}

int SendMessage(int msg_id, long type,const char *msg)
{
	struct msgbuf buf;
	buf.mtype = type;
	strcpy(buf.mtext,msg);
	
	int ret = msgsnd(msg_id, &buf, sizeof(buf.mtext), 0);
	if(ret < 0)
	{
		perror("msgsnd");
		return -4;
	}

	return 0;
}

int RecvMessage(int msg_id, int type, char out[])
{	
	struct msgbuf buf;
	int size = msgrcv(msg_id, &buf, sizeof(buf.mtext),type,0);
	
	if(size < 0)
	{
		perror("msgrcv");
		return -5;
	}

	strncpy(out, buf.mtext, size);
	return 0;
}


int DestoryMsgQueue(int msg_id)
{
	if( msgctl(msg_id, IPC_RMID, NULL) < 0 )
	{
		perror("msgctl");
		return -3;
	}

	return 0;
}














