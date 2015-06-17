#include "buffer.h"

char getCharFromBuffer(struct buffer *b)
{
  sem_wait(&b->full);
  char ret = *(b->head);
  b->head = incrementa(b, b->head);
  sem_post(&b->empty);
  return ret;
}

void insertCharInBuffer(struct buffer *b, char c)
{
  sem_wait(&b->empty);
  *(b->tail) = c;
  b->tail = incrementa(b, b->tail);
  sem_post(&b->full);
}

char *incrementa(struct buffer *b, char *c)
{
  if (c == &b->buff[TAM_BUFFER - 1])
  {
    return b->buff;
  }
  return ++c;
}

void initBuffer(struct buffer *b)
{
  b->head = (b->buff);
  b->tail = (b->buff);
  b->get = &getCharFromBuffer;
  b->insert = &insertCharInBuffer;
  sem_init(&b->full, 0, 0);
  sem_init(&b->empty, 0, TAM_BUFFER);
}

void destructBuffer(struct buffer *b)
{
  sem_destroy(&b->empty);
  sem_destroy(&b->full);
}
