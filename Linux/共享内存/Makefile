ser=server
cli=client

serSrc=comm.c server.c
cliSrc=comm.c client.c
cc=gcc

.PHONY:all
all:$(ser) $(cli)

$(ser):$(serSrc)
	$(cc) -o $@ $^
$(cli):$(cliSrc)
	$(cc) -o $@ $^

-PHONY:clean
clean:
	rm -f $(ser) $(cli)

