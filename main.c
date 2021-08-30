#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "collision_graph.h"
#include "stack.h"

#define BUFFER_LEN 255

void parse_file(char *filename, int *radius, vector *frequencies, vector *transmitters) {
    FILE *f;
    char line_buffer[BUFFER_LEN];
        char file_part = 'b';   /* Aktualni cast souboru: 'b' - begin,  'f' - frekvence, 'r' - radius,  't' - transmitter   */
    transmitter *temp; /*   Pomocna promenna pro tvorbu a ukladani hodnot transmitteru  */
    int *val;

    f = fopen(filename, "r");
    if (!f) {
        printf("ERR#4: Could not open file!\n");
        exit(4);
    }

    while (fgets(line_buffer, BUFFER_LEN, f)) {


        switch (file_part) {
            case 'b':
                if (line_buffer[0] == 'A') file_part = 'f';
                break;
            case 'f':
                if (line_buffer[0] == 'T') file_part = 'r';
                else {
                    val = malloc(sizeof(int));
                    if (!val) {
                        printf("ERR#2: Out of memory!");
                        return;
                    }
                    sscanf(line_buffer, "%*d %d", val);
                    vector_add(frequencies, val);
                }
                break;
            case 'r':
                if (line_buffer[0] == 'T') file_part = 't';
                else {
                    sscanf(line_buffer, "%d", radius);
                }
                break;
            case 't':
                temp = malloc(sizeof(transmitter));
                if (!temp) {
                    printf("ERR#2: Out of memory!");
                    return;
                }
                sscanf(line_buffer, "%*d %f %f", &temp->x_pos, &temp->y_pos);
                temp->freq = NO_FREQ;
                vector_add(transmitters, temp);
                break;

        }
    }
    fclose(f);
}

int main(int argc, char* argv[]) {
    /*     DEKLERACE PROMENNYCH     */
    int radius = 0, stack_i, color = 0, freq_full;
    vector frequencies;
    vector transmitters;
    transmitter *t, *tmp_t;
    graph *collision_graph;
    size_t graph_size, i;
    stacknode *stack_root = NULL;
    graphnode *tmp_node = NULL;

    /*      KONTROLA ARGUMENTU      */
    if (argc != 2) {
        printf("ERR#1: Missing argument!\n");
        exit(1);
    }

    /*      INICIALIZACE VEKTORU        */
    vector_init(&frequencies);
    vector_init(&transmitters);

    /*      NAPLNENI VEKTORU A PROMENNE ZE SOUBORU      */
    parse_file(argv[1], &radius, &frequencies, &transmitters);

    /*      VYTVORENI GRAFU KOLIZI      */
    graph_size = transmitters.curr_size;
    collision_graph = create_graph(graph_size);
    add_collisions(collision_graph, &transmitters, radius);
    /* print_graph(collision_graph); */

    /*      OBARVOVACI ALGORITMUS       */
    for(i = 0; i < graph_size; ++i) {

        t = (transmitter *) vector_get(&transmitters, i);
        if(t->freq == NO_FREQ) {
            push(&stack_root, i);
        }

        while(!is_empty(stack_root)) {
            stack_i = pop(&stack_root);
            tmp_node = collision_graph->adjacent[stack_i];
            t = (transmitter *) vector_get(&transmitters, stack_i);
            while(t->freq == NO_FREQ) {
                while(tmp_node) {
                    tmp_t = vector_get(&transmitters, tmp_node->vertex);
                    if (color > (frequencies.curr_size-1)) {
                        printf("ERR#3: Non-existent solution!");
                        /*      UVOLNI PAMET        */
                        vector_free(&frequencies);
                        vector_free(&transmitters);
                        free_graph(collision_graph);
                        exit(3);
                    }
                    else if(color == tmp_t->freq) {
                        ++color;
                        tmp_node = collision_graph->adjacent[stack_i];
                    }
                    else {
                        tmp_node = tmp_node->next;
                    }
                }
                t->freq = color;
                color = 0;

                tmp_node = collision_graph->adjacent[stack_i];
                    while(tmp_node) {
                        tmp_t = vector_get(&transmitters, tmp_node->vertex);
                        if (tmp_t->freq == NO_FREQ && !in_stack(stack_root,tmp_node->vertex)) {
                            push(&stack_root, tmp_node->vertex);
                        }
                        tmp_node = tmp_node->next;
                    }
                }
            }

        }

    /*      VYPIS DO KONZOLE        */
    for( i = 0; i < transmitters.curr_size; ++i) {
        t = vector_get(&transmitters, i);
        freq_full = *((int *) vector_get(&frequencies, t->freq));
        printf("%lu %d\n", i, freq_full);
    }


    /*      UVOLNENI PAMETI     */
    vector_free(&frequencies);
    vector_free(&transmitters);
    free_graph(collision_graph);
    return EXIT_SUCCESS;
}
