#include <termios.h>
#include <unistd.h>
#include "header.h"

static void readHiddenLine(char *buffer, int bufferSize)
{
    struct termios oldFlags, newFlags;

    if (tcgetattr(STDIN_FILENO, &oldFlags) != 0)
    {
        perror("tcgetattr");
        exit(1);
    }

    newFlags = oldFlags;
    newFlags.c_lflag &= ~ECHO;  
    newFlags.c_lflag |= ECHONL; 

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newFlags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }

    readStringSafe(NULL, buffer, bufferSize);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldFlags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
}

int loginMenu(struct User *loggedInUser)
{
    char name[NAME_LEN];
    char password[PASSWORD_LEN];

    clearScreen();
    printf("\n\n\t\t\t\t   Bank Management System\n");
    readStringSafe("\t\t\t\t User Login (username): ", name, sizeof(name));

    printf("\n\t\t\t\tEnter the password to login: ");
    readHiddenLine(password, sizeof(password));

    struct User found;
    if (!findUserByName(name, &found))
    {
        printf("\nNo user found with that name.\n");
        return 0;
    }

    if (!passwordMatches(password, found.password))
    {
        printf("\nWrong password.\n");
        return 0;
    }

    *loggedInUser = found;
    printf("\nPassword match! Welcome, %s.\n", found.name);
    return 1;
}

void registerMenu(struct User *loggedInUser)
{
    char name[NAME_LEN];
    char password[PASSWORD_LEN];
    char passwordConfirm[PASSWORD_LEN];

    clearScreen();
    printf("\n\n\t\t\t\t   Bank Management System\n");
    printf("\t\t\t\t      New user registration\n\n");

    while (1)
    {
        readStringSafe("\t\t\t\t Choose a username: ", name, sizeof(name));

        if (name[0] == '\0')
        {
            printf("Username cannot be empty.\n");
            continue;
        }

        if (userNameExists(name))
        {
            printf("That username is already taken. Please choose another.\n");
            continue;
        }

        break;
    }

    printf("\n\t\t\t\t Choose a password: ");
    readHiddenLine(password, sizeof(password));
    printf("\t\t\t\t Confirm the password: ");
    readHiddenLine(passwordConfirm, sizeof(passwordConfirm));

    if (strcmp(password, passwordConfirm) != 0)
    {
        printf("\nPasswords did not match. Registration cancelled.\n");
        waitForEnter();
        exit(0);
    }

    struct User newUser;
    strncpy(newUser.name, name, NAME_LEN - 1);
    newUser.name[NAME_LEN - 1] = '\0';
    hashPassword(password, newUser.password);

    appendUser(newUser);

    findUserByName(name, loggedInUser);

    printf("\nAccount created! You are now logged in as %s.\n", loggedInUser->name);
}
