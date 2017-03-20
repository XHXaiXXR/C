#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include <arpa/inet.h>

//client...

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usuge: %s [IP_Addr] [Post]\n",argv[0]);
		return 4;
	}
	//(1)创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}
	
	//(2)链接
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	//connect是以阻塞的方式链接的,出错返回-1
	if( connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0 )
	{
		//链接失败
		perror("connect");
		return 2;
	}

	//链接成功
	while(1)
	{
		char buf[1024] = {0};
		printf("Please Enter:");
		fflush(stdout);
		ssize_t _s = read(0, buf, sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s-1] = '\0';
			write(sock, buf, sizeof(buf)-1);
		}
		else
		{
			perror("read");
			exit(3);
		}
	}
	close(sock);
	return 0;
}












