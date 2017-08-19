#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int sig)
{
}

int my_sleep(int time)
{
	struct sigaction act,oact;
	act.sa_handler = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGALRM, &act, &oact);
	alarm(time);
	pause();
	
	int timeout = alarm(0);
	sigaction(SIGALRM, &oact, NULL);
	return timeout;
}

int main()
{
	while(1)
	{
		printf("hello\n");
		my_sleep(3);
	}
	return 0;
}

