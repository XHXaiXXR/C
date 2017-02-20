#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>

void* thread_run(void* arg)
{
	while(1)
	{
		sleep(2);
		printf("new thread, pid: %d, ppid: %d,tid: %lu\n",getpid(),getppid(),pthread_self());
	}
}

int main()
{
	printf("Pthread...\n");

	pthread_t tid;//线程ID
	int ret = pthread_create(&tid, NULL, thread_run, NULL);//第一个参数为指向线程ID的地址，第二个参数是设置线程的属性（一般不设置），第三个参数是一个返回值和参数都为（void*）的函数指针，第三个参数是传递给函数指针的参数。
	if(ret < 0)
	{
		perror("pthread_create");
		return -1;
	}
	
	int count = 5;
	while(count--)
	{
		sleep(1);
		printf("main thread, pid: %d, ppid: %d,tid: %lu\n",getpid(),getppid(),pthread_self());
	}

	pthread_join(tid, NULL);
	return 0;
}
