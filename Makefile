CC=cc
CFLAGS= -Wno-implicit-function-declaration
PREFIX ?= /usr/local

all: 
	${CC} ${CFLAGS} main.c -o cof

clean:
	rm cof

install: all
	mkdir -p ${PREFIX}/bin
	cp -f cof ${PREFIX}/bin/cof
	chmod 755 ${PREFIX}/bin/cof
