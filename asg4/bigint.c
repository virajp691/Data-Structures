// $Id: bigint.c,v 1.13 2014-01-24 18:33:47-08 - - $
// Viraj Patel (vispatel@ucsc.edu)

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

static void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}


bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

static bigint *do_add (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   size_t length = this->capacity > that->capacity ?
                   this->capacity+1 : that->capacity+1;
   bigint *result = new_bigint (length);
   int carry = 0;
   char digit;
   for(int index = 0; index < length; ++index) {
     digit = this->digits[index] + that->digits[index]+carry;
     result->digits[index] = digit % 10;
     carry = digit / 10;
   }
   return result;
}

static bigint *do_sub (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   bigint *result = new_bigint (this->size);
   int borrow = 0;
   char digit;
   for (int index = 0; index < this->size; ++index) {
     digit = this->digits[index] - that->digits[index] - borrow + 10;
     result->digits[index] = digit % 10;
     borrow = 1- digit / 10;
   }
   trim_zeros(result);
   return result;
}
void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
   DEBUGS ('b', show_bigint (this));
}

bigint *add_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   if (!this->negative && !that->negative) {
     bigint *sum = do_add (this, that);
     return sum;
   }else if (this->negative && that->negative) {
      bigint *sum = do_add (this, that);
      return sum;
   }else {
      if (this->size > that->size) {
         bigint *sum = do_sub (this , that);
         return sum;
      }else {
         bigint *sum = do_sub (that, this);
         return sum;
      }
   }
}

bigint *sub_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   STUB (return NULL);
   if (this->negative != that->negative) {
     bigint *sum = do_add (this, that);
     return sum;
   }else {
     bigint *sum = do_sub (this,that);
     return sum;
   }
}


bigint *mul_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   bigint *result = new_bigint (this->size + that->size);
   for (int i = 0; i < this->size - 1; ++i) {
     char c = 0;
     for (int j = 0; j < that->size - 1; ++j) {
       char d = result->digits[i+j] +
                (this->digits[i] * that->digits[j])
                + c;
       result->digits[i+j] = d % 10;
       c = d / 10;
     }
     result->digits[i+that->size] = c;
   }
   return result;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}

