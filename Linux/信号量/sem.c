#include"comm.h"
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	printf("sem...\n");
		
	int sem_id = CreateSemSet(1);
	InitSemSet(sem_id,0);	
	
	pid_t id = fork();//创建子进程
	if(id == 0)
	{
		//child proc
		while(1)
		{
			P(sem_id, 0);

			printf("A");
			fflush(stdout);
			usleep(10000);
			printf("A");
			fflush(stdout);
			usleep(10000);

			V(sem_id, 0);
		}
	}
	else if(id > 0)
	{
		//father proc
		while(1)
		{
			P(sem_id, 0);

			printf("B");
			fflush(stdout);
			usleep(10000);
			printf("B");
			fflush(stdout);
			usleep(10000);
		
			V(sem_id, 0);
		}
		wait(NULL);
	}
	else
	{
		//fail
		perror("fork");
		exit(0);
	}

	DestorySemSet(sem_id);

	return 0;
}
