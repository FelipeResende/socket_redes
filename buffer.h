#ifndef BUFFER_H
#define BUFFER_H

#define TAM_BUFFER 1

#include<semaphore.h>
typedef struct buffer buffer;

struct buffer
{
  char buff[TAM_BUFFER];
  char *head, *tail;
  sem_t empty;
  sem_t full;
  char (*get)(struct buffer *b);
  void (*insert)(struct buffer *b, char c);
};

char getCharFromBuffer(struct buffer *b);
void insertCharInBuffer(struct buffer *b, char c);
char *incrementa(struct buffer *b, char *c);
void initBuffer(struct buffer *b);
void destructBuffer(struct buffer *b);

#endif
