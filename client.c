#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include "sock.h"
#include "buffer.h"

void *producer(void *);
void *consumer(void *);

char texto[] = "Texto a ser escrito no buffer para testes...";
int port;

#define check(A,msg) \
  if ((A)) { \
    printf("##msg"); \
    exit(1); \
  }
    
int main(int argc, char *argv[])
{
  buffer *b = malloc(sizeof(buffer));
  pthread_t pthread_consumidor, pthread_produtor;

  if (argc != 2)
  {
    printf("Usage: %s port\n", argv[0]);
    return 1;
  }
  port = atoi(argv[1]);

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
    /*printf("Producer: %c\n", texto[i]);*/
    pb->insert(pb, texto[i]);
  }
  return 0;
}
void *consumer(void *d)
{
  buffer *pb = (buffer *)d;
  int s = sock_conn("localhost", port);
  if (s < 0)
    printf("Erro: s menor que zero!\n");

  printf("2\n");
  while (1)
  {
    char c = pb->get(pb);
    /*printf("\t\tConsumer: %c\n", c);*/
    if (send(s, &c, 1, 0) < 0)
    {
      puts("Send failed\n");
    }
  }
  return 0;
}
