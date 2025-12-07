#include "Vector.h"
#include <stdint.h>
#include <stdio.h>

#define EXAMPLE (0)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define LINE_LEN 10
#else
#define INPUT_FILE "./input.txt"
#define LINE_LEN 50
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

    char line[LINE_LEN + 2];

    Vector_t ranges;
    InitVector(&ranges, 10);

    uint64_t from = 0u;
    uint64_t to   = 0u;
    while (fgets(line, sizeof(line), pInputFile) != 0)
    {
        if (line[0] == '\n')
        {
            break;
        }
        sscanf(line, "%lld-%lld", &from, &to);
        Range_t newRange = { .from = from, .to = to };
        AddToVector(&ranges, newRange);
    }

    /* Part 1 */
    uint64_t id          = 0u;
    uint64_t resultPart1 = 0u;
    while (fgets(line, sizeof(line), pInputFile) != 0)
    {
        sscanf(line, "%lld", &id);
        for (uint32_t idx = 0; idx < ranges.items; idx++)
        {
            if (id >= ranges.data[idx].from && id <= ranges.data[idx].to)
            {
                resultPart1++;
                break;
            }
        }
    }
    printf("Part1 Result: %lld\n", resultPart1);

    FreeVector(&ranges);
    return 0;
}