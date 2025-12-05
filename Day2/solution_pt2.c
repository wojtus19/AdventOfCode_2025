#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define EXAMPLE (0)

#if EXAMPLE

#define INPUT_FILE "./example.txt"
#define LINE_LEN 162
#else
#define INPUT_FILE "./input.txt"
#define LINE_LEN 532
#endif // EXAMPLE

#define UINT64_MAX_DIGITS 20
#define TRUE 1
#define FALSE 0

typedef uint8_t bool_t;

uint32_t countDigits(uint64_t n)
{
    uint64_t r = 1;
    while (n > 9)
    {
        n /= 10;
        r++;
    }
    return r;
}

bool_t CheckSequence(char str[], uint32_t strLen, uint32_t seqLen)
{

    if (strLen % seqLen != 0)
    {
        return FALSE;
    }
    for (uint32_t idx = 0u; idx + seqLen <= strLen; idx += seqLen)
    {
        if (strncmp(&str[0], &str[idx], seqLen) != 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool_t CheckValid(uint64_t number)
{
    char strNumber[UINT64_MAX_DIGITS];
    sprintf(strNumber, "%lld", number);
    uint32_t digits = countDigits(number);
    for (uint32_t seqLen = 1; seqLen <= digits / 2; seqLen++)
    {
        if (CheckSequence(strNumber, digits, seqLen))
        {
            return FALSE;
        }
    }
    return TRUE;
}

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
    fgets(line, sizeof(line), pInputFile);

    uint64_t result  = 0u;
    uint64_t start   = 0u;
    uint64_t stop    = 0u;
    uint32_t lineIdx = 0u;
    while (lineIdx < strlen(line))
    {
        sscanf(&line[lineIdx], "%lld-%lld", &start, &stop);

        lineIdx += countDigits(start);
        lineIdx += countDigits(stop);
        lineIdx += 2; /* - and , */
        for (uint64_t idx = start; idx <= stop; idx++)
        {
            if (CheckValid(idx) == FALSE)
            {
                result += idx;
            }
        }
    }

    printf("Result: %lld\n", result);

    return 0;
}
