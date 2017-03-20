#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<poll.h>
#include<unistd.h>

#define _SIZE_ 128

int statup(char* _ip,char* _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(_port));
	local.sin_addr.s_addr = inet_addr(_ip);

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(2);
	}

	if(listen(sock, 5) < 0)
	{
		perror("listen");
		exit(3);
	}

	return sock;
}


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]\n",argv[0]);
		exit(4);
	}

	//设置监听套接字
	int listen_sock = statup(argv[1], argv[2]);
	printf("listen_sock = %d \n",listen_sock);

	//初始化poll结构体
	struct pollfd fds[_SIZE_];
	int i = 0;
	for(; i < _SIZE_; i++)
	{
		fds[i].fd = -1;
		fds[i].events = 0;
		fds[i].revents = 0;
	}
	
	fds[0].fd = listen_sock;
	fds[0].events = POLLIN;

	while(1)
	{
		int timeout = 5000;//5秒，毫秒为单位
		switch(poll(fds, _SIZE_, timeout))
		{
		case 0:
			printf("timeout...\n");
			break;
		case -1:
			perror("poll");
			break;
		default:
		{
			int j = 0;
			for(; j < _SIZE_; j++)
			{
				if(fds[i].fd < 0)
				{
					continue;
				}
				if((j == 0) && (fds[j].revents & POLLIN))
				{
					//监听到一个新链接
					struct sockaddr_in peer;
					socklen_t len = sizeof(peer);

					int new_sock = accept(listen_sock, (struct sockaddr*)&peer,&len);
					if(new_sock < 0)
					{
						perror("accept");
						exit(5);
					}

					printf("get new client# %s:%d\n",inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
				
					//将监听到的套接字赋到poll结构体中
					int k = 0;
					for(; k < _SIZE_; k++)
					{
						if(fds[k].fd < 0)
						{
							fds[k].fd = new_sock;
							fds[k].events = POLLIN;
							break;
						}
					}

					if(k == _SIZE_)
					{
						printf("full...\n");
						close(new_sock);
					}
				}//if
				else if(fds[j].revents & POLLIN)
				{
					char buf[1024];
					ssize_t _s = read(fds[j].fd, buf, sizeof(buf)-1);

					if(_s > 0)
					{
						buf[_s-1] = '\0';
						printf("client# %s\n",buf);
					}
					else if(_s == 0)
					{
						printf("client is quit...\n");
						close(fds[j].fd);
						
						fds[j].fd = -1;
						fds[j].events = 0;
						fds[j].revents = 0;
					}
					else
					{
						perror("read");
						exit(6);
					}
				}//else if
			}
		}//default
			break;
		}//switch
	}


	return 0;
}
