#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	umask(0);
	int fd = open("./log",O_WRONLY | O_CREAT, 0644);

	close(1);
	//int newfd = dup(fd);
	int newfd = dup2(fd,1);

	printf("fd = %d\nnewfd = %d\n",fd,newfd);
	char* msg = "hello";

	int count = 0;
	while(count++ <= 10)
	{
		printf("%s	%d\n",msg,count);
	}
	return 0;
}
