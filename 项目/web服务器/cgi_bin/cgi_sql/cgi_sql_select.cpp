#include"sql_api.h"
#include"cgi.h"

int main()
{
	sql_api sql;
	sql.sql_connect();
	sql.sql_select();
	return 0;
}
