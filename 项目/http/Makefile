.PHONY:all
all:http cgi

http:httpd.c main.c 
	gcc -o $@ $^ -lpthread

.PHONY:cgi
cgi:
	cd cgi; make; make output; cd -

.PHONY:clean
clean:
	rm -rf http output cgi_math; cd cgi; make clean; cd -

.PHONY:output
output:
	mkdir output
	cp http output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin/

