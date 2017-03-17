#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>

#define _SIZE_ 1024
int gfds[_SIZE_];

int startup(char* _ip,char* _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
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
		perror("bing");
		exit(2);
	}
	
	if(listen(sock, 5) < 0)
	{
		perror("listen");
		exit(3);
	}

	return sock;
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port] \n",argv[0]);
		exit(4);
	}

	int listen_sock = startup(argv[1],argv[2]);
	
	//将存放文件描述符的数组初始化为无效，并且0下标的位置上放listen_sock
	int i = 0;
	for(;i < _SIZE_;i++)
	{
		gfds[i] = -1;
	}
	
	while(1)
	{
		//设置rfds只读文件描述符集，由于rfds是一个输入输出型的变量，所以每次都要重新初始化，以免上次的结果对新一次的操作产生影响
		fd_set rfds;
		FD_ZERO(&rfds);//将只读文件描述符全部清空
		FD_SET(listen_sock, &rfds);//将监听套接字设置进只读文件描述符集当中

		gfds[0] = listen_sock;
		
		int max_fd = -1;
		int j = 0;
		for(;j < _SIZE_;j++)
		{
			if(gfds[j] > 0)//文件描述符数组当中文件描述符是否有效
			{
				//有效的话，要将新的文件描述符设置进只读文件描述符集当中
				FD_SET(gfds[j], &rfds);

				//还要记得每次更新最大文件描述符的值
				if(max_fd < gfds[j])
				{
					max_fd = gfds[j];
				}
			}
		}

		struct timeval timeout = {0, 0};//设置轮寻的时间为5秒	
		//select（最大文件描述符的值+1， 只读文件描述符集，只写文件描述符集，异常错误文件描述符集，设置超时时间）
		switch(select(max_fd+1, &rfds, NULL, NULL, NULL/*&timeout*/))
		{
			case 0:
				{
					printf("timeout...\n");
				}
				break;
			case -1:
				{
					perror("select");
					exit(5);
				}
				break;
			default:
				{
					int k = 0;
					for(;k < _SIZE_;k++)
					{
						if(k== 0 && FD_ISSET(listen_sock, &rfds))
						{
							//监听到连接请求，进行三次握手
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							

							int new_fd = accept(listen_sock, (struct sockaddr*)&peer, &len);

							if(new_fd < 0)
							{
								perror("accept");
								exit(6);
							}

							printf("get a client: %s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
							//要将新的文件描述符放进全局的文件描述符数组中以便记录
							int m = 0;
							for(;m < _SIZE_;m++)
							{
							printf("this....\n");
								//找一个最小的无效的位置放进新的文件描述符
								if(gfds[m] == -1)
								{
									gfds[i] = new_fd;
									break;
								}
							}
							
							//会有已经没有位置存放的情况，这时候我们应该把放不进的新的文件描述符给关掉
							if(m == _SIZE_)
							{
								close(new_fd);
							}

							printf("1....\n");
						}
						else if(FD_ISSET(gfds[i], &rfds))
						{
							printf("2...\n");
							char buf[1024];
							ssize_t _s = read(gfds[i], buf,sizeof(buf)-1);

							if(_s > 0)
							{
								buf[_s] = '\0';
								printf("client# %s\n",buf);
							}
							else if(_s == 0)
							{
								//对端已经退出
								printf("client is quit...\n");
								//这时候需要将对应的文件描述符关闭
								close(gfds[k]);
								//全局的文件描述符数组中相应位置也需要设置成无效
								gfds[k] = -1;
							}
							else
							{
								perror("read");
							}
						}
						printf("3...\n");
					}
				}
				break;
		}
	}

	return 0;
}











