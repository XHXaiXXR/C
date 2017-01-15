#include<iostream>
using namespace std;
#include<sys/types.h>
#include<sys/wait.h>

void test()
{
	pid_t id = fork();

	if(id == 0)
	{
		//child
		int count = 10;
		
		while(count--)
		{
			cout<<"I am child	: "<<getpid()<<" , ppid : "<<getppid()<<endl;
			sleep(1);
		}
	}
	else if(id > 0)
	{
		//father
		int count = 5;

		while(count--)
		{
			cout<<"I am father	: "<<getpid()<<" , ppid : "<<getppid()<<endl;
			sleep(1);
		}
		
		//进程等待(阻塞等待)函数pid_t wait(int* status);
		//参数：参数为输出型参数，获取子进程的退出状态，不关心则设置成NULL
		pid_t ret = wait(NULL);

		if(ret < 0)
		{
			//失败返回-1
			//等待失败，继续等待
			cout<<"waiting..."<<endl;
		}
		else
		{
			//成功返回被等待进程的PID
			//等待成功，父进程退出等待
			cout<<"wait is success"<<endl;
		}
	}
}
int main()
{
	test();
	return 0;
}
