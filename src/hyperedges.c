//
// Created by philip on 09.08.19.
//

#include "../include/hyperedges.h"

/// NodeList

NodeList* create_nodelist(size_t id) {
    NodeList* new_nodelist = (NodeList*)malloc(sizeof(NodeList));
    new_nodelist->node_id = id;
    new_nodelist->next = NULL;
    return new_nodelist;
}

void append_to_nodelist(NodeList* nodelist, size_t id) {
    while (nodelist->next != NULL) {
        nodelist = nodelist->next;
    }
    NodeList* new_nodelist = create_nodelist(id);
    nodelist->next = new_nodelist;
}

void print_nodes(NodeList* nodes) {
    while (nodes != NULL) {
        printf("%zu ", nodes->node_id);
        nodes = nodes->next;
    }
}

void free_nodes(NodeList* nodes) {
    NodeList* next_nodes;

    while(nodes != NULL) {
        next_nodes = nodes->next;
        free(nodes);
        nodes = next_nodes;
    }
}


/// HyperedgesList

HyperedgesList* create_hyperedges_from_csv(char* filepath, char* delim) {
    // Necessary variables for reading in csv file
    FILE *fp;
    char* line = NULL;
    //char* line_in = NULL;
    size_t len;
    ssize_t read;
    char* endptr = NULL;
    char* line_edge_id = NULL;
    char* line_node_id = NULL;
    // needs to be initialized only once, since the content is always copied and not directly used
    size_t* edge_id = (size_t*)malloc(sizeof(size_t));
    size_t* node_id = (size_t*)malloc(sizeof(size_t));
    size_t* last_edge_id = (size_t*)malloc(sizeof(size_t));
    *last_edge_id = -1;
    // Return
    HyperedgesList* hyperedges = NULL;
    HyperedgesList* next_hyperedges = NULL;
    HyperedgesList* first_hyperedges = NULL;


    // open csv file
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        return NULL;
    }

    // read file line by line
    while((read = getline(&line, &len, fp)) != -1) {
        //line = line_in;

        // actual line content
        line_edge_id = strtok(line, delim);
        line_node_id = strtok(NULL, delim);

        // remove \n
        line_node_id[strlen(line_node_id) - 1] = 0;

        // convert input to numbers
        *edge_id = strtoumax(line_edge_id, &endptr, 10);
        *node_id = strtoumax(line_node_id, &endptr, 10);

        if (*edge_id != *last_edge_id) {
            /// new edge
            next_hyperedges = (HyperedgesList*)malloc(sizeof(HyperedgesList));
            next_hyperedges->edge_id = *edge_id;
            next_hyperedges->nodes = create_nodelist(*node_id);
            next_hyperedges->next = NULL;
        } else {
            /// still the same hyperedge
            append_to_nodelist(hyperedges->nodes, *node_id);
        }

        /// Return first element of list
        if (first_hyperedges == NULL) {
            assert(hyperedges == NULL);
            hyperedges = next_hyperedges;
            first_hyperedges = hyperedges;
        } else if (*edge_id != *last_edge_id) {
            hyperedges->next = next_hyperedges;
            hyperedges = next_hyperedges;
        }

        /// save id of last edge to evaluate if we have to create a new node list or append to the last
        *last_edge_id = *edge_id;
    }

    // clean up
    fclose(fp);
    free(edge_id);
    free(node_id);
    free(last_edge_id);
    free(line);

    return first_hyperedges;
}

void print_hyperedges(HyperedgesList* hyperedges) {
    while (hyperedges != NULL) {
        printf("%zu: ", hyperedges->edge_id);
        print_nodes(hyperedges->nodes);
        printf("\n");
        hyperedges = hyperedges->next;
    }
}

void free_hyperedges(HyperedgesList* hyperedges) {
    HyperedgesList* next_hyperedges;

    while (hyperedges != NULL) {
        next_hyperedges = hyperedges->next;
        free_nodes(hyperedges->nodes);
        free(hyperedges);
        hyperedges = next_hyperedges;
    }
}