#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "sock.h"
#include "buffer.h"

#define check(A,msg) \
  if ((A)) { \
    printf("##msg"); \
    exit(1); \
  }

void *producer(void *);
void *consumer(void *);

int main()
{
  buffer *b = malloc(sizeof(buffer));
  pthread_t pthread_consumidor, pthread_produtor;
  initBuffer(b);

  check(pthread_create(&pthread_produtor, NULL, producer, (void *)b), "ERROR creating thread producer!!\n");
  check(pthread_create(&pthread_consumidor, NULL, consumer, (void *)b), "ERROR creating thread consumer!!\n")
  check(pthread_join(pthread_produtor, NULL), "ERROR joining thread producer")
  check(pthread_join(pthread_consumidor, NULL), "ERROR joining thread consumer")

  destructBuffer(b);

  pthread_exit(NULL);
  return 1;
}

void *producer(void *b)
{
  buffer *pb = (buffer *)b;
  int n = sock_bind(8000, 3);
  int n_client = sock_accept(n);
  int read_size;
  char m;

  if (n < 0 || n_client < 0)
    pthread_exit(NULL);

  while ( (read_size = recv(n_client, &m, 1, 0)) > 0 )
  {
    printf("Server producer: %c\n", m);
    pb->insert(pb, m);
  }
  return NULL;
}

void *consumer(void *b)
{
  buffer *pb = (buffer *)b;
  while (1)
  {
    char c = pb->get(pb);
    printf("\t\tServer consumer: %c\n", c);
  }

  return NULL;
}
