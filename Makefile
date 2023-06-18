CC=cc
CFLAGS= -Wno-implicit-function-declaration

all: final

final: main.o
	${CC} ${CFLAGS} main.o -o cof
main.o: main.c 
	${CC} ${CFLAGS} -c main.c

clean:
	rm main.o

install: all 
	cp -f cof /usr/local/bin/cof
	chmod 755 /usr/local/bin/cof
