DEP=buffer.o sock.o
CFLAGS=-Wall -g
LIBS=-lpthread
CC=gcc

all: server client

server: ${DEP} server.o
	${CC} ${CFLAGS} ${LIBS} ${DEP} $@.c -o $@

client: ${DEP} client.o
	${CC} ${CFLAGS} ${LIBS} ${DEP} $@.c -o $@

%.o: %.c
	gcc ${CFLAGS} -c $^

clean:
	rm -f *.o client server
