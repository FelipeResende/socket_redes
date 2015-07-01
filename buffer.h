#ifndef BUFFER_H
#define BUFFER_H

#define TAM_BUFFER 1000

#include<semaphore.h>
typedef struct buffer buffer;
typedef struct  buffer_element buffer_element;

struct buffer_element
{
	char c;
	long pos;
};

struct buffer
{
  buffer_element buff[TAM_BUFFER];
  buffer_element *head, *tail;
  sem_t empty;
  sem_t full;
  sem_t mutex_head;
  sem_t mutex_tail;
  buffer_element (*get)(struct buffer *b);
  void (*insert)(struct buffer *b, buffer_element c);
};

buffer_element getElemFromBuffer(buffer *b);
void insertElemInBuffer(buffer *b, buffer_element elem);
buffer_element *incrementa(buffer *b, buffer_element *elem);
void initBuffer(buffer *b);
void destructBuffer(buffer *b);

#endif
