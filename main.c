#include <stdio.h>
#include <time.h>
#include "include/terms.h"
#include "include/hyperedges.h"
#include "include/hashmap.h"


int main() {
    /// runtime begin
   // clock_t begin = clock();

    /// paths to files
    char* nodes_path = "../data/terms.csv";
    char* edges_path = "../data/occurrences.csv";

    /// storage list for terms
    TermList* terms = create_terms_from_csv(nodes_path, "\t");

    /// fill hashmap for terms
    map_t nameToID_map = create_nameToID_hashmap_from_termlist(terms);

    /// control hashmap for terms
    //bool check = control_nameToID_hashmap(terms, nameToID_map);


    /// HYPER HYPER EDGES
    HyperedgesList* hyperedges = create_hyperedges_from_csv(edges_path, ",");

    clock_t begin = clock();
    char* thedonald = "Donald Trump";
    size_t* id;
    hashmap_get(nameToID_map, thedonald, (void**)(&id));
  //  printf("%s: %zu\n", thedonald, *id);

    clock_t begin2 = clock();
    int counter = 0;
    NodeList* nodes = NULL;
    HyperedgesList* iter_hyperedges = hyperedges;
    while (iter_hyperedges != NULL) {
        ++counter;
        nodes = iter_hyperedges->nodes;
        while (nodes != NULL) {
            if (*id == nodes->node_id) {
              //  printf("%zu\n", hyperedges->edge_id);

                break;
            }
            nodes = nodes->next;
        }
        iter_hyperedges = iter_hyperedges->next;
    }
    clock_t end = clock();
    printf("Counter: %i\n", counter);

    /// clean up
    free_termlist(terms);
    free_hyperedges(hyperedges);
    hashmap_free(nameToID_map);

  //  clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    double time_spent2 = (double)(end - begin2) / CLOCKS_PER_SEC;

    printf("Runtime with hash lookup: %f\n", time_spent);
    printf("Runtime without hash lookup: %f\n", time_spent2);

    return 1;
}
