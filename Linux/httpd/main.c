#include"httpd.h"

static void Usage(const char* arg)
{
	printf("Usage: %s [ip] [port]\n", arg);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	int listen_fd = Statup(argv[1], atoi(argv[2]));
	
	int epoll_fd = epoll_create(256);//创建一个指向事件表的句柄
	if(epoll_fd < 0)
	{
		perror("epoll_create");
		exit(5);
	}

	//向事件表中注册一个事件
	Addfd(epoll_fd, listen_fd);

	struct epoll_event evs[_SIZE_];//epoll_wait的第二个参数，用于存放由内核直接映射的就绪事件，是一个存放就绪事件的就绪队列

	while(1)
	{
		int num = 0;
		switch(num = epoll_wait(epoll_fd, evs, _SIZE_, 5000 ))//第三个参数是能够处理事务的个数，第四个参数是超时时间,5000就是5s。返回值num是就绪事件的个数
		{
		case 0:
			{
				printf("timeout....\n");//超时
			}
			break;
		case -1:
			{
				perror("epoll_wait");
			}
			break;
		default:
			{
				//轮询就绪队列
				int i = 0;
				for(; i < num; i++)
				{
					int fd = evs[i].data.fd;
					if(fd == listen_fd && (evs[i].events & EPOLLIN))
					{
						struct sockaddr_in cli;
						socklen_t len = sizeof(len);
						int connfd = accept(fd, (struct sockaddr*)&cli, &len);
						if(connfd < 0)
						{
							perror("accept");
							continue;
						}

						//连接成功，输出连接信息
						printf("get a new client: %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
						
						//向事件表中注册一个事件
						Addfd(epoll_fd, connfd);
					}
					else if(evs[i].events & EPOLLIN)
					{
						//两端连接成功，为每个连接创建一个线程，处理http请求
						pthread_t id;
						//创建线程
						pthread_create(&id, NULL, HandlerRequest, (void*)fd);
						//将线程设置成分离状态
						pthread_detach(id);
					}
					else
					{}
				}
			}
		}

	}
	
	return 0;
}
