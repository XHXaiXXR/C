#include <iostream>
using namespace std;
#include <assert.h>

size_t Strlen(const char* str)
{
	assert(str);

	size_t count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}

	return count;
}
size_t StrlenR(const char* str)
{
	if (*str == '\0')
	{
		return 0;
	}

	return StrlenR(++str) + 1;
}
void test()
{
	char* str = "hello moninghello moninghello moninghello moninghello moning";
	//int count = Strlen(str);
	int count = StrlenR(str);	
	cout<<"count = "<<count<<endl;
}