#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#include "sock.h"
#include "buffer.h"

void *producer(void *);
void *consumer(void *);

char texto[] = "Texto a ser escrito no buffer para testes...";

#define check(A,msg) \
  if ((A)) { \
    printf("##msg"); \
    exit(1); \
  }
    
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

void *producer(void * d)
{
  buffer *pb = (buffer *)d;
  for (int i = 0; i < sizeof(texto) - 1; ++i)
  {
    printf("Producer: %c\n", texto[i]);
    pb->insert(pb, texto[i]);
  }
  return 0;
}
void *consumer(void *d)
{
  buffer *pb = (buffer *)d;
  int s = sock_conn("localhost", "8000", "tcp");
  if (s < 0)
    printf("Erro s menor que zero!\n");
  for (int i = 0; i < sizeof(texto) - 1; ++i)
  {
    char c = pb->get(pb);
    printf("\t\tConsumer: %c\n", c);
  }
  return 0;
}
