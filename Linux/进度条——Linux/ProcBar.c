#include"ProcBar.h"
#include<unistd.h>

void Proc()
{
	char proc[102];
	const char* table = "|/-\\";
	int i = 0;

	while(i <= 100)
	{
		printf("[%-100s][%d\%][%c]\r",proc,i,table[i%4]);
		fflush(stdout);
		proc[i++] = '=';
		proc[i] = '\0';

		usleep(100000);
	}
	printf("\n");
}
