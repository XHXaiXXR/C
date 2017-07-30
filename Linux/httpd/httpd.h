#ifndef __HTTPD_H__
#define __HTTPD_H__

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<sys/fcntl.h>
#include<pthread.h>
#include<string.h>
#include<sys/stat.h>

#define SIZE 1024
#define _SIZE_ 1024

int Statup(char* ip, int port);
int SetNonBlocking(int fd);
void Addfd(int epollfd, int fd);
int GetLine(int fd, char buf[], int len);
void* HandlerRequest(void* arg);
void EchoClient(int nums);
void ClearHead(int fd);
void EchoWww(int fd, char* path, int size);
void ExecCgi(int fd, const char* path, const char* method, const char*query_string);		

#endif //__HTTPD_H__
