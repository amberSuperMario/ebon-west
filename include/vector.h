#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INITIAL_LIMIT 16

typedef struct Vector
{
    void** data;
    int limit;
    int count;
} Vector;

void vector_init(Vector*);
void vector_add(Vector*, void*);
void vector_remove(Vector*, int);
void* vector_get(Vector*, int);
bool vector_contains(Vector*, void*);
int vector_count(Vector*);
void vector_free(Vector*);

#endif
