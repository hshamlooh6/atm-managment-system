#if defined(__APPLE__)
#define _DARWIN_C_SOURCE
#include <unistd.h>
#else
#define _GNU_SOURCE
#include <crypt.h>
#endif

#include <time.h>
#include "header.h"

//wroted by myself by watching toturials 
//AI improve it 

static void generateSalt(char outSalt[32])
{
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789./";

    outSalt[0] = '$';
    outSalt[1] = '6';
    outSalt[2] = '$';

    for (int i = 0; i < 16; i++)
    {
        int randomIndex = rand() % (int)(sizeof(alphabet) - 1);
        outSalt[3 + i] = alphabet[randomIndex];
    }

    outSalt[19] = '$';
    outSalt[20] = '\0';
}

static void seedRandomOnce(void)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
}

void hashPassword(const char *plainPassword, char outHash[PASSWORD_LEN])
{
    char salt[32];
    seedRandomOnce();
    generateSalt(salt);

    char *result = crypt(plainPassword, salt);
    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: could not hash password.\n");
        exit(1);
    }

    snprintf(outHash, PASSWORD_LEN, "%s", result);
}

int passwordMatches(const char *plainPassword, const char *storedHash)
{
    char *result = crypt(plainPassword, storedHash);
    if (result == NULL)
    {
        return 0;
    }
    return strcmp(result, storedHash) == 0;
}
