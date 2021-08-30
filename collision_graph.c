#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "collision_graph.h"

graphnode *create_graph_node(int vertex) {
    graphnode *new_node = (graphnode *) malloc(sizeof(graphnode));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

graph *create_graph(int vert_count) {
    size_t i;
    graph *new_graph = (graph *) malloc(sizeof(graph));
    new_graph->num_vertices = vert_count;

    new_graph->adjacent = malloc(vert_count * sizeof(graphnode));

    for(i = 0; i < vert_count; ++i)
        new_graph->adjacent[i] = NULL;

    return new_graph;
}
void add_edge(graph *graph, int src, int dest) {
    graphnode *new_node = create_graph_node(dest);
    new_node->next = graph->adjacent[src];
    graph->adjacent[src] = new_node;

    new_node = create_graph_node(src);
    new_node->next = graph->adjacent[dest];
    graph->adjacent[dest] = new_node;
}

void append_edge(graph *graph, int src, int dest) {
    graphnode *new_node, *last;

    last = graph->adjacent[src];
    new_node = create_graph_node(dest);

    if (graph->adjacent[src] == NULL) {
        graph->adjacent[src] = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void add_collisions(graph *graph, vector *trs, int radius) {
    size_t i, j;
    size_t trs_count;
    transmitter *trs_i, *trs_j;
    double distance;

    if(!graph || !trs || !trs->items)
        return;

    trs_count = trs->curr_size;

    for(i = 0; i < trs_count; ++i) {
        for(j = 0; j < trs_count; ++j) {
            trs_i = (transmitter *) vector_get(trs, i);
            trs_j = (transmitter *) vector_get(trs, j);
            if (j == i) {
                break;
            }
            distance = sqrt(fabs((trs_j->x_pos - trs_i->x_pos) * (trs_j->x_pos - trs_i->x_pos)) +
                             fabs((trs_j->y_pos - trs_i->y_pos) * (trs_j->y_pos - trs_i->y_pos)));

            if(distance < (2 * radius)) {
                append_edge(graph, i, j);
                append_edge(graph, j ,i);
            }
        }
    }
}

void print_graph(graph *graph) {
    size_t vert;
    graphnode *tmp;
    for (vert = 0; vert < graph->num_vertices; ++vert) {
        tmp = graph->adjacent[vert];
        printf("\n Adjacency list of vertex %ld\n", vert);
        while (tmp) {
            printf("%d->", tmp->vertex);
            tmp = tmp->next;
        }
        printf("end\n");
    }
}

void free_graph(graph *graph) {
    size_t vert;
    graphnode *tmp, *head;
    for (vert = 0; vert < graph->num_vertices; ++vert) {
        head = graph->adjacent[vert];
        while(head) {
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(graph->adjacent);
    free(graph);
}