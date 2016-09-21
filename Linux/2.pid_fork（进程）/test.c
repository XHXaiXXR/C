#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int g_val = 10;
void test1()
{
	pid_t id = fork();

	if(id < 0)
	{
		//fork error
		printf("fork error\n");
	}
	else if(id == 0)
	{
		//child
		g_val = 200;
		printf("child , pid : %d, ppid : %d, g_val = %d, &g_val = %p\n",getpid(),getppid(),g_val,&g_val);
	}
	else
	{
		//father
		sleep(3);
		printf("father , pid : %d, ppid = %d,g_val = %d, &g_val = %p\n",getpid(),getppid(),g_val,&g_val);
		}
}
void test()
{
	while(1)
	{
		printf("I am a process\n");
		printf("my id is: %d, father id is: %d\n",getpid(),getppid());
		printf("=======================================================\n");
		sleep(1);
	}
}
int main()
{
	test1();
	return 0;
}