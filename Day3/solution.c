#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define EXAMPLE (1)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define LINE_LEN 16
#else
#define INPUT_FILE "./input.txt"
#define LINE_LEN 100
#endif // EXAMPLE

#define DIGITS_TO_FIND 12u /* For part1: 2u \
                              For part2: 12u */

uint32_t findBiggest(char str[], uint32_t len, uint32_t start, uint32_t digitsLeft)
{
    uint32_t biggest = start;
    for (uint32_t idx = start; idx < len - digitsLeft; idx++)
    {
        if (str[idx] > str[biggest])
        {
            biggest = idx;
        }
    }
    return biggest;
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

    char line[LINE_LEN + 2];

    uint64_t current = 0u;
    uint64_t result  = 0u;

    uint32_t digitsToFind = DIGITS_TO_FIND;

    while (fgets(line, sizeof(line), pInputFile) != 0)
    {
        line[strcspn(line, "\n")] = 0;

        uint32_t biggestIdx = 0u;
        for (uint32_t idx = 0; idx < digitsToFind; idx++)
        {
            biggestIdx = findBiggest(line, strlen(line), biggestIdx, digitsToFind - idx - 1);
            current += ((line[biggestIdx] - '0') * pow(10, digitsToFind - idx - 1));
            biggestIdx++;
        }
        result += current;
        current = 0u;
    }

    printf("Result: %lld\n", result);

    return 0;
}