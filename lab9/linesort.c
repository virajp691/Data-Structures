// $Id: linesort.c,v 1.6 2014-03-12 15:52:07-07 - - $

// NAME
//    Linesort - sorts lines from stdin in array

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inssort.h"

int exit_status = EXIT_SUCCESS;

int strstrcmp (const void *this, const void *that) {
  char **thisstr = (char**) this;
  char **thatstr = (char**) that;
  return strcmp (*thisstr, *thatstr);
}

int main () {
  int x;
  char* array[1000]; //array of 1000 char pointers
  char buffer[1000]; // input buffer

  for (x=0; x < 999; ++x) {
    char *gotline = fgets (buffer, sizeof (buffer), stdin);
    if (gotline == NULL) break;
    char *nlpos = strchr (buffer, '\n');
    if (nlpos != NULL) {
      *nlpos = '\0';
    }
    array[x] = strdup (buffer);
    printf ("Line: %s\n", array[x]);
  }
  // qsort (&array[0], x, sizeof (char *), strstrcmp);
  inssort (array, x, sizeof (char *), strstrcmp);
  for (int i=0; i<x; ++i){
    printf ("%s\n",array[i]);
  }
  return exit_status;
}
