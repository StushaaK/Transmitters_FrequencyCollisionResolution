#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vector_init(vector *v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->curr_size = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

int vector_curr_size(vector *v) {
    return v->curr_size;
}

void vector_resize(vector *v, int capacity) {
    void **items = realloc(v->items, sizeof(void *) * capacity);

    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
    else return;
}

void vector_add(vector *v, void *item) {
    if (v->curr_size == v->capacity) vector_resize(v, v->capacity * 2);

    v->items[v->curr_size++] = item;
}

void vector_set(vector *v, int index, void *item) {
    if (index >= 0 && index < v->curr_size) v->items[index] = item;

    else return;
}

void *vector_get(vector *v, int index) {
    if (index >= 0 && index < v->curr_size) return v->items[index];

    return NULL;
}

void vector_print(vector *v, char mode) {
    int i = 0;

    switch (mode) {
        case 'i':
            for (i = 0; i < vector_curr_size(v); i++) printf("%d ", *((int *) vector_get(v, i)));
            printf("\n");
            break;
        case 'f':
            for (i = 0; i < vector_curr_size(v); i++) printf("%f ", *((float *) vector_get(v, i)));
            printf("\n");
            break;
        case 'd':
            for (i = 0; i < vector_curr_size(v); i++) printf("%f ", *((double *) vector_get(v, i)));
            printf("\n");
            break;
        case 'c':
            for (i = 0; i < vector_curr_size(v); i++) printf("%s ", (char *) vector_get(v, i));
            printf("\n");
            break;
        default:
            for (i = 0; i < vector_curr_size(v); i++) printf("%s ", (char *) vector_get(v, i));
            printf("\n");
    }

}

void vector_delete(vector *v, int index) {
    int i = 0;

    if (index < 0 || index >= v->curr_size) return;

    v->items[index] = NULL;

    for (i = index; i < v->curr_size - 1; i++) {
        v->items[i] = v->items[i+1];
        v->items[i + 1] = NULL;
    }

    v->curr_size--;

    if (v->curr_size > 0 && v->curr_size == v->capacity / 4) vector_resize(v, v->capacity / 2);
}

void vector_free(vector *v) {
    size_t i;
    for (i = 0; i < v->curr_size; ++i) {
        free(v->items[i]);
    }
    free(v->items);
}



