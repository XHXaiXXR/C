#include<stdio.h>
#include<pthread.h>

int val = 0;
pthread_rwlock_t myrw;

void* run_reader(void* arg)
{
	while(1)
	{
		//sleep(1);
		pthread_rwlock_rdlock(&myrw);//只读模式去加锁	
		printf("val = %d\n",val);
		pthread_rwlock_unlock(&myrw);	
	}
}

void* run_writer(void* arg)
{
	while(1)
	{
		sleep(1);
		pthread_rwlock_wrlock(&myrw);//只写模式去加锁	
		val++;
		pthread_rwlock_unlock(&myrw);	
	}
}

int main()
{
	printf("rwlock...\n");
	
	pthread_rwlock_init(&myrw, NULL);

	pthread_t reader;
	pthread_t writer;

	pthread_create(&reader, NULL, run_reader, NULL);
	pthread_create(&writer, NULL, run_writer, NULL);

	pthread_join(reader, NULL);
	pthread_join(writer, NULL);

	pthread_rwlock_destroy(&myrw);
	return 0;
}
