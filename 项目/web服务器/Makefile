
.PHONY:all
all:thttpd
	cd cgi_bin;make;cd -

thttpd:/home/admin/code/web/main.o /home/admin/code/web/thttpd.o 
	gcc -o $@ $< -lpthread
%.o:%.c
	gcc -c $<

.PHONY:output
output:
	mkdir output
	cp -rf log output/
	cp -rf conf output/
	cp thttpd output/
	cp -rf wwwroot output/
	cp thttp_ctl.sh output/
	mkdir -p output/wwwroot/cgi_bin/sql
	cp cgi_bin/cgi_math output/wwwroot/cgi_bin
	cp -rf cgi_bin/cgi_sql/cgi_sql_insert  output/wwwroot/cgi_bin/sql/
	cp -rf cgi_bin/cgi_sql/cgi_sql_select  output/wwwroot/cgi_bin/sql/
	cp -rf cgi_bin/cgi_sql/cgi_sql_delete  output/wwwroot/cgi_bin/sql/
.PHONY:clean
clean:
	rm -rf thttpd *.o output;cd cgi_bin;make clean;cd -
