#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "include/terms.h"
#include "include/hashmap.h"

//typedef struct {
//    size_t term_id;
//    char* name;
//} term_idents;

Term terms[59883];

int main() {
    char* nodes_path = "../data/terms.csv";
    char* edges_path = "../data/occurrences.csv";

    int error;
    FILE *fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t term_len = 0;

    fp = fopen(nodes_path, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    map_t mymap = hashmap_new();


    while ((read = getline(&line, &len, fp)) != -1) {
        Term* term;
        char* endptr;
        char* temp_temp_id = strtok(line, ",");
        size_t temp_id = strtoumax(temp_temp_id, &endptr, 10);
        char* temp_name = strtok(NULL, ",");
        temp_name[strlen(temp_name) - 1] = 0;
        term = create_term(temp_id, temp_name);
//        term = (term_idents*)malloc(sizeof(term_idents));
//        term->term_id = atoi(strtok(line, ","));
//        term->name = strtok(NULL, ",");
        terms[term_len++] = *term;
        printf("Retrieved line of length %zu:\n", read);
        printf("%zu : %s\n", term->term_id, term->name);
        error = hashmap_put(mymap, term->name, &term->term_id);
    }

    size_t out = 2;
    char * test = "Maurice E. Crumpacker";
    error = hashmap_get(mymap, test, (void**)(&out));
    printf("Result for %s: %zu with %i", test, out, error);

    fclose(fp);
    if (line) {
        free(line);
    }

    hashmap_free(mymap);

    return 1;
}
