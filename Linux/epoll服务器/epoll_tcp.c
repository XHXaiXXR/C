#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>

#define _SIZE_ 1024

int statup(char* _ip, char* _port)
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
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if(bind(sock, (struct sockaddr*)&local, sizeof(local))< 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0)
	{
		perror("listen");
		exit(4);
	}

	return sock;
}

typedef struct epbuf_t
{
	int _fd;
	char _buf[1024];
}epbuf_t, *epbuf_p, **epbuf_pp;

static epbuf_p Alloc(int fd)
{
	epbuf_p ptr = (epbuf_p)malloc(sizeof(epbuf_t));
	if(NULL == ptr)
	{
		exit(6);
	}
	ptr->_fd = fd;

	return ptr;
}
static void Free(epbuf_p ptr)
{
	if(NULL != ptr)
	{
		free(ptr);
		ptr = NULL;
	}

	return;
}
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [local_ip] [local_port]",argv[0]);
		exit(1);
	}

	int listen_sock = statup(argv[1],argv[2]);
	printf("listen_sock = %d\n",listen_sock);
	
	int epfd = epoll_create(256);
	if(epfd < 0)
	{
		perror("epoll_create");
		exit(5);
	}
	
	//一个存放事件的红黑树
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = Alloc(listen_sock);
	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);//将事件添加进红黑树中
	
	//就绪队列，存放就绪事件
	struct epoll_event evs[_SIZE_];
	
	int num = 0;
	int maxevents = _SIZE_;
	int timeout = 5000;//5s
	while(1)
	{
		switch( num = epoll_wait(epfd, evs, maxevents,timeout))
		{
		case 0:
			printf("timeout...\n");
			break;
		case -1:
			perror("epoll_wait");
			break;
		default:
			{
				int i = 0;
				for(;i < num;i++)
				{
					printf("i = %d\n",i);
					int fd = ((epbuf_p)(evs[i].data.ptr))->_fd;

					if(fd == listen_sock && (evs[i].events & EPOLLIN))
					{
						//监听到新链接
						struct sockaddr_in peer;
						socklen_t len = sizeof(peer);

						int new_fd = accept(fd, (struct sockaddr*)&peer, &len);//fd == listen_sock
						if(new_fd < 0)
						{
							perror("accept");
							exit(6);
						}

						//链接成功
						printf("get new client : %s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
						
						ev.events = EPOLLIN | EPOLLET;//et 边缘触发
						ev.data.ptr = Alloc(new_fd);
						epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &ev);
					}
					else if(fd != listen_sock && (evs[i].events & EPOLLIN))
					{
						char* buf = ((epbuf_p)(evs[i].data.ptr))->_buf;

						ssize_t _s = read(fd, buf, sizeof(buf)-1);
						if(_s < 0)
						{
							perror("read");
							exit(7);
						}
						else if(_s == 0)
						{
							printf("client quit...\n");
							close(fd);

							Free((epbuf_p)(evs[i].data.ptr));
							evs[i].data.ptr = NULL;
							epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
						}
						else
						{
							//读成功
							buf[_s] = '\0';
							printf("client# %s\n",buf);

							//回显
							ev.events = EPOLLOUT | EPOLLET;
							epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);//修改事件
						}
					}
					else if(fd != listen_sock && (evs[i].events & EPOLLOUT))
					{
						const char* msg = "HTTP/1.0 200 OK\r\n\r\n<html><h1>Haixia Xiao</h1></html>\n";
						write(fd, msg, strlen(msg));
						
						//写完以后就立即关闭该文件描述符
						Free((epbuf_p)(evs[i].data.ptr));
						evs[i].data.ptr = NULL;
						epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);

						close(fd);
					}
					else
					{
						printf("other...\n");
						//other thing
					}
				}
			}//default
			break;
		}//switch
	}//while

	return 0;
}
