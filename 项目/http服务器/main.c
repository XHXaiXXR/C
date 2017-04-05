#include"httpd.h"

void Usage(char* proc)
{
	printf("Usage: %s [local_ip] [local_port]\n", proc);
}

void* accept_request(void* arg)
{
	pthread_detach(pthread_self());			
	return (void* )handle_pthread(arg);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	int sock = strtup(argv[1], argv[2]);

	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	while(1)
	{
		int fd = accept(sock, (struct sockaddr*)&peer, &len);	
		if(fd < 0)
		{
			printf_log("accept",WARNING);
			exit(2);
		}

		//链接成功
		printf("get a new cliend# [ip]:%s [port]:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));

		pthread_t tid;
		int ret = pthread_create(&tid, NULL, accept_request, (void*)fd);
		if(ret != 0)
		{
			printf_log("pthread_create", FATAL);
		}
	}
	return 0;
}
