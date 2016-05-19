// $Id: hashset.h,v 1.1 2014/03/17 20:53:11 vispatel Exp $

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset hashset;

//
// Create a new hashset with a default number of elements.
//
hashset *new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset*);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset*, const char*);

//
// Looks up the string in the hashset and returns true if found,
// false if not found.
//
bool has_hashset (hashset*, const char*);

#endif

