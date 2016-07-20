#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>
void Reversal(char* start,char* end)
{
	assert(start);
	assert(end);

	//tneduts a ma i
	while (start < end)
	{
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
}

int MyStrlen(char arr[])
{
	assert(arr);
	int count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return count;
}

void ReversalStr(char arr[])
{
	assert(arr);
	int len = MyStrlen(arr);
	Reversal(arr,arr+len-1);//i ma a tneduts
	
	char *start = arr;
	char *end = arr;

	while (*end != '\0')
	{
		while ((*end != ' ') && (*end != '\0'))
		{
			end++;
		}

		end--;
		Reversal(start,end);
		if (*(end+1) != '\0')
		{
			end = end + 2;
			start = end;
		} 
		else
		{
			end++;
		}
	}
}



int main()
{
	char arr[] = "student a am i";
	//i am a student
	ReversalStr(arr);
	cout<<arr<<endl;
	system("pause");
	return 0;
}