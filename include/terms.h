//
// Created by philip on 07.08.19.
//

#ifndef KEYVALUESTORE_TERMS_H
#define KEYVALUESTORE_TERMS_H

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include "hashmap.h"

typedef struct {
    size_t term_id;
    char* name;
} Term;

typedef struct Term_List {
    Term* term;
    struct Term_List* next;
} TermList;


/// TERMS
Term* create_term(size_t term_id, char* name);

void free_term(Term* term);


/// TERMLIST
TermList* create_terms_from_csv(char* filepath, char* delim);

void free_termlist(TermList* termlist);

void print_terms(TermList* terms);


/// utilities
map_t create_nameToID_hashmap_from_termlist(TermList* terms);

// checks if all elements in termlist are returned correctly
bool control_nameToID_hashmap(TermList* terms, map_t map);

#endif //KEYVALUESTORE_TERMS_H
