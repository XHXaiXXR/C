#include"sql_api.h"

sql_api::sql_api()
{
	mysql=mysql_init(NULL);
}

sql_api::~sql_api()
{
	mysql_close(mysql);
}

int sql_api::sql_connect()
{
	if(!mysql_real_connect(mysql,"127.0.0.1","root","1996","myhttp",3306,NULL,0))
	{
		return -1;     //失败返回非0
	}
	return 0;     //成功返回0
}

int sql_api::sql_insert(std::string str)
{
	std::string data="insert into myhttp_info (name,sex,age,tel) values ( "; 
	data+=str;
	data+=" )";
	return mysql_real_query(mysql,data.c_str(),data.size());      //成功返回0，
}

int sql_api::sql_delete(std::string str)
{
	std::string data="delete from myhttp_info where ";
	data+=str;
	return mysql_real_query(mysql,data.c_str(),data.size());  //成功返回0
}

int sql_api::sql_select()
{
	std::string data="select * from myhttp_info";
	if(mysql_real_query(mysql,data.c_str(),data.size()))     //成功返回0
	{
		return -1;
	}
	//获取结果集
	MYSQL_RES *res=mysql_store_result(mysql);
	if(res==NULL)
	{
		return -1;     //失败返回非0
	}
	
	size_t num=mysql_num_fields(res);     //获取结果集的行数
	size_t num_field=mysql_field_count(mysql);  //获取结果集中的列数

	printf("<table border=\"1\" cellspacing=\"0\" >");
	printf("<tr>");	
	MYSQL_FIELD* field;       //获取列名
	while(field=mysql_fetch_field(res))
	{
		printf("<th>");
		cout<<field->name;
		printf("</th>");
	}
	printf("</tr>");

	MYSQL_ROW fetch;
	while(fetch=mysql_fetch_row(res))
	{
		printf("<tr>");
		int i=0;
		for(i=0;i<num_field;i++)
		{
			printf("<td>");	
			cout<<fetch[i];
			printf("</td>");	
		}
		printf("</tr>");
	}

	printf("</table>");
	return 0;
}

int sql_api::sql_update(std::string str1,std::string str2)
{
	std::string data="update myhttp_info set ";
	data+=str1;
	data+=" where ";
	data+=str2;
	return mysql_real_query(mysql,data.c_str(),data.size());    //
}

#ifdef DEBUG
int main()
{
	sql_api sql;
	sql.sql_connect();
	sql.sql_insert(" 'zhangsan' ,'man','18','13892905443'");
	sql.sql_update(" name='zhangfei' ","name='zhangsan'");
	sql.sql_select();
	return 0;
}

#endif
