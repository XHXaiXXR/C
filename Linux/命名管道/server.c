#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	printf("I am server...\n");
	
	umask(0);//设置默认权限
	if( mkfifo("./myfifo",S_IFIFO | 0666) != 0 )
	{
		//fail
		perror("mkfifo");
		exit(1);
	}

	int fd = open("./myfifo",O_RDONLY);//以只读的方式打开文件
	if(fd < 0)
	{
		//open fail
		perror("open");
		exit(1);
	}
	
	char buf[1024];
	while(1)
	{
		printf("please waiting...\n");
		fflush(stdout);

		memset(buf,'\0',sizeof(buf));
		ssize_t _s = read(fd,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s] = '\0';
			printf("client# %s",buf);
		}
		else if(_s == 0)
		{
			printf("client quit...\n");
			break;
		}
		else
		{
			//fail
			perror("read");
			exit(1);
		}
	}
	close(fd);
	return 0;
}
