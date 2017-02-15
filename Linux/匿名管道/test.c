#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int fd[2] = {0};
	if( pipe(fd) != 0)
	{
		//pipe(fd) -> create pipe
		//success -> return 0    fail -> return -1
		perror("pipe");
		exit(1);
	}
	printf("fd[0] = %d\nfd[1] = %d\n",fd[0],fd[1]);
	
	pid_t id = fork();
	if(id == 0)
	{
		//child
		close(fd[0]);//close read port, only write
		
		const char* buf = "father,i see you";
		int count = 5;
		while(count--)
		{
			write(fd[1],buf,strlen(buf));
			sleep(1);
		}

		close(fd[1]);
		exit(0);
	}
	else if(id > 0)
	{
		//father
		close(fd[1]);//close write port, only read
		
		char line[1024] = {0};
		int count = 5;
		while(count--)
		{
			ssize_t _s = read(fd[0],line,sizeof(line)-1);
			if(_s > 0)
			{
				//success
				line[_s] = '\0';
				printf("child : %s\n",line);
			}
			else if(_s == 0)
			{
				break;
			}
			else
			{
				perror("read");
				exit(1);
			}
		}

		close(fd[0]);
		wait(NULL);
	}
	else
	{
		//fail
		perror("fork");
		exit(1);
	}
	return 0;
}
