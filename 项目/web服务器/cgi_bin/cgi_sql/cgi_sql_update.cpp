#include"sql_api.h"
#include"cgi.h"

int main()
{
	char content_data[_SIZE_]={0};
	if(cgi(content_data)!=0)
	{
		//cout<<falied<<endl;
		return -1;
	}

	char* start=content_data;
	char* cont[8];
	int i=0;
	while(*start)
	{
		if(*start=='=')
		{
			cont[i++]=start+1;
		}
		else if(*start=='&')
		{
			*start='\0';
		}
		start++;
	}
	
	int j=0;
	std::string str;
	for(j=0;j<i;j++)
	{
		str+="' ";
		str+=cont[j];
		if(j==i-1)
		{
			str+="' ";
		}
		else
		{
			str+="',";
		}
	}
	sql_api sql;
	sql.sql_connect();
	sql.sql_insert(str);
	printf("<html>");
	printf("<h1>");
	printf("YES");
	printf("</h1>");
	printf("</html>");

	return 0;
}
