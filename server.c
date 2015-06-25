#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include <sys/socket.h>
#include "sock.h"
#include "buffer.h"

#define check(A,msg) \
  if ((A)) { \
    printf("##msg"); \
    exit(1); \
  }

#define MAX_THREADS 10
void *producer();
void *consumer();
void *receiver_handler(void *n);

int port;
FILE *fr;

buffer b;
char filename[200];

int main(int argc, char *argv[])
{
  pthread_t pthread_consumidor, pthread_produtor;

  if (argc != 3)
  {
    printf("Usage: %s port filename\n", argv[0]);
    return 1;
  }
  port = atoi(argv[1]);
  strncpy(filename, argv[2], 199);
  filename[199] = '\0';

  initBuffer(&b);

  check(pthread_create(&pthread_produtor, NULL, producer, NULL), "ERROR creating thread producer!!\n");
  check(pthread_create(&pthread_consumidor, NULL, consumer, NULL), "ERROR creating thread consumer!!\n")
  check(pthread_join(pthread_produtor, NULL), "ERROR joining thread producer")
  check(pthread_join(pthread_consumidor, NULL), "ERROR joining thread consumer")

  destructBuffer(&b);

  return 1;
}

void *producer()
{
  int n = sock_bind(port, MAX_THREADS);
  int n_clients[MAX_THREADS];
  pthread_t n_threads[MAX_THREADS];

  for (int i = 0; i < MAX_THREADS; i++)
  {
    n_clients[i] = sock_accept(n);
    if (n < 0 || n_clients[i] < 0)
      pthread_exit(NULL);

    check(pthread_create(&n_threads[i], NULL, receiver_handler, (void *)&n_clients[i]), "Nao foi possivel criar a thread.\n");
  }

  for (int i = 0; i < MAX_THREADS; i++) check(pthread_join(n_threads[i], NULL), "Error joining threads"); 

  return NULL;
}

void *receiver_handler(void *n)
{
  int n_client = *(int *)n;
  int read_size;
  buffer_element elem;
  buffer *pb = &b;

  while ( (read_size = recv(n_client, &elem, sizeof(elem), 0)) > 0 )
  {
    pb->insert(pb, elem);
  }

  return NULL;
}
void *consumer()
{
  buffer *pb = &b;
  fr = fopen (filename, "w");

  while (1)
  {
    buffer_element elem = pb->get(pb);
    fseek(fr, elem.pos, SEEK_SET);
    fwrite(&elem.c, sizeof(char), 1, fr);
    //fputc(c, fr);
    //printf("%c %d", c, escreveu);
    fflush(fr);
  }

  return NULL;
}
