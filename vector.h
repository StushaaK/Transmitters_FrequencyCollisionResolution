#ifndef __VECTOR__
#define __VECTOR__

#define VECTOR_INIT_CAPACITY 4

typedef struct thevector {
    void **items;
    int capacity;
    int curr_size;
} vector;

void vector_init(vector *);
int vector_curr_size(vector *);
void vector_resize(vector *, int);
void vector_add(vector *, void *);
void vector_set(vector *, int, void *);
void *vector_get(vector *, int);
void vector_print(vector *, char mode);
void vector_delete(vector *, int);
void vector_free(vector *);

#endif
