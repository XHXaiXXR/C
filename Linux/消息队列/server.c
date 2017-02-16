#include"comm.h"

int main()
{
	printf("I am Server...\n");

	int msg_id = CreateMsgQueue();

	char buf[2*MYSIZE];
	while(1)
	{
		sleep(20);
		if(RecvMessage(msg_id, CLIENT_TYPE, buf) < 0)
		{
			//接收来自client的消息，出错重新读取
			break;
		}
		
		//接收成功
		printf("client# %s\n",buf);

		//将消息重新发送给client（回显）
		if(SendMessage(msg_id,SERVER_TYPE,buf) < 0)
		{
			break;
		}
	}

	if( DestoryMsgQueue(msg_id) == 0)
	{
		printf("destory success...\n");
	}
	return 0;
}
