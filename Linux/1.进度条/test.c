#include<stdio.h>
#include<string.h>

void proc()
{
	int i = 0;
	char proc_buf[102];
	const char* latle = "|/-\\";

	memset(proc_buf,'\0',sizeof(proc_buf));

	while(i <= 100)
	{
		printf("[%-100s][%d%%][%c]\r",proc_buf,i,latle[i % 4]);
		fflush(stdout);
		proc_buf[i] = '=';
		i++;
		usleep(100000);
	}
	printf("\n");
}

int main()
{
	proc();
	return 0;
}