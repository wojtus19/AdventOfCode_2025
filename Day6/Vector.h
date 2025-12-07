
#pragma once

#include <stdint.h>

typedef enum Status_t
{
    STATUS_SUCCESS,
    STATUS_NULLPTR
} Status_t;

typedef struct Equation_t
{
    uint32_t* elements;
    char operator;
} Equation_t;

typedef struct Vector_t
{
    Equation_t* data;
    uint32_t size;
    uint32_t items;
} Vector_t;

Status_t InitVector(Vector_t* v, uint32_t size);

Status_t AddToVector(Vector_t* v, Equation_t value);

void PrintVector(Vector_t v, void (*printFunc)(Equation_t));

void FreeVector(Vector_t* v);