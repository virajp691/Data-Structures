// $Id: inssort.c,v 1.1 2014-03-12 15:37:33-07 - - $

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "inssort.h"


// base - array
// nelem - number of elements
// size - size of one element
// compar - comparison function req. addresses of elements
void inssort (void* base, size_t nelem, size_t size
              ,int (*compar) (const void*, const void*)) {
  for (size_t index = 1; index < nelem; ++index) {
    int slot = index;
    void *temp = malloc (size);
    void *elem = (char*) base+index*size;
    void *copy = elem;
    for (; slot > 0; --slot) {
      void *elem2 = (char*) base + (slot-1) * size;
      int cmp = compar (&copy, &elem2);
      if (cmp > 0) break;
      memcpy (temp, elem , size);
      memcpy (elem, elem2, size);
      memcpy (elem2, temp, size);
    }
    memcpy (temp, elem, size);
    memcpy (elem, copy, size);
    memcpy (copy, temp, size);
    free (temp);
  }

}

