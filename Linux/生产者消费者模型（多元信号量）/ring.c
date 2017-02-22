#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

#define _SIZE_ 5

int buf[_SIZE_] = {0};
sem_t blanks;//环形队列的格子
sem_t datas;//环形队列的数据

void* thread_product(void* arg)
{
	int i = 0;
	while(1)
	{
		sleep(1);//生产者sleep（1），消费者不sleeep.现象：生产一次，消费一次
		sem_wait(&blanks);//P -> blanks--

		int data = rand() % 1234;
		buf[i++] = data;
		i %= _SIZE_;
		printf("product done, data : %d\n",data);

		sem_post(&datas);//V -> datas++
	}
}

void* thread_consumer(void* arg)
{
	int i = 0;
	while(1)
	{
		//sleep(1);//消费者sleep（1）生产者没有sleep。现象：先在环形队列中生产满数据，再消费一次，生产一次
		sem_wait(&datas);//P -> datas--

		int data = buf[i++];
		i %= _SIZE_;
		printf("consumer done, data : %d\n",data);

		sem_post(&blanks);//V -> blanks++
	}
}

int main()
{
	printf("ring...\n");
	
	sem_init(&blanks, 0, _SIZE_);
	sem_init(&datas, 0, 0);

	pthread_t product;
	pthread_t consumer;
	
	pthread_create(&product, NULL, thread_product, NULL);
	pthread_create(&consumer, NULL, thread_consumer, NULL);

	pthread_join(product, NULL);
	pthread_join(consumer, NULL);
	
	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;
}
