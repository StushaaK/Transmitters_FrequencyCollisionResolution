#ifndef _COLLISION_GRAPH_H
#define _COLLISION_GRAPH_H

#include "vector.h"

#define NO_FREQ -1

typedef struct thetransmitter {
    float x_pos, y_pos;
    int freq;
} transmitter;

typedef struct thegraphnode{
    int vertex;
    struct thegraphnode* next;
} graphnode;

typedef struct thegraph {
    int num_vertices;
    graphnode **adjacent;
} graph;

graphnode *create_graph_node(int vertex);
graph *create_graph(int vert_count);
void add_edge(graph *graph, int src, int vertex);
void add_collisions(graph *graph, vector *trs, int radius);
void print_graph(graph *graph);
void free_graph(graph *graph);

#endif