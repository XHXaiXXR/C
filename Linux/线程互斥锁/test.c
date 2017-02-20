#include<stdio.h>
#include<pthread.h>

int count = 0;

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void* thread_run1(void* arg)
{
	int i = 0;
	int val = 0;
	for(;i < 5000;i++)
	{
		//进临界区时加锁
		pthread_mutex_lock(&mylock);
		
		//临界区
		val = count;
		printf("tid : %lu,count : %d\n",pthread_self(),count);
		count = val + 1;
		
		//出临界区时解锁
		pthread_mutex_unlock(&mylock);
	}
}

void* thread_run2(void* arg)
{
	int i = 0;
	int val = 0;
	for(;i < 5000;i++)
	{
		//进临界区时加锁
		pthread_mutex_lock(&mylock);

		//临界区
		val = count;
		printf("tid : %lu,count : %d\n",pthread_self(),count);
		count = val + 1;
		
		//出临界区时解锁
		pthread_mutex_unlock(&mylock);
	}
}

int main()
{
	printf("Lock...\n");
	
	//线程ID
	pthread_t tid1;	
	pthread_t tid2;

	//创建线程
	pthread_create(&tid1, NULL, thread_run1, NULL);
	pthread_create(&tid2, NULL, thread_run2, NULL);

	//等待新线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("count = %d\n",count);

	//销毁锁
	pthread_mutex_destroy(&mylock);
	return 0;
}
