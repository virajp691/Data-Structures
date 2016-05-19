// $Id$

#ifndef __INSSORT_H__
#define __INSSORT_H__

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar_t;

void inssort (void* base, size_t nelem, size_t size,
              int (*compar) (const void*, const void*));

#endif
