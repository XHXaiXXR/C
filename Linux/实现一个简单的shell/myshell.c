#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
	while(1)
	{
		printf("[xhx@localhost myshell]# ");
		fflush(stdout);//刷新标准输出流
		
		char line[1024] = {0};
		ssize_t _s = read(0,line,sizeof(line));
		if(_s > 0)
		{
			//read success
			line[_s - 1] = '\0';
		}
		else
		{
			//read fail
			perror("read");
			continue;//again read
		}

		char* my_argv[10];
		int i = 1;
		char *start = line;
		my_argv[0] = start;
		while(*start)
		{
			if( isspace(*start) )
			{
				//*start == ' '
				*start = '\0';
				start++;
				my_argv[i++] = start;
			}
			else
			{
				start++;
			}
		}
		my_argv[i] = NULL;

		pid_t id = fork();//创建子进程
		if(id == 0)
		{
			//child
			execvp(my_argv[0],my_argv);
			perror("exit fail");
			exit(1);
		}
		else if(id > 0)
		{
			//father
			sleep(1);
			wait(NULL);
		}
		else
		{
			//fail
			perror("fork");	
		}
	}
	return 0;
}
