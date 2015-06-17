client: buffer.o client.c connectsock.o connectTCP.o
	gcc -Wall -g -lpthread $^ -o $@.out

client2: client2.c buffer.o
	gcc -Wall -g -lpthread $^ -o $@.out

%.o: %.c
	gcc -Wall -c $^

clean:
	rm *.o client client2
