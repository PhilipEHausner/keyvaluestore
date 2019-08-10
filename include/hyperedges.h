//
// Created by philip on 09.08.19.
//

#ifndef KEYVALUESTORE_HYPEREDGES_H
#define KEYVALUESTORE_HYPEREDGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

/*
 *
 * This class assumes that all data is inserted in a sorted fashion, i.e., lower edge IDs are inserted at first
 * and for all edges node IDs are inserted in ascending order.
 *
 */

typedef struct _NodeList {
    size_t node_id;
    struct _NodeList* next;
} NodeList;

typedef struct _HyperedgesList {
    size_t edge_id;
    NodeList* nodes;
    struct _HyperedgesList* next;
} HyperedgesList;


/// NodeList
NodeList* create_nodelist(size_t id);

void append_to_nodelist(NodeList* nodelist, size_t id);

void print_nodes(NodeList* nodes);

void free_nodes(NodeList* nodes);

/// HyperedgesList
HyperedgesList* create_hyperedges_from_csv(char* filepath, char* delim);

//void free_termlist(TermList* termlist);

void print_hyperedges(HyperedgesList* hyperedges);

void free_hyperedges(HyperedgesList* hyperedges);

#endif //KEYVALUESTORE_HYPEREDGES_H
