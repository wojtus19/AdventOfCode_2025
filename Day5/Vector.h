
#pragma once

#include <stdint.h>

typedef enum Status_t
{
    STATUS_SUCCESS,
    STATUS_NULLPTR
} Status_t;

typedef struct Range_t
{
    uint64_t from;
    uint64_t to;
} Range_t;

typedef struct Vector_t
{
    Range_t* data;
    uint32_t size;
    uint32_t items;
} Vector_t;

Status_t InitVector(Vector_t* v, uint32_t size);

Status_t AddToVector(Vector_t* v, Range_t value);

void PrintVector(Vector_t v, void (*printFunc)(Range_t));

void FreeVector(Vector_t* v);