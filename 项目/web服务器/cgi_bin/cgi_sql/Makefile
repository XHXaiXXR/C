DIR=-I/usr/include/mysql
LIB=-L/usr/lib/mysql
lib=-lmysqlclient
DEFINE=-DDEBUG
CC=g++

.PHONY:all
all:cgi_sql_insert cgi_sql_select cgi_sql_delete

cgi_sql_insert:cgi_sql_insert.cpp sql_api.cpp
	$(CC) -o $@  $^ $(LIB) $(lib) $(DIR)

cgi_sql_select:cgi_sql_select.cpp sql_api.cpp 
	$(CC) -o $@  $^ $(LIB) $(lib) $(DIR)

cgi_sql_delete:cgi_sql_delete.cpp sql_api.cpp 
	$(CC) -o $@  $^ $(LIB) $(lib) $(DIR)

.PHONY:clean
clean:
	rm -rf cgi_sql_insert cgi_sql_select
