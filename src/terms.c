//
// Created by philip on 07.08.19.
//

#include "../include/terms.h"
#include <stdio.h>

/// TERM

Term* create_term(size_t term_id, char* name) {
    Term* new_term = (Term*)malloc(sizeof(Term));
    new_term->term_id = term_id;
    new_term->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    strcpy(new_term->name, name);
    return new_term;
}

void free_term(Term* term) {
    free(term->name);
    free(term);
}


/// TERMLIST

TermList* create_terms_from_csv(char* filepath, char* delim) {
    // Necessary variables for reading in csv file
    FILE *fp;
    char* line = NULL;
    size_t len;
    ssize_t read;
    char* endptr = NULL;
    char* line_id = NULL;
    char* line_name = NULL;
    // needs to be initialized only once, since the content is always copied and not directly used
    size_t* temp_id = (size_t*)malloc(sizeof(size_t));
    Term* term = NULL;
    // return
    TermList* termlist = NULL;
    TermList* next_termlist = NULL;
    TermList* first_term = NULL;

    // open csv file
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        return NULL;
    }

    // read file line by line
    while((read = getline(&line, &len, fp)) != -1) {
        // actual line content
        line_id = strtok(line, delim);
        line_name = strtok(NULL, delim);

        if (line_name == NULL) {
            continue;
        }

        *temp_id = strtoumax(line_id, &endptr, 10);
        // remove \n
        line_name[strlen(line_name) - 1] = 0;

        term = create_term(*temp_id, line_name);

        next_termlist = (TermList*)malloc(sizeof(TermList));
        next_termlist->term = term;
        next_termlist->next = NULL;

        if (next_termlist->term->term_id == 389818) {
            printf("id 389818 : %s\n", termlist->term->name);
        }

        // We want to return the first term
        if (first_term == NULL) {
            assert(termlist == NULL);
            termlist = next_termlist;
            first_term = termlist;
        } else {
            termlist->next = next_termlist;
        }

        termlist = next_termlist;
    }

    // clean up
    fclose(fp);
    free(line);
    free(temp_id);

    return first_term;
}

void free_termlist(TermList* termlist) {
    TermList* next_termlist;

    while(termlist != NULL) {
        next_termlist = termlist->next;
        free_term(termlist->term);
        free(termlist);
        termlist = next_termlist;
    }
}

void print_terms(TermList* terms) {
    while (terms != NULL) {
        printf("%zu : %s\n", terms->term->term_id, terms->term->name);
        terms = terms->next;
    }
}


/// Utilities

map_t create_nameToID_hashmap_from_termlist(TermList* terms) {
    map_t nameToID_map = hashmap_new();

    /// fill hashmap
    int error;
    while (terms != NULL) {
        error = hashmap_put(nameToID_map, terms->term->name, &terms->term->term_id);
        terms = terms->next;
        assert(error == MAP_OK);
    }

    return nameToID_map;
}

bool control_nameToID_hashmap(TermList* terms, map_t map) {
    size_t* out = (size_t*)malloc(sizeof(size_t));
    int error;
    bool okay = true;
    while (terms != NULL) {
        error = hashmap_get(map, terms->term->name, (void**)(&out));
        if (error != MAP_OK || *out != terms->term->term_id) {
            okay = false;
        }
        assert(error == MAP_OK);
        if (strlen(terms->term->name) <= 5) {
            printf("ALARM\n");
        }
        printf("%zu : %zu : %s\n", *out, terms->term->term_id, terms->term->name);
        printf("%u : %u\n", hashmap_hash_int(map, "overspend"), hashmap_hash_int(map, terms->term->name));
        assert(*out == terms->term->term_id);
        printf("fhusaf\n");
        terms = terms->next;
    }
    return okay;
}