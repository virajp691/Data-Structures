// $Id: queue.c,v 1.6 2014-02-26 21:27:06-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
  queue *this = malloc (sizeof (struct queue));
  assert (this != NULL);
  return this;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
  queue_node *tmp = malloc (sizeof (queue_node));
  assert (tmp!=NULL);
  tmp->item=item;
  tmp->link = this->front;
  this->front = tmp;  
}

queue_item_t remove_queue (queue *this) {
   assert (! isempty_queue (this));
   queue_item_t result = this->front->item;
   this->front->item = NULL;
   this->front = this->front->link;
   
   return result;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}

