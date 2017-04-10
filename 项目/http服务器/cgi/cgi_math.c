#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _SIZE_ 1024

void math_data(char* data)
{
	//data1=100&data2=200
	char* buf[3];
	char* start = data;
	int i = 0;

	while(*start)
	{
		if(*start == '=')
		{
			buf[i] = start + 1;
			i++;
		}
		else if(*start == '&')
		{
			*start = '\0';
		}

		start++;
	}
	buf[i] = NULL;

	//buf[0] = data1   buf[1] = data2   buf[2] = NULL
	int data1 = atoi(buf[0]);
	int data2 = atoi(buf[1]);

	printf("<html>");
	printf("<h2><br/>");
	printf("%d + %d = %d\n",data1, data2, data1 + data2);
	printf("%d - %d = %d\n",data1, data2, data1 - data2);
	printf("%d * %d = %d\n",data1, data2, data1 * data2);
	printf("%d / %d = %d\n",data1, data2, data1 / data2);
	printf("%d %% %d = %d\n",data1, data2, data1 % data2);
	printf("</h2>");
	printf("</html>");
}

int main()
{
	printf("cgi runing.....\n");
	char cgi_math_data[_SIZE_];
	char method[_SIZE_];
	char content_length[_SIZE_];
	int content_len = -1;

	if(getenv("REQUEST_METHOD"))
	{
		strcpy(method, getenv("REQUEST_METHOD"));
	}
	else
	{
		printf("REQUEST_METHOD is not exist\n");
	}
	
	if(strcasecmp(method, "GET") == 0)
	{
		if(getenv("QUERY_STRING"))
		{
			strcpy(cgi_math_data, getenv("QUERY_STRING"));		
		}
		else
		{
			printf("QUERY_STRING is not exist\n");
		}
	}
	else if(strcasecmp(method, "POST") == 0)
	{

		if(getenv("CONTENT_LENGTH"))
		{
			strcpy(content_length, getenv("CONTENT_LENGTH"));
		}
		else
		{
			printf("CONTENT_LENGTH is not exist\n");
		}
		content_len = atoi(content_length);

		int i = 0;
		char c = '\0';
		for(;i < content_len;i++)
		{
			read(0, &c, 1);//从标准输入里面读（标准输入已经被重定项）
			cgi_math_data[i] = c;
		}
		cgi_math_data[i] = '\0';
	}
	else
	{}

	math_data(cgi_math_data);
	return 0;
}
