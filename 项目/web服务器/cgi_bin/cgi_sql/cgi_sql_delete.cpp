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
	std::string str;
	while(*start)
	{
		if(*start=='=')
		{
			str+="='";
		}
		else if(*start=='&')
		{
			str+="',";
		}
		else
		{
			str+=*start;
		}
		start++;
	}
	str+="'";
	sql_api sql;
	sql.sql_connect();
	sql.sql_delete(str);
	printf("<html>");
	printf("<h1>");
	printf("YES delete success");
	printf("</h1>");
	printf("</html>");

	return 0;
}
