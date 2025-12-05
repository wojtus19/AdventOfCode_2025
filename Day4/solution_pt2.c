#include <stdint.h>
#include <stdio.h>

#define EXAMPLE (0)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define GRID_SIZE 10
#else
#define INPUT_FILE "./input.txt"
#define GRID_SIZE 139
#endif // EXAMPLE

#define TRUE 1
#define FALSE 0
typedef uint8_t bool_t;

bool_t CheckAccess(char grid[GRID_SIZE][GRID_SIZE], uint32_t y, uint32_t x)
{
    uint32_t count = 0u;
    for (int32_t dx = -1; dx <= 1; dx++)
    {
        for (int32_t dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
            {
                continue;
            }
            if (x + dx < 0 || x + dx >= GRID_SIZE ||
                y + dy < 0 || y + dy >= GRID_SIZE)
            {
                continue;
            }
            if (grid[y + dy][x + dx] == '@')
            {
                count++;
            }
        }
    }
    if (count < 4)
    {
        return TRUE;
    }
    return FALSE;
}

int main()
{
    FILE* pInputFile = NULL;

    pInputFile = fopen(INPUT_FILE, "r");
    if (NULL == pInputFile)
    {
        printf("One of input files is NULL\n");
        return -1;
    }

    char line[GRID_SIZE + 2];
    char grid[GRID_SIZE][GRID_SIZE];

    uint32_t idx = 0u;
    while (fgets(line, sizeof(line), pInputFile) != 0)
    {
        for (uint32_t jdx = 0; jdx < GRID_SIZE; jdx++)
        {
            grid[idx][jdx] = line[jdx];
        }
        idx++;
    }

    uint32_t result   = 0u;
    uint32_t accesses = 0u;
    do
    {
        accesses = 0u;
        for (uint32_t idx = 0; idx < GRID_SIZE; idx++)
        {
            for (uint32_t jdx = 0; jdx < GRID_SIZE; jdx++)
            {
                if (grid[idx][jdx] == '@')
                {
                    if (CheckAccess(grid, idx, jdx))
                    {
                        grid[idx][jdx] = '.';
                        accesses++;
                    }
                }
            }
        }
        result += accesses;
    } while (accesses != 0u);

    printf("Result: %d\n", result);

    return 0;
}