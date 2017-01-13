#include<iostream>
using namespace std;
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int i = 0;
	while(++i)
	{
		cout<<"I am a progress	"<< getpid()<<"	"<<getppid()<<"	"<<i<<endl;
		sleep(1);
	}
	return 0;
}
