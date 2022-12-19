#include <rogue.h>
#include "vector.h"

void vector_init(Vector* v)
{
    v->limit = VECTOR_INITIAL_LIMIT;
    v->count = 0;
    v->data = malloc(sizeof(void*) * v->limit);
}

void vector_add(Vector* v, void* data)
{
    // resize if needed
    if(v->count == v->limit)
    {
        v->limit = v->limit * 2;
        v->data = realloc(v->data, sizeof(void*) * v->limit);
    }

    // add data
    v->data[v->count] = data;
    v->count++;
}

void vector_remove(Vector* v, int index)
{
    if(index > -1 && index < v->count)
    {
        // swap the last item to the index to be removed
        // then remove the last item
        v->data[index] = v->data[v->count - 1];
        v->data[v->count - 1] = NULL;
        v->count--;
    }
}

void* vector_get(Vector* v, int index)
{
    if(index > -1 && index < v->count)
    {
        return v->data[index];
    }
    return NULL;
}

bool vector_contains(Vector* v, void* data)
{
    for(int i = 0; i < v->count; i++)
    {
        if(v->data[i] == data)
            return true;
    }
    return false;
}

int vector_count(Vector* v) 
{
    return v->count;
}

void vector_free(Vector* v)
{
    if(v->data)
    {
        free(v->data);
        v->data = NULL;
    }
}
