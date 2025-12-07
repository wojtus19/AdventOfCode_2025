#include "Vector.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXAMPLE (0)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define LINE_LEN 20
#define LINES 4
#else
#define INPUT_FILE "./input.txt"
#define LINE_LEN 3800
#define LINES 5
#endif // EXAMPLE

int main()
{
    FILE* pInputFile = NULL;

    pInputFile = fopen(INPUT_FILE, "r");
    if (NULL == pInputFile)
    {
        printf("One of input files is NULL\n");
        return -1;
    }

    char lines[LINES][LINE_LEN + 2];

    Vector_t problems;
    InitVector(&problems, 10);

    for (uint32_t idx = 0; idx < LINES; idx++)
    {
        fgets(lines[idx], sizeof(lines[idx]), pInputFile);
    }

    uint32_t element  = 0u;
    uint32_t consumed = 0u;
    char op           = '\0';

    uint32_t linesIdxs[LINES] = { 0u };
    while (linesIdxs[0] < strlen(lines[0]))
    {
        // uint32_t newProblem[LINES - 1] = { 0u };
        Equation_t newProblem = { 0u };
        newProblem.elements   = (uint32_t*)malloc(sizeof(uint32_t) * (LINES - 1));

        for (uint32_t jdx = 0; jdx < LINES - 1; jdx++)
        {
            sscanf(&lines[jdx][linesIdxs[jdx]], " %u%n", &element, &consumed);
            newProblem.elements[jdx] = element;
            linesIdxs[jdx] += consumed + 1;
        }
        sscanf(&lines[LINES - 1][linesIdxs[LINES - 1]], " %c%n", &op, &consumed);
        newProblem.operator = op;
        linesIdxs[LINES - 1] += consumed + 1;

        AddToVector(&problems, newProblem);
    }

    /* Part 1 */
    uint64_t resultP1 = 0u;
    uint64_t partial  = 0u;
    for (uint32_t idx = 0; idx < problems.items; idx++)
    {
        if (problems.data[idx].operator == '*')
        {
            partial = 1u;
            for (uint32_t jdx = 0; jdx < LINES - 1; jdx++)
            {
                partial *= problems.data[idx].elements[jdx];
            }
        }
        else if (problems.data[idx].operator == '+')
        {
            partial = 0u;
            for (uint32_t jdx = 0; jdx < LINES - 1; jdx++)
            {
                partial += problems.data[idx].elements[jdx];
            }
        }
        resultP1 += partial;
    }
    printf("Part1 Result: %lld\n", resultP1);

    for (uint32_t idx = 0; idx < problems.items; idx++)
    {
        free(problems.data[idx].elements);
    }

    FreeVector(&problems);
    return 0;
}