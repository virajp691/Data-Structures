// $Id: numsort.c,v 1.25 2014-03-12 15:52:07-07 - - $

// NAME
//    Numsort - sorts numbers from stdin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inssort.h"

int exit_status = EXIT_SUCCESS;

int doucmp (const void *this, const void *that){
  double *thisdouble = (double*) this;
  double *thatdouble = (double*) that;
  return (*thisdouble > *thatdouble) - (*thisdouble < *thatdouble);
}

int main () {
  double array[1000];
  int x;
  for (x=0; x < 999; ++x) {
    int scancount = scanf ("%lg", &array[x]);
    if (scancount == EOF) {
      printf ("EOF\n");
      break;
    }else if (scancount == 1) {
      printf ("number = %.15g\n",array[x]);
    }else {
      printf ("bad number\n");
      break;
    };
  }

  // qsort (&array[0], x, sizeof (double *), doucmp);
  inssort(array, x, sizeof (double *), doucmp);

  for (int i = 0; i < x; ++i) {
    printf ("%20.15g\n",array[i]);
  }
  return exit_status;
}
