#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
//server

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]",argv[1]);
		return 1;
	}

	//创建套接字
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}
	//绑定
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));//转换成正确的网络字节序（大端）
	local.sin_addr.s_addr = inet_addr(argv[1]);//将字符串类型的数据转换成in_addr的类型

	if( bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		return 2;
	}

	//接收数据
	char buf[1024];
	struct sockaddr_in peer;
	socklen_t len = sizeof(struct sockaddr_in);
	while(1)
	{
		ssize_t s = recvfrom(sock, buf, sizeof(buf)-1, 0, \
					(struct sockaddr*)&peer, &len);
		if(s < 0)
		{
			perror("recvfrom");
			return 3;
		}
		else if (s == 0)
		{
			printf("client quit...\n");
		}
		else
		{
			printf("client# %s\n",buf);
		}
	}
	close(sock);
	return 0;
}
