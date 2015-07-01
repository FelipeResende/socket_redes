#include "buffer.h"

buffer_element getElemFromBuffer(buffer *b)
{
  sem_wait(&b->full);
  sem_wait(&b->mutex_head);
  buffer_element ret = *(b->head);
  b->head = incrementa(b, b->head);
  sem_post(&b->mutex_head);
  sem_post(&b->empty);
  return ret;
}

void insertElemInBuffer(buffer *b, buffer_element elem)
{
  sem_wait(&b->empty);
  sem_wait(&b->mutex_tail);
  *(b->tail) = elem;
  b->tail = incrementa(b, b->tail);
  sem_post(&b->mutex_tail);
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
  sem_init(&b->mutex_head, 0, 1);
  sem_init(&b->mutex_tail, 0, 1);
}

void destructBuffer(buffer *b)
{
  sem_destroy(&b->empty);
  sem_destroy(&b->full);
  sem_destroy(&b->mutex_head);
  sem_destroy(&b->mutex_tail);
}
