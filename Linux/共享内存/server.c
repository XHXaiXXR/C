#include"comm.h"

int main()
{
	printf("I am Server...\n");
	
	int shm_id = CreateShm();
	char* mem = AtShm(shm_id);

	while(1)
	{
		sleep(1);
		printf("%s\n",mem);
	}

	DtShm(mem);

	//int shm_id = CreateShm();
	//sleep(2);
	//char* mem = (char*)AtShm(shm_id);
	//sleep(2);
	//DtShm(mem);
	//DestoryShm(shm_id);

	return 0;
}
