ser=server
cli=client
serverSrc=comm.c server.c
clientSrc=comm.c client.c
CC=gcc

.PHONY:all
all:$(ser) $(cli)

$(ser):$(serverSrc)
	$(CC) -o $@ $^
$(cli):$(clientSrc)
	$(CC) -o $@ $^

-PHONY:clean
clean:
	rm -f $(ser) $(cli)
