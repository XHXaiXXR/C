#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [server_ip] [server_port]",argv[0]);
		return 1;
	}
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
		exit(2);
	}
	
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock, (struct sockaddr*)&server,sizeof(server)) < 0)
	{
		perror("connect");
		exit(3);
	}

	char buf[1024];
	while(1)
	{
		printf("Please Ether# ");
		fflush(stdout);

		ssize_t _s = read(0, buf,sizeof(buf)-1);
		if(_s < 0)
		{
			perror("read");
			continue;
		}
		else
		{
			buf[_s-1] = '\0';
			write(sock, buf, sizeof(buf)-1);
		}

	}
	colse(sock);
	return 0;
}
