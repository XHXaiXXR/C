#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

int Startup(char* _ip,char* _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(_port));
	local.sin_addr.s_addr = inet_addr(_ip);
	
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}
	
	if( listen(sock, 5) < 0)
	{
		perror("lesten");
		exit(4);
	}

	return sock;
}

void* Run(void *arg)
{
	int sock = *((int*)arg);

	char buf[1024];
	while(1)
	{
		ssize_t _s = read(sock, buf, sizeof(buf)-1);
		if(_s == 0)
		{
			printf("client is quit...\n");
			break;
		}
		else if(_s > 0)
		{
			buf[_s] = '\0';
			printf("client# %s\n",buf);
		}
		else
		{
			perror("read");
			exit(5);
		}
	}
	close(sock);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]\n",argv[0]);
		return 1;
	}
	int listen_sock = Startup(argv[1],argv[2]);

	while(1)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(struct sockaddr_in);	
		
		int fd = accept(listen_sock, (struct sockaddr* )&peer, &len);
		if(fd < 0)
		{
			continue;
		}

		pthread_t tid;
		int ret = pthread_create(&tid, NULL, Run, &fd);
		if(ret != 0)
		{
			continue;
		}
	}



	return 0;
}
