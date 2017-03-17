.PHONY:all
all:select_tcp client

client:client.c
	gcc -o $@ $^

select_tcp:select_tcp.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f select_tcp client
