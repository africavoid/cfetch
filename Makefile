CC=cc
CFLAGS= -Wno-implicit-function-declaration
PREFIX ?= /usr/local

all: 
	${CC} ${CFLAGS} main.c -o cof

clean:
	rm -f cof

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cof ${DESTDIR}${PREFIX}/bin/cof
	chmod 755 ${DESTDIR}${PREFIX}/bin/cof
