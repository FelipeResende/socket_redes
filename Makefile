DEP=buffer.o sock.o
CFLAGS=-Wall -g
LIBS=-lpthread
CC=gcc

server: ${DEP}
	${CC} ${CFLAGS} ${LIBS} ${DEP} $@.c -o $@

client: ${DEP}
	${CC} ${CFLAGS} ${LIBS} ${DEP} $@.c -o $@

%.o: %.c
	gcc -Wall -c $^

clean:
	rm -f *.o client server
