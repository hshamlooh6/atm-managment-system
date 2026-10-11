#include "header.h"

static void welcomeScreen(struct User *u)
{
    while (1)
    {
        clearScreen();
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t\t-->> Feel free to login / register:\n");
        printf("\n\t\t[1]- Login\n");
        printf("\t\t[2]- Register\n");
        printf("\t\t[3]- Exit\n");

        int option = readIntSafe("\nYour choice: ");

        if (option == 1)
        {
            if (loginMenu(u))
            {
                return;
            }
            waitForEnter();
        }
        else if (option == 2)
        {
            registerMenu(u);
            return;
        }
        else if (option == 3)
        {
            exit(0);
        }
        else
        {
            printf("Please enter a valid option!\n");
            waitForEnter();
        }
    }
}gf=[          ]

int main(void)
{
    struct User u;

    welcomeScreen(&u);

    mainMenu(u);
    
    return 0;
}
