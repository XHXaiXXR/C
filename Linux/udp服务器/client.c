#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
//client

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [server_ip] [server_port]",argv[1]);
		return 1;
	}

	//创建套接字
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}
	
	//发送数据
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));//转换成正确的网络字节序（大端）
	server.sin_addr.s_addr = inet_addr(argv[1]);//将字符串类型的数据转换成in_addr的类型
	socklen_t len = sizeof(struct sockaddr_in);

	char buf[1024];
	while(1)
	{
		printf("Please Enter: ");
		fflush(stdout);
		
		ssize_t _s = read(0, buf, sizeof(buf)-1);
		if(_s < 0)
		{
			perror("read");
			return 3;
		}
		else
		{
			buf[_s-1] = '\0';
			ssize_t s = sendto(sock, buf, sizeof(buf)-1, 0, \
					(struct sockaddr*)&server, len);

			if(s < 0)
			{
				perror("sendto");
				return 4;
			}
		}
	}
	close(sock);
	return 0;
}
