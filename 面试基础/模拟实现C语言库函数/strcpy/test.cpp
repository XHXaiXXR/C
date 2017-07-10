#include <iostream>
using namespace std;
#include<assert.h>

char* Strcpy(char* dect, const char* src)
{
	assert(dect);
	assert(src);

	char* newdect = dect;
	while (*dect++ = *src++)
	{
		;
	}

	return newdect;
}

void test()
{
	char str[10];
	Strcpy(str, "  hello");
	cout<<str<<endl;
}