// $Id: lsort.c,v 1.1 2014/02/20 21:01:57 vispatel - $
// USER
//    VIRAJ PATEL (vispatel@ucsc.edu)
// NAME
//    lsort - sort lines read from stdin
// SYSNOPSIS
//    lsort [-d]


#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  char *string;
  node *link;
};

int main (int argc, char **argv) {
  (void) argc; 
  char *progname = basename (argv[0]);
  node *head = NULL;
  char buffer[256];

  for(;;) {
    node *prev = NULL;
    node *curr = head;
    fgets(buffer, sizeof (buffer), stdin);

    if (buffer == NULL) break;

    // Find insertion point
    while (curr != NULL) {
      if (strcmp (curr->string, buffer) > 0) break;
      prev = curr;
      curr = curr->link;
    }

    // Insert the string
    node *tmp = malloc (sizeof (struct node));
    assert (tmp != NULL);
    tmp->string = buffer;
    tmp->link = curr;
    if (prev == NULL) {
      head = tmp;
    }else {
      prev->link = tmp;
    };
  };

  // Print out nodes values
  for (node *curr = head; curr != NULL; curr = curr->link) {
    printf("%s\n", curr->string);
  }

  // Free Memory
  while (head != NULL) {
    node *old = head;
    head = head->link;
    free (old);
  }

  return EXIT_SUCCESS;

}

