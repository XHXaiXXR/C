#include"comm.h"

int main()
{
	printf("I am client...\n");

	int msg_id = GetMsgQueue();
	
	char buf[MYSIZE];
	char out[2*MYSIZE];

	while(1)
	{
		printf("Please Enther:");
		fflush(stdout);

		ssize_t _s = read(0,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s] = '\0';
			SendMessage(msg_id,CLIENT_TYPE,buf);
		}

		if(RecvMessage(msg_id,SERVER_TYPE,out) < 0)
		{
			break;
		}

		//收到回显的消息
		printf("server echo# %s\n",out);
	}
	return 0;
}
