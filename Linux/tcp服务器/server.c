#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/wait.h>
//Server...

//启动，返回值是一个监听套接字
int Startup(const char* addr,const char* port)
{
	//(1)创建套接字
	//socket(当前域(默认是AF_INET),流式套接(默认SOCKET_STREAM),(默认为0)),出错返回-1，否则返回新的文件描述符（默认从3开始）	
	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if( listen_sock < 0)
	{
		//创建失败
		perror("socket");
		exit(1);//直接错误退出
	}
	
	//（2）绑定	
	struct sockaddr_in local;
	local.sin_family = AF_INET;//协议家族
	local.sin_port = htons(atoi(port));//端口号
	local.sin_addr.s_addr = inet_addr(addr);//IP地址
	
	//bind(文件描述符,socket的抽象数据类型的结构体,结构体的长度)，出错返回返回-1
	if( bind(listen_sock, (struct sockaddr* )&local, sizeof(local)) < 0 )
	{
		//绑定失败
		perror("bind");
		exit(2);
	}

	//（3）监听
	//listen（文件描述符，长度一般为5-8），出错返回-1
	if( listen( listen_sock, 5) < 0)
	{
		//监听失败
		perror("listen");
		exit(3);
	}

	return listen_sock;
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("%s [IP_Addr] [Port]\n",argv[0]);
		return 0;
	}
	int listen_sock = Startup(argv[1], argv[2]);	
	printf("listen_sock = %d\n",listen_sock);
	
	//对端套接字
	struct sockaddr_in remote;
	int len = sizeof(struct sockaddr);

	//（4）监听（接收）新的链接请求，用于数据通信
	while(1)
	{
		//建立新的链接
		int fd = accept(listen_sock, (struct sockaddr*)&remote, &len);
		if(fd < 0)
		{
			perror("accept");
			continue;
		}

		pid_t id = fork();
		if(id < 0)
		{
			perror("fork");
			return 1;
		}
		else if(id == 0)
		{
			//child
			
			if(fork() > 0)
			{
				exit(1);
			}

			while(1)
			{
				char buf[1024] = {0};
				ssize_t _s = read(fd, buf, sizeof(buf)-1);
				if(_s > 0)
				{
					printf("client#	%s\n",buf);
				}
				else if(_s == 0)
				{
					printf("client print end...\n");
					break;
				}
				else
				{
					perror("read");
				}
			}
			close(fd);
		}
		else
		{
			//father
			close(fd);
			//waitpid(-1, NULL, WNOHANG);
		}
	}
		
	return 0;
}












