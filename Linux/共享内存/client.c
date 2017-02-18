#include"comm.h"

int main()
{
	printf("I am Client...\n");
	
	int shm_id = GetShm();
	char* mem = AtShm(shm_id);

	int i = 0;
	while(1)
	{
		sleep(1);
		mem[i++] = 'A';
		i %= (SIZE-1);
		mem[i] = '\0';
	}

	DtShm(mem);

	return 0;
}
