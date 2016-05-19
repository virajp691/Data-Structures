// $Id: hashset.c,v 1.1 2014/03/17 20:52:39 vispatel Exp $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   DEBUGF ('h', "%p -> struct hashset {size = %d, chains=%p}\n",
                this, this->size, this->chains);
   return this;
}

void free_hashset (hashset *this) {
  // DEBUGF ('h', "free (%p)\n", this);
  size_t i;
  hashnode *node, *temp;

  if (this == NULL) return;

  for (i=0; i < this->size; ++i) {
    node = this->chains[i];
    while (node!=NULL) {
      temp = node;
      node = node->link;
      free(temp->word);
      free(temp);
    }
  }

  free (this->chains);
  free (this);
}

void put_hashset (hashset *this, const char *item) {
  // STUBPRINTF ("hashset=%p, item=%s\n", this, item);
  hashnode *new_node = malloc (sizeof (hashnode));
  assert (new_node != NULL);
  hashnode *current_node;
  size_t hash_index = strhash (item) % (this->size);
  
  for (current_node = this->chains[hash_index];
       current_node != NULL; current_node = current_node->link) {
    if (strcmp (item, current_node->word) == 0)
      return;
  }
  new_node->word = strdup(item);
  new_node->link = this->chains[hash_index];
  this->chains[hash_index] = new_node;

  this->load = this->load + 1;

}

bool has_hashset (hashset *this, const char *item) {
   // STUBPRINTF ("hashset=%p, item=%s\n", this, item);
   // Compute Hashcode
   size_t hash_index = strhash (item) % (this->size);
   // Start at Hash Index and Linear search until found or fail
   for (hashnode *list = this->chains[hash_index];
        list != NULL; list= list->link) {
     if (strcmp(item, list->word) == 0)
       return true;
   }
   return false;
}

