#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	printf("I am client...\n");
	
	int fd = open("./myfifo",O_WRONLY);//以只写的方式打开文件
	if(fd < 0)
	{
		//open fail
		perror("open");
		exit(1);
	}
	
	char buf[1024];
	while(1)
	{
		printf("please Enter# \n");
		fflush(stdout);
		memset(buf,'\0',sizeof(buf));
		ssize_t _s = read(0,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s] = '\0';
			write(fd,buf,strlen(buf));
		}
	}
	close(fd);
	return 0;
}
