// $Id: stack.c,v 1.11 2013-05-16 15:07:42-07 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "debug.h"

#define DEFAULT_CAPACITY 16

struct stack {
   size_t capacity;
   size_t size;
   stack_item *data;
};

stack *new_stack (void) {
   stack *this = malloc (sizeof (stack));
   assert (this != NULL);
   this->capacity = DEFAULT_CAPACITY;
   this->size = 0;
   this->data = calloc (this->capacity, sizeof (stack_item));
   assert (this->data != NULL);
   return this;
}

void free_stack (stack *this) {
   assert (empty_stack (this));
   free (this->data);
   free (this);
}

static bool full_stack (stack *this) {
   return this->size == this->capacity;
}

static void realloc_stack (stack *this) {
   size_t old_capacity = this->capacity;
   this->capacity *= 2;
   this->data = realloc (this->data, this->capacity);
   memset (this->data + old_capacity, 0, old_capacity);
   assert (this->data != NULL);
}


void push_stack (stack *this, stack_item item) {
   DEBUGS ('s', show_stack (this));
   DEBUGF ('s', "item=%p\n", item);
   if (full_stack (this)) realloc_stack (this);
   this->data[this->size+1] = item;
   this->size = this->size + 1;
}

stack_item pop_stack (stack *this) {
   assert (! empty_stack (this));
   DEBUGS ('s', show_stack (this));
   stack_item item = this->data[this->size];
   this->data[this->size] = NULL;
   this->size = this->size-1;
   return item;   
}

stack_item peek_stack (stack *this, size_t index) {
   assert (index < size_stack (this));
   DEBUGS ('s', show_stack (this));
   stack_item item = this->data[index];
   return item;
}

bool empty_stack (stack *this) {
   return size_stack (this) == 0;
}

size_t size_stack (stack *this) {
   return this->size;
}

void show_stack (stack *this) {
   fprintf (stderr, "stack@%p->{%lu,%lu,%p}\n",
            this, this->capacity, this->size, this->data);
}

