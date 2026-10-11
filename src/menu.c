
#include "header.h"

void mainMenu(struct User u)
{
    int option;

    do
    {
        clearScreen();
        printf("\n\n\t\t======= ATM =======\n\n");
        printf("\t\tLogged in as: %s\n", u.name);
        printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
        printf("\n\t\t[1]- Create a new account\n");
        printf("\t\t[2]- Update account information\n");
        printf("\t\t[3]- Check account details\n");
        printf("\t\t[4]- Check list of owned accounts\n");
        printf("\t\t[5]- Make a transaction\n");
        printf("\t\t[6]- Remove an existing account\n");
        printf("\t\t[7]- Transfer ownership\n");
        printf("\t\t[8]- Log out / Exit\n");
        option = readIntSafe("\nYour choice: ");

        switch (option)
        {
        case 1:
            createNewAccount(u);
            break;
        case 2:
            updateAccountInfo(u);
            break;
        case 3:
            showAccountDetails(u);
            break;
        case 4:
            listMyAccounts(u);
            break;
        case 5:
            makeTransaction(u);
            break;
        case 6:
            removeAccount(u);
            break;
        case 7:
            transferOwnership(u);
            break;
        case 8:
            printf("\nGoodbye, %s!\n", u.name);
            exit(0);
        default:
            printf("Invalid operation!\n");
            waitForEnter();
        }
    } while (1);
}
