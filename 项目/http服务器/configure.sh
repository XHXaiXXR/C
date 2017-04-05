#!/bin/bash

LOCAL_PATH=$(pwd)
SRC=$(ls *.c | tr '\n' ' ')
echo ${SRC}
CC=gcc
INCLUDE="-lpthread"
HTTPD=http

cat <<EOF >Makefile
${HTTPD}:${SRC}
	${CC} -o \$@ \$^ ${INCLUDE}

.PHONY:clean
clean:
	rm -f ${HTTPD}
EOF
