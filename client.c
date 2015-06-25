#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include "sock.h"
#include "buffer.h"

void *producer();
void *consumer();
void *transmitter_handler();

char texto[] = "Texto a ser escrito no buffer para testes...";
int port;
char file_name[200];
FILE *fr;
buffer b;

#define check(A,msg) \
  if ((A)) { \
    printf("##msg"); \
    exit(1); \
  }
    
#define MAX_THREADS 2
int main(int argc, char *argv[])
{
  pthread_t pthread_consumidor, pthread_produtor;

  if (argc != 3)
  {
    printf("Usage: %s port file\n", argv[0]);
    return 1;
  }
  port = atoi(argv[1]);

  strncpy(file_name, argv[2], 199);
  file_name[199] = '\0';

  initBuffer(&b);

  check(pthread_create(&pthread_produtor, NULL, producer, NULL), "ERROR creating thread producer!!\n");
  check(pthread_create(&pthread_consumidor, NULL, consumer, NULL), "ERROR creating thread consumer!!\n")
  check(pthread_join(pthread_produtor, NULL), "ERROR joining thread producer")
  check(pthread_join(pthread_consumidor, NULL), "ERROR joining thread consumer")

  destructBuffer(&b);
  pthread_exit(NULL);
  return 1;
}

void *producer()
{
  buffer_element elem;
  buffer *pb = &b;
  fr = fopen (file_name, "rb");
  
  elem.c = 'a';
  
  while( elem.c != EOF )
  {
    elem.pos = ftell(fr);
    elem.c = fgetc(fr); 
    pb->insert(pb, elem);
  }
  fclose(fr);  /* close the file prior to exiting the routine */
  return 0;
}
void *consumer()
{
  pthread_t n_threads[MAX_THREADS];
  for (int i = 0; i < MAX_THREADS; i++)
  {
    printf("thrd: %d\n", i);
    check(pthread_create(&n_threads[i], NULL, transmitter_handler, NULL), "Failed to create the client consumer thread");
  }
  for (int i = 0; i < MAX_THREADS; i++)
  {
    check(pthread_join(n_threads[i], NULL), "Error joining threads");
  }

  return NULL;
}

void *transmitter_handler()
{
  buffer *pb = &b;
  int s = sock_conn("localhost", port);
  if (s < 0)
    printf("Erro: s menor que zero!\n");

  buffer_element elem;
  elem  = pb->get(pb);
  while (elem.c != EOF)
  {
    if (send(s, &elem, sizeof(elem), 0) < 0)
    {
      puts("Send failed\n");
    }
    elem  = pb->get(pb);
  }
  return NULL;
}
