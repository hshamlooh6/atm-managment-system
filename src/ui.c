#include "header.h"

//All the functions are ai generated
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        
    }
}

void clearScreen(void)
{
    system("clear");
}

void waitForEnter(void)
{
    char discard[16];
    readStringSafe(NULL, discard, sizeof(discard));
}

void readStringSafe(const char *prompt, char *buffer, int bufferSize)
{
    if (prompt != NULL)
    {
        printf("%s", prompt);
    }

    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {

        }
    }
}

int readIntSafe(const char *prompt)
{
    char line[64];
    char *endPtr;
    long value;

    while (1)
    {
        readStringSafe(prompt, line, sizeof(line));

        value = strtol(line, &endPtr, 10);

        if (endPtr != line)
        {
            while (*endPtr == ' ')
            {
                endPtr++;
            }
            if (*endPtr == '\0')
            {
                return (int)value;
            }
        }

        printf("Please enter a whole number.\n");
    }
}

double readDoubleSafe(const char *prompt)
{
    char line[64];
    char *endPtr;
    double value;

    while (1)
    {
        readStringSafe(prompt, line, sizeof(line));

        value = strtod(line, &endPtr);

        if (endPtr != line)
        {
            while (*endPtr == ' ')
            {
                endPtr++;
            }
            if (*endPtr == '\0')
            {
                return value;
            }
        }

        printf("Please enter a number (e.g. 123.45).\n");
    }
}
