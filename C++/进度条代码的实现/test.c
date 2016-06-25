#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

void proc()
{
	int i = 0;
	char proc_buf[102];
	const char* lable = "\|-\\";
	memset(proc_buf,'\0',sizeof(proc_buf));
	while (i <= 100)
	{
		printf("[%-101s][%d%%](%c)\r",proc_buf,i,lable[i%4]);
		fflush(stdout);
		proc_buf[i] = '=';
		i++;
		Sleep(100);
	}
}

int main()
{
	proc();
	system("pause");
	return 0;
}