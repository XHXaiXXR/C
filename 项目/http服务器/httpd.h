#ifndef _HTTPD_H_
#define _HTTPD_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<assert.h>
#include<unistd.h>
#include<fcntl.h>

#define NORMAL 0
#define WARNING 1
#define FATAL 2
#define _SIZE_ 4096

int strtup(const char* _ip, const char* _port);
void printf_log(const char* mather, int rank);
int handle_pthread(void* arg);
int get_line(int sock, char* buf, int len);
void clear_hander();
void echo_www();
void echo_errno();

#endif //_HTTPD_H_
