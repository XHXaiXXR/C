cc=gcc
bin=httpd
src=$(shell ls *.c)

LDFLAGS=-lpthread

$(bin):$(src)
	$(cc) -o $@ $^ $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(bin)
