server=fifo_server
client=fifo_client
CC=gcc
serverSrc=server.c
clientSrc=client.c

.PHONY:all
all:$(server) $(client)

$(server):$(serverSrc)
	$(CC) -o $@ $^
$(client):$(clientSrc)
	$(CC) -o $@ $^

.PHONY:clean
clean:
	rm -f $(server) $(client) myfifo
