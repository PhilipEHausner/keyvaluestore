//
// Created by philip on 07.08.19.
//

#ifndef KEYVALUESTORE_TERMS_H
#define KEYVALUESTORE_TERMS_H

#include <stdlib.h>

typedef struct {
    size_t term_id;
    char* name;
} Term;

Term* create_term(size_t term_id, char* name);

#endif //KEYVALUESTORE_TERMS_H
