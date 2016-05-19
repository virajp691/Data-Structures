// $Id: nsort.c,v 1.1 2014-02-20 17:07:19-08 vispatel - $
// USER
//    Viraj Patel
// NAME
//    nsort - sort numbers read from stdin
// SYSNOPSIS
//    nsort [-d]

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  double item;
  node *link;
};

int main (int argc, char **argv) {
  char* progname = basename (argv[0]);
  node *head = NULL;
  double number;
  int c;
  int debugFlag = 0;

  c = getopt (argc, argv, "d:");
  if (c == 'd')
    debugFlag = 1;

  for (;;) {
    int scancount = scanf("%lg", &number);
    if (scancount == EOF) {
      break;
    }else {
      node *prev = NULL;
      node *curr = head;

      while (curr != NULL) {
        if (curr->item > number) break;
        prev = curr;
        curr = curr->link;
      }

      node *tmp = malloc (sizeof (struct node));
      assert (tmp != NULL);
      tmp->item = number;
      tmp->link = curr;
      if (prev == NULL) {
        head = tmp;
      }else {
        prev->link = tmp;
      };
    };
  };

  // Print in Debug Format
  if (debugFlag == 1) {
    printf("%s: head= %p\n", argv[0], head);
    while (head != NULL) {
      node *old = head;
      head = head->link;
      printf ("%s: %p-> node {\n"
              "    item= %.15g->\"%.15g\",\n"
              "    link= %p}\n",
              progname, old, old->item, old->item, old->link);
    };
    while (head != NULL) {
      node *old = head;
      head = head->link;
      free (old);
    }
    return EXIT_SUCCESS;
  };

  // Print regularly
  for (node *curr = head; curr != NULL; curr = curr->link) {
    printf ("%.15g\n", curr->item);
  };

  // Free all allocated nodes
  while (head != NULL) {
    node *old = head;
    head = head->link;
    free (old);
  }
  return EXIT_SUCCESS;
}
