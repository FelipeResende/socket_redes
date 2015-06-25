#include "buffer.h"

buffer_element getElemFromBuffer(buffer *b)
{
  sem_wait(&b->full);
  buffer_element ret;
  ret.c = b->head->c;
  ret.pos = b->head->pos;
  b->head = incrementa(b, b->head);
  sem_post(&b->empty);
  return ret;
}

void insertElemInBuffer(buffer *b, buffer_element elem)
{
  sem_wait(&b->empty);
  b->tail->c = elem.c;
  b->tail->pos = elem.pos;
  b->tail = incrementa(b, b->tail);
  sem_post(&b->full);
}

buffer_element *incrementa(buffer *b, buffer_element *elem)
{
  if (elem == &b->buff[TAM_BUFFER - 1])
  {
    return b->buff;
  }
  return ++elem;
}

void initBuffer(buffer *b)
{
  b->head = (b->buff);
  b->tail = (b->buff);
  b->get = &getElemFromBuffer;
  b->insert = &insertElemInBuffer;
  sem_init(&b->full, 0, 0);
  sem_init(&b->empty, 0, TAM_BUFFER);
}

void destructBuffer(buffer *b)
{
  sem_destroy(&b->empty);
  sem_destroy(&b->full);
}
