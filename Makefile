client: buffer.o client.c
	gcc -Wall -g -lpthread $^ -o $@.out

%.o: %.c
	gcc -Wall -c $^

clean:
	rm *.o client client2
