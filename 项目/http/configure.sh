#!/bin/bash

CC=gcc
LOCAL_PATH=$(pwd)

#top
SRC=$(ls *.c | tr '\n' ' ')
INCLUDE="-lpthread"
HTTPD=http

#cgi
CGI_PATH=${LOCAL_PATH}/cgi/
MATH_SRC=$(ls ${CGI_PATH} | grep 'math' | grep -E '.c$')
MATH=cgi_math

#cgi Makefile
cat << EOF > ${CGI_PATH}/Makefile
${MATH}:${MATH_SRC}
	${CC} -o \$@ \$^

.PHONY:clean
clean:
	rm -f ${MATH}

.PHONY:output
output:
	mv ${MATH} ..
EOF



#top Makefile
cat <<EOF >Makefile
.PHONY:all
all:${HTTPD} cgi

${HTTPD}:${SRC}
	${CC} -o \$@ \$^ ${INCLUDE}

.PHONY:cgi
cgi:
	cd cgi; make; make output; cd -

.PHONY:clean
clean:
	rm -rf ${HTTPD} output ${MATH}; cd cgi; make clean; cd -

.PHONY:output
output:
	mkdir output
	cp ${HTTPD} output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin/

EOF
