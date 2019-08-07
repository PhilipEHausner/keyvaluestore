//
// Created by philip on 07.08.19.
//

#include "../include/terms.h"
#include <stdio.h>

//Term* create_term(size_t term_id, char* name) {
//    return NULL;
//}

Term* create_term(size_t term_id, char* name) {
    Term* new_term = (Term*)malloc(sizeof(Term));
    new_term->term_id = term_id;
    new_term->name = name;
    return new_term;
}