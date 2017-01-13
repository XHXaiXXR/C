#include<iostream>
using namespace std;
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

void test()
{
	pid_t id = fork();
	int i = 0;

	if(id < 0)
	{
		//创子进程失败
		perror("fork");
	}
	else if(id == 0)
	{
		//fork()有两个返回值，若创建成功
		//子进程返回0
		//父进程返回子进程的PID
		while(++i)
		{
			cout<<"I am child	, pid : "<<getpid()<<", ppid : "<<getppid()<<", i = "<<i<<endl;
			sleep(1);
		}
	}
	else//id > 0 
	{
		//fork()有两个返回值，若创建成功
		//子进程返回0
		//父进程返回子进程的PID
		while(++i)
		{
			cout<<"I am father	, pid : "<<getpid()<<", ppid : "<<getppid()<<", i = "<<i<<endl;
			sleep(1);
		}
	}

}

int main()
{
	test();
	return 0;
}
