// $Id: list4.c,v 1.19 2014-02-19 18:17:32-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   char *word;
   node *link;
};

int main (int argc, char **argv) {
   node *head;
   for (int argi = 0; argi < 5; ++argi) {
      node *node = malloc (sizeof (struct node));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }

   for (node *curr = head; curr->link != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->*word, curr->link);
   }

   free (head->link->link->link->link);
   free (head->link->link->link);
   free (head->link->link);
   free (head->link);
   free (head);

   return 9;
}
