#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status_t InitVector(Vector_t* v, uint32_t size)
{
    v->size  = size;
    v->items = 0u;
    v->data  = (Equation_t*)malloc(sizeof(Equation_t) * size);
    if (NULL != v->data)
    {
        memset(v->data, 0, sizeof(Equation_t) * size);
    }
    else
    {
        return STATUS_NULLPTR;
    }
    return STATUS_SUCCESS;
}

Status_t AddToVector(Vector_t* v, Equation_t value)
{
    if (v->items >= v->size)
    {
        v->data = (Equation_t*)realloc(v->data, sizeof(Equation_t) * v->size * 2);
        if (NULL == v->data)
        {
            printf("Failed memory reallocation for vector.\n");
            return STATUS_NULLPTR;
        }
        memset(&v->data[v->size], 0, sizeof(Equation_t) * v->size);
        v->size = v->size * 2;
    }
    v->data[v->items] = value;
    v->items++;
    return STATUS_SUCCESS;
}

void PrintVector(Vector_t v, void (*printFunc)(Equation_t))
{
    for (uint32_t idx = 0; idx < v.items; idx++)
    {
        printFunc(v.data[idx]);
    }
    printf("\n");
}

void FreeVector(Vector_t* v)
{

    free(v->data);
}