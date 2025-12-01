#include <stdint.h>
#include <stdio.h>

#define EXAMPLE (0)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define LINE_LEN 4
#else
#define INPUT_FILE "./input.txt"
#define LINE_LEN 4
#endif // EXAMPLE

int main()
{
    FILE* pInputFile = NULL;

    pInputFile = fopen(INPUT_FILE, "r");
    if (NULL == pInputFile)
    {
        printf("Input file is NULL\n");
        return -1;
    }

    char line[LINE_LEN + 2];

    int32_t part1Result = 0;
    int32_t part2Result = 0;
    int32_t dial        = 50;
    int32_t distance    = 0;
    uint8_t dir         = 0;

    while (fgets(line, sizeof(line), pInputFile) != 0)
    {
        sscanf(line, "%c%d\n", &dir, &distance);
        part2Result += (distance / 100);

        if (dir == 'L')
        {
            dial -= (distance % 100);
            if (dial == 0)
            {
                part2Result++;
            }
            else if (dial < 0)
            {
                if ((dial + distance % 100) != 0)
                    part2Result++;
                dial = 100 + dial;
            }
        }
        else if (dir == 'R')
        {
            dial += (distance % 100);
            if (dial > 99)
            {
                part2Result++;
                dial = dial - 100;
            }
        }
        if (dial == 0)
        {
            part1Result++;
        }
    }

    printf("P1 Result: %d, P2 Result: %d\n", part1Result, part2Result);

    return 0;
}
