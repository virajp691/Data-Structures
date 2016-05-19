// $Id: queue.h,v 1.1 2014-02-25 12:20:45-08 vispatel - $

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct queue queue;
typedef char *queue_item_t;

queue *new_queue (void);

void free_queue (queue*);

void insert_queue (queue*, queue_item_t);

queue_item_t remove_queue (queue*);

bool isempty_queue (queue*);

#endif

